/*
 * crash_screen.c
 *
 * If the game crashes, this screen shows up, printing debug info.
 * Useful to trace where the game crashed.
 */

#include <ultra64.h>
#include <stdarg.h>
#include <string.h>
#include "buffers/framebuffers.h"
#include "sm64.h"
#include "lib/src/printf.h"

#ifdef N64_CRASH_SCREEN

#define CRASH_BG_COLOR      GPACK_RGBA5551(0, 0, 0, 1)
#define CRASH_CH_COLOR      GPACK_RGBA5551(255, 255, 255, 1)
#define CRASH_FONT_WIDTH    6
#define CRASH_FONT_HEIGHT   8
// This doesn't really work if you extend horizontal row
#define CRASH_FONT_HOR_ROW  5
#define CRASH_FONT_VER_ROW  19

struct {
    OSThread thread;
    char stack[0x800];
    OSMesgQueue mesgQueue;
    OSMesg mesg;
    u16 *framebuffer;
    u16 width;
    u16 height;
} gCrashScreen;

// A height of seven pixels for each Character * nine rows of characters + one row unused.
u32 gCrashScreenFont[] = {
    #include "textures/crash_screen/crash_screen_font_custom.ia1.inc.c"
};

char *gCauseDesc[18] = {
    "Interrupt",
    "TLB modification",
    "TLB exception on load",
    "TLB exception on store",
    "Address error on load",
    "Address error on store",
    "Bus error on inst.",
    "Bus error on data",
    "System call exception",
    "Breakpoint exception",
    "Reserved instruction",
    "Coprocessor unusable",
    "Arithmetic overflow",
    "Trap exception",
    "Virtual coherency on inst.",
    "Floating point exception",
    "Watchpoint exception",
    "Virtual coherency on data",
};

char *gFpcsrDesc[6] = {
    "Unimplemented operation", "Invalid operation", "Division by zero", "Overflow", "Underflow",
    "Inexact operation",
};

void crash_screen_sleep(s32 ms) {
    u64 cycles = ms * 1000LL * 46875000LL / 1000000ULL;

    osSetTime(0);

    while (osGetTime() < cycles) {
        // wait
    }
}

void crash_screen_draw_rect(s32 x, s32 y, s32 w, s32 h) {
    u16 *ptr;
    s32 i, j;

    ptr = gCrashScreen.framebuffer + gCrashScreen.width * y + x;

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            // 0xe738 = 0b1110011100111000
            *ptr = ((*ptr & 0xE738) >> 2) | CRASH_BG_COLOR;
            ptr++;
        }

        ptr += gCrashScreen.width - w;
    }
}

void crash_screen_draw_glyph(s32 x, s32 y, s32 glyph) {
    s32 shift = ((glyph % CRASH_FONT_HOR_ROW) * CRASH_FONT_WIDTH);
    const u32* data = &gCrashScreenFont[glyph / CRASH_FONT_HOR_ROW * CRASH_FONT_HEIGHT];
    s32 i;
    s32 j;

    u16* ptr = gCrashScreen.framebuffer + (gCrashScreen.width) * y + x;

    for (i = 0; i < CRASH_FONT_HEIGHT; i++) {
        u32 bit = 0x80000000U >> shift;
        u32 rowMask = *data++;

        for (j = 0; j < CRASH_FONT_WIDTH; j++) {
            if (bit & rowMask) {
                *ptr = CRASH_CH_COLOR;
            }
            ptr++;
            bit >>= 1;
        }

        ptr += gCrashScreen.width - CRASH_FONT_WIDTH;
    }
}

char *crash_screen_copy_to_buf(char *dest, const char *src, size_t size) {
    memcpy(dest, src, size);
    return dest + size;
}

void crash_screen_print(s32 x, s32 y, const char *fmt, ...) {
    char *ptr;
    u32 glyph;
    s32 size;
    char buf[0x100];
    va_list args;

    va_start(args, fmt);

    size = _Printf(crash_screen_copy_to_buf, buf, fmt, args);

    if (size > 0) {
        ptr = buf;

        while (size > 0) {
            glyph = ((*ptr - 0x20) & 0x7f);

            if (glyph != 0xff) {
                crash_screen_draw_glyph(x, y, glyph);
            }

            x += CRASH_FONT_WIDTH;
            size--;
            ptr++;
        }
    }

    va_end(args);
}

void crash_screen_print_float_reg(s32 x, s32 y, s32 regNum, void *addr) {
    u32 bits;
    s32 exponent;

    bits = *(u32 *) addr;
    exponent = ((bits & 0x7f800000U) >> 0x17) - 0x7f;
    if ((exponent >= -0x7e && exponent <= 0x7f) || bits == 0) {
        crash_screen_print(x, y, "F%02d:%.3e", regNum, *(f32 *) addr);
    } else {
        crash_screen_print(x, y, "F%02d:---------", regNum);
    }
}

void crash_screen_print_fpcsr(u32 fpcsr) {
    s32 i;
    u32 bit = 1 << 17;

    crash_screen_print(30, 155, "FPCSR:%08XH", fpcsr);

    for (i = 0; i < 6; i++) {
        if (fpcsr & bit) {
            crash_screen_print(132, 155, "(%s)", gFpcsrDesc[i]);
            return;
        }
        bit >>= 1;
    }
}

void draw_crash_screen(OSThread *thread) {
    s16 cause;
    __OSThreadContext *tc = &thread->context;

    cause = (tc->cause >> 2) & 0x1f;
    if (cause == 23) { // EXC_WATCH
        cause = 16;
    }
    if (cause == 31) { // EXC_VCED
        cause = 17;
    }

    osWritebackDCacheAll();

    crash_screen_draw_rect(25, 20, 270, 25);
    crash_screen_print(30, 25, "THREAD:%d  (%s)", thread->id, gCauseDesc[cause]);
    crash_screen_print(30, 35, "PC:%08XH   SR:%08XH   VA:%08XH", tc->pc, tc->sr, tc->badvaddr);

    crash_screen_sleep(2000);
    osViBlack(FALSE);
    osViSwapBuffer(gCrashScreen.framebuffer);

    crash_screen_draw_rect(25, 45, 270, 185);

    crash_screen_print(30, 50,  "AT:%08XH   V0:%08XH   V1:%08XH", (u32) tc->at, (u32) tc->v0, (u32) tc->v1);
    crash_screen_print(30, 60,  "A0:%08XH   A1:%08XH   A2:%08XH", (u32) tc->a0, (u32) tc->a1, (u32) tc->a2);
    crash_screen_print(30, 70,  "A3:%08XH   T0:%08XH   T1:%08XH", (u32) tc->a3, (u32) tc->t0, (u32) tc->t1);
    crash_screen_print(30, 80,  "T2:%08XH   T3:%08XH   T4:%08XH", (u32) tc->t2, (u32) tc->t3, (u32) tc->t4);
    crash_screen_print(30, 90,  "T5:%08XH   T6:%08XH   T7:%08XH", (u32) tc->t5, (u32) tc->t6, (u32) tc->t7);
    crash_screen_print(30, 100, "S0:%08XH   S1:%08XH   S2:%08XH", (u32) tc->s0, (u32) tc->s1, (u32) tc->s2);
    crash_screen_print(30, 110, "S3:%08XH   S4:%08XH   S5:%08XH", (u32) tc->s3, (u32) tc->s4, (u32) tc->s5);
    crash_screen_print(30, 120, "S6:%08XH   S7:%08XH   T8:%08XH", (u32) tc->s6, (u32) tc->s7, (u32) tc->t8);
    crash_screen_print(30, 130, "T9:%08XH   GP:%08XH   SP:%08XH", (u32) tc->t9, (u32) tc->gp, (u32) tc->sp);
    crash_screen_print(30, 140, "S8:%08XH   RA:%08XH", (u32) tc->s8, (u32) tc->ra);

    crash_screen_print_fpcsr(tc->fpcsr);

    crash_screen_print_float_reg(30, 170, 0, &tc->fp0.f.f_even);
    crash_screen_print_float_reg(120, 170, 2, &tc->fp2.f.f_even);
    crash_screen_print_float_reg(210, 170, 4, &tc->fp4.f.f_even);
    crash_screen_print_float_reg(30, 180, 6, &tc->fp6.f.f_even);
    crash_screen_print_float_reg(120, 180, 8, &tc->fp8.f.f_even);
    crash_screen_print_float_reg(210, 180, 10, &tc->fp10.f.f_even);
    crash_screen_print_float_reg(30, 190, 12, &tc->fp12.f.f_even);
    crash_screen_print_float_reg(120, 190, 14, &tc->fp14.f.f_even);
    crash_screen_print_float_reg(210, 190, 16, &tc->fp16.f.f_even);
    crash_screen_print_float_reg(30, 200, 18, &tc->fp18.f.f_even);
    crash_screen_print_float_reg(120, 200, 20, &tc->fp20.f.f_even);
    crash_screen_print_float_reg(210, 200, 22, &tc->fp22.f.f_even);
    crash_screen_print_float_reg(30, 210, 24, &tc->fp24.f.f_even);
    crash_screen_print_float_reg(120, 210, 26, &tc->fp26.f.f_even);
    crash_screen_print_float_reg(210, 210, 28, &tc->fp28.f.f_even);
    crash_screen_print_float_reg(30, 220, 30, &tc->fp30.f.f_even);

    crash_screen_sleep(500);

    crash_screen_print(210, 140, "MM:%08XH", *(u32*)tc->pc);
}

OSThread *get_crashed_thread(void) {
    OSThread *thread = __osGetCurrFaultedThread();

    while (thread->priority != -1) {
        if (thread->priority > OS_PRIORITY_IDLE && thread->priority < OS_PRIORITY_APPMAX
            && (thread->flags & 3)) {
            return thread;
        }

        thread = thread->tlnext;
    }

    return NULL;
}

void thread2_crash_screen(UNUSED void *arg) {
    OSMesg mesg;
    OSThread *thread;

    osSetEventMesg(OS_EVENT_CPU_BREAK, &gCrashScreen.mesgQueue, (OSMesg) 1);
    osSetEventMesg(OS_EVENT_FAULT, &gCrashScreen.mesgQueue, (OSMesg) 2);
    do {
        osRecvMesg(&gCrashScreen.mesgQueue, &mesg, 1);
        thread = get_crashed_thread();
    } while (thread == NULL);

    draw_crash_screen(thread);

    while (TRUE) {}
}

void crash_screen_set_framebuffer(u16 *framebuffer, u16 width, u16 height) {
    gCrashScreen.framebuffer = framebuffer;
    gCrashScreen.width = width;
    gCrashScreen.height = height;
}

extern u16 sRenderedFramebuffer;

void crash_screen_init(void) {
    gCrashScreen.framebuffer = (u16 *) gFramebuffers[sRenderedFramebuffer];
    gCrashScreen.width = SCREEN_WIDTH;
    gCrashScreen.height = SCREEN_HEIGHT;

    osCreateMesgQueue(&gCrashScreen.mesgQueue, &gCrashScreen.mesg, 1);
    osCreateThread(&gCrashScreen.thread, 2, thread2_crash_screen, NULL,
        gCrashScreen.stack + sizeof(gCrashScreen.stack), OS_PRIORITY_APPMAX);
    osStartThread(&gCrashScreen.thread);
}

#endif
