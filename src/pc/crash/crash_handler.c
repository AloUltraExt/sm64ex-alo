// Crash handler by PeachyPeach, from sm64ex-omm
// Adapated to vanilla by djoslin0, from sm64ex-coop
// Linux port by Isaac0-dev
// Simplified dependencies by AloXado320

#if defined(__x86_64__) || defined(_M_X64) // 64 bit
#define ENABLE_CRASH_HANDLER
#endif

#if defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86) // 32 bit
#define ENABLE_CRASH_HANDLER
#endif

#if (defined(_WIN32) || defined(__linux__)) && !defined(WAPI_DUMMY) && defined(ENABLE_CRASH_HANDLER)
#ifdef HAVE_SDL2
#include <SDL2/SDL.h>
#endif

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "config.h"
#include "gfx_dimensions.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "game/segment2.h"
#include "game/mario.h"
#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/gfx/gfx_dxgi.h"
#include "pc/gfx/gfx_sdl.h"
#include "pc/gfx/gfx_pc.h"
#include "pc/gfx/gfx_rendering_api.h"

// Graphics and textures
#include "pc/crash/crash_graphics.h"

typedef struct {
    s32 x, y;
    u8 r, g, b;
    char s[128];
} CrashHandlerText;
static CrashHandlerText sCrashHandlerText[128 + 256];

#define PTR long long unsigned int)(uintptr_t

#define ARRAY_SIZE(a)               (sizeof(a) / sizeof(a[0]))
#define MEMNEW(typ, cnt)            calloc(sizeof(typ), cnt)
#define STRING(str, size, fmt, ...) char str[size]; snprintf(str, size, fmt, __VA_ARGS__);

#ifdef _WIN32

#define OS_NAME "Windows"

// Architecture defines
#if IS_64_BIT
    #define CRASH_HANDLER_TYPE LONG
    #define SYMBOL_INCREMENT 16
    #define SYMBOL_SCAN_FORMAT "%016llX"
    #define MACHINE_TYPE IMAGE_FILE_MACHINE_AMD64
    #define ARCHITECTURE_STR "64-bit"
#else
    #define CRASH_HANDLER_TYPE LONG WINAPI
    #define SYMBOL_INCREMENT 9
    #define SYMBOL_SCAN_FORMAT "%08X"
    #define MACHINE_TYPE IMAGE_FILE_MACHINE_I386
    #define ARCHITECTURE_STR "32-bit"
#endif

#include <stdio.h>
#include <windows.h>
#include <dbghelp.h>
#include <crtdbg.h>
#include "dbghelp.h"

static struct {
    u32 code;
    const char *error;
    const char *message;
} sCrashHandlerErrors[] = {
    { EXCEPTION_ACCESS_VIOLATION,       "Segmentation Fault",       "The game tried to %s at address 0x%016llX." },
    { EXCEPTION_ARRAY_BOUNDS_EXCEEDED,  "Array Out Of Bounds",      "The game tried to access an element out of the array bounds." },
    { EXCEPTION_DATATYPE_MISALIGNMENT,  "Data Misalignment",        "The game tried to access misaligned data." },
    { EXCEPTION_BREAKPOINT,             "Breakpoint",               "The game reached a breakpoint." },
    { EXCEPTION_FLT_DENORMAL_OPERAND,   "Float Denormal Operand",   "The game tried to perform a floating point operation with a denormal operand." },
    { EXCEPTION_FLT_DIVIDE_BY_ZERO,     "Float Division By Zero",   "The game tried to divide a floating point number by zero." },
    { EXCEPTION_FLT_INEXACT_RESULT,     "Float Inexact Result",     "The game couldn't represent the result of a floating point operation as a decimal fraction." },
    { EXCEPTION_FLT_INVALID_OPERATION,  "Float Invalid Operation",  "The game tried to perform an invalid floating point operation." },
    { EXCEPTION_FLT_OVERFLOW,           "Float Overflow",           "An overflow occurred with a floating point number." },
    { EXCEPTION_FLT_STACK_CHECK,        "Float Stack Overflow",     "The game performed a floating point operation resulting in a stack overflow." },
    { EXCEPTION_FLT_UNDERFLOW,          "Float Underflow",          "An underflow occurred with a floating point number." },
    { EXCEPTION_ILLEGAL_INSTRUCTION,    "Illegal Instruction",      "The game tried to execute an invalid instruction." },
    { EXCEPTION_IN_PAGE_ERROR,          "Page Error",               "The game tried to %s at address 0x%016llX." },
    { EXCEPTION_INT_DIVIDE_BY_ZERO,     "Integer Division By Zero", "The game tried to divide an integer by zero." },
    { EXCEPTION_INT_OVERFLOW,           "Integer Overflow",         "An overflow occurred with an integer." },
    { EXCEPTION_PRIV_INSTRUCTION,       "Instruction Not Allowed",  "The game tried to execute an invalid instruction." },
    { EXCEPTION_STACK_OVERFLOW,         "Stack Overflow",           "The game performed an operation resulting in a stack overflow." },
    { 0,                                "Unknown Exception",        "An unknown exception occurred." },
};

#if !IS_64_BIT
static ULONG CaptureStackWalkBackTrace(CONTEXT* ctx, DWORD FramesToSkip, DWORD FramesToCapture, void* BackTrace[]) {

    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();

    STACKFRAME64 stack;
    memset(&stack, 0, sizeof(STACKFRAME64));
#if IS_64_BIT
    stack.AddrPC.Offset = (*ctx).Rip;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrStack.Offset = (*ctx).Rsp;
    stack.AddrStack.Mode = AddrModeFlat;
    stack.AddrFrame.Offset = (*ctx).Rbp;
    stack.AddrFrame.Mode = AddrModeFlat;
#else
    stack.AddrPC.Offset = (*ctx).Eip;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrStack.Offset = (*ctx).Esp;
    stack.AddrStack.Mode = AddrModeFlat;
    stack.AddrFrame.Offset = (*ctx).Ebp;
    stack.AddrFrame.Mode = AddrModeFlat;
#endif

    ULONG frame = 0;
    for (frame = 0; ; frame++)
    {
        if (!StackWalk64(MACHINE_TYPE, process, thread, &stack, ctx, NULL, NULL, NULL, NULL)) { break; }
        if (frame < FramesToSkip || frame >= FramesToCapture) { continue; }
        BackTrace[frame+1] = (void*)(intptr_t)stack.AddrPC.Offset;
    }
    return frame;
}
#endif

#elif __linux__

#define OS_NAME "Linux"

#if IS_64_BIT
    #define CRASH_HANDLER_TYPE LONG
    #define SYMBOL_INCREMENT 16
    #define SYMBOL_SCAN_FORMAT "%ld"
    #define MACHINE_TYPE IMAGE_FILE_MACHINE_AMD64
    #define ARCHITECTURE_STR "64-bit"
#else
    #define CRASH_HANDLER_TYPE LONG WINAPI
    #define SYMBOL_INCREMENT 9
    #define SYMBOL_SCAN_FORMAT "%ld"
    #define MACHINE_TYPE IMAGE_FILE_MACHINE_I386
    #define ARCHITECTURE_STR "32-bit"
#endif

#define __USE_GNU

#include <signal.h>
#include <execinfo.h>
#include <ucontext.h>
#include <dlfcn.h>

static struct {
    u32 code;
    const char *error;
    const char *message;
} sCrashHandlerErrors[] = {
    { SIGBUS,       "Bad Memory Access",        "The game tried to access memory out of bounds." },
    { SIGFPE,       "Floating Point Exception", "The game tried to perform illegal arithmetic on a floating point." },
    { SIGILL,       "Illegal Instruction",      "The game tried to execute an invalid instruction." },
    { SIGSEGV,      "Segmentation Fault",       "The game tried to %s at address 0x%016llX." },
};

#endif

static void crash_font_render_char(char c) {
    // replace undisplayable characters
    if (c < ' ' || (u8)c > ('~' + 1)) { c = '?'; }
    if (c == ' ') { return; }

    void* fontChar = (void*)crash_font_pc_chars_lut[c - '!'];
    if (fontChar == NULL) { fontChar = (void*)crash_font_pc_chars_lut[0x5E]; }

    gDPLoadTextureBlock(gDisplayListHead++, fontChar, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, 3, 3, G_TX_NOLOD, G_TX_NOLOD);

    gSPDisplayList(gDisplayListHead++, dl_crash_font_display_list_vertices);
}

#define crash_handler_set_text(_x_, _y_, _r_, _g_, _b_, _fmt_, ...)     \
{                                                                       \
    if (_x_ == -1) {                                                    \
        pText->x = ((pText - 1)->x + strlen((pText - 1)->s) * 4);       \
    } else {                                                            \
        pText->x = _x_;                                                 \
    }                                                                   \
    pText->y = _y_;                                                     \
    pText->r = _r_;                                                     \
    pText->g = _g_;                                                     \
    pText->b = _b_;                                                     \
    snprintf(pText->s, 128, _fmt_, __VA_ARGS__);                        \
    pText++;                                                            \
}

static void crash_handler_produce_one_frame() {
    // Start frame
    gfx_start_frame();
    select_gfx_pool();
    init_rcp();

    float minAspectRatio = 1.743468f;
    float aspectScale = 1.0f;
    if (gfx_current_dimensions.aspect_ratio < minAspectRatio) {
        aspectScale = gfx_current_dimensions.aspect_ratio / minAspectRatio;
    }

    // Fix scaling issues
    extern Vp D_8032CF00;
    gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&D_8032CF00));
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, BORDER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BORDER_HEIGHT);

    // Clear screen
    create_dl_translation_matrix(MENU_MTX_PUSH, GFX_DIMENSIONS_FROM_LEFT_EDGE(0), 240.f, 0.f);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, (GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT) / 130.f, 3.f, 1.f);
    gDPSetEnvColor(gDisplayListHead++, 0x00, 0x00, 0x00, 0xFF);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    // Print text
    gSPDisplayList(gDisplayListHead++, dl_crash_font_display_list_begin);
    for (CrashHandlerText* text = sCrashHandlerText; text->s[0] != 0; ++text) {
        s32 x = GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(text->x * aspectScale);
        s32 y = SCREEN_HEIGHT - 8 - text->y * aspectScale;

        gDPPipeSync(gDisplayListHead++);
        gDPSetEnvColor(gDisplayListHead++, text->r, text->g, text->b, 0xFF);
        create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);

        // translate scale
        f32 fontSize = 10.0f * aspectScale;
        create_dl_scale_matrix(MENU_MTX_NOPUSH, fontSize, fontSize, 1.0f);

        // set color
        gDPSetEnvColor(gDisplayListHead++, text->r, text->g, text->b, 0xFF);

        // render the line
        f32 addX = 0;
        size_t length = strlen(text->s);
        for (size_t i = 0; i < length; i++) {
            char c = text->s[i];
            f32 charWidth = 0.4f;

            if (c <= 0x20 || c >= 0x7F) {
                addX += charWidth;
                continue;
            }

            if (addX != 0) {
                create_dl_translation_matrix(MENU_MTX_NOPUSH, addX, 0, 0);
                addX = 0;
            }
            // render
            crash_font_render_char(c);

            create_dl_translation_matrix(MENU_MTX_NOPUSH, charWidth, 0, 0);
        }

        // pop
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }

    // Render frame
    end_master_display_list();
    alloc_display_list(0);
    display_and_vsync();
    gfx_end_frame();
}

static void crash_handler_add_info_str(CrashHandlerText** pTextP, f32 x, f32 y, char* title, char* value) {
    CrashHandlerText* pText = *pTextP;
    crash_handler_set_text(x, y, 0xFF, 0xFF, 0x00, "%s", title);
    crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, "%s", ": ");
    crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", value);
    *pTextP = pText;
}

static void crash_handler_add_info_int(CrashHandlerText** pTextP, f32 x, f32 y, char* title, int value) {
    CrashHandlerText* pText = *pTextP;
    crash_handler_set_text(x, y, 0xFF, 0xFF, 0x00, "%s", title);
    crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, "%s", ": ");
    crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%d", value);
    *pTextP = pText;
}

#ifdef _WIN32
static CRASH_HANDLER_TYPE crash_handler(EXCEPTION_POINTERS *ExceptionInfo)
#elif __linux__
static void crash_handler(const int signalNum, siginfo_t *info, ucontext_t *context)
#endif
{
    memset(sCrashHandlerText, 0, sizeof(sCrashHandlerText));
    CrashHandlerText *pText = &sCrashHandlerText[0];

    // Exception report
    crash_handler_set_text(8, -4, 0xFF, 0x80, 0x00, "%s", "Please report this crash with a consistent way to reproduce it.");

    // Exception address, code, type and info
#ifdef _WIN32
    if (ExceptionInfo && ExceptionInfo->ExceptionRecord) {
        PEXCEPTION_RECORD er = ExceptionInfo->ExceptionRecord;
        crash_handler_set_text( 8, 4, 0xFF, 0x00, 0x00, "%s", "Exception occurred at address ");
        crash_handler_set_text(-1, 4, 0xFF, 0xFF, 0x00, "0x%016llX", (PTR) er->ExceptionAddress);
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0x00, "%s", " with error code ");
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0xFF, "0x%08X", (u32) er->ExceptionCode);
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0x00, "%s", ":");
        for (s32 i = 0; i != ARRAY_SIZE(sCrashHandlerErrors); ++i) {
            if (sCrashHandlerErrors[i].code == (u32) er->ExceptionCode || sCrashHandlerErrors[i].code == 0) {
                crash_handler_set_text( 8, 12, 0xFF, 0x00, 0x00, "%s", sCrashHandlerErrors[i].error);
                crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", " - ");
                if (er->ExceptionCode == EXCEPTION_ACCESS_VIOLATION || er->ExceptionCode == EXCEPTION_IN_PAGE_ERROR) {
                    crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, sCrashHandlerErrors[i].message, (er->ExceptionInformation[0] ? "write" : "read"), (PTR)er->ExceptionInformation[1]);
                } else {
                    crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", sCrashHandlerErrors[i].message);
                }
                break;
            }
        }
#elif __linux__
    if (signalNum != 0 && info != NULL) {
        crash_handler_set_text( 8, 4, 0xFF, 0x00, 0x00, "%s", "Exception occurred at address ");
        crash_handler_set_text(-1, 4, 0xFF, 0xFF, 0x00, "0x%016llX", (u64) info->si_addr);
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0x00, "%s", " with error code ");
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0xFF, "0x%08X", (u32) signalNum);
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0x00, "%s", ":");
        for (s32 i = 0; i != ARRAY_SIZE(sCrashHandlerErrors); ++i) {
            if (sCrashHandlerErrors[i].code == (u32) signalNum || sCrashHandlerErrors[i].code == 0) {
                crash_handler_set_text( 8, 12, 0xFF, 0x00, 0x00, "%s", sCrashHandlerErrors[i].error);
                crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", " - ");
                if (signalNum == SIGSEGV) {
                    char segFaultStr[128] = "";
                    if (info->si_code == SEGV_MAPERR) {
                        snprintf(segFaultStr, 128, "The game tried to read unmapped memory at address %p", info->si_addr);
                    } else if (info->si_code == SEGV_ACCERR) {
                        snprintf(segFaultStr, 128, "The game tried to %s at address %016llX", ((context->uc_mcontext.gregs[REG_ERR] & 0x2) != 0 ? "write" : "read"), (u64) info->si_addr);
                    } else {
                        snprintf(segFaultStr, 128, "Unknown segmentation fault at address %p", info->si_addr);
                    }

                    crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", segFaultStr);
                } else {
                    crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", sCrashHandlerErrors[i].message);
                }
                break;
            }
        }
#endif
    } else {
        crash_handler_set_text(8,  4, 0xFF, 0x00, 0x00, "%s", "An unknown exception occurred somewhere in the game's code.");
        crash_handler_set_text(8, 12, 0x80, 0x80, 0x80, "%s", "Unable to retrieve the exception info.");
    }

    // Registers
    crash_handler_set_text( 8, 22, 0xFF, 0xFF, 0xFF,   "%s", "Registers:");
#ifdef _WIN32
    if (ExceptionInfo && ExceptionInfo->ContextRecord) {
        PCONTEXT cr = ExceptionInfo->ContextRecord;
#if IS_64_BIT
        crash_handler_set_text( 8, 30, 0xFF, 0xFF, 0xFF,   "RSP: 0x%016llX", (PTR)cr->Rsp);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  RBP: 0x%016llX", (PTR)cr->Rbp);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  RIP: 0x%016llX", (PTR)cr->Rip);
        crash_handler_set_text( 8, 38, 0xFF, 0xFF, 0xFF,   "RAX: 0x%016llX", (PTR)cr->Rax);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RBX: 0x%016llX", (PTR)cr->Rbx);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RCX: 0x%016llX", (PTR)cr->Rcx);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RDX: 0x%016llX", (PTR)cr->Rdx);
        crash_handler_set_text( 8, 46, 0xFF, 0xFF, 0xFF,   "R08: 0x%016llX", (PTR)cr->R8);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R09: 0x%016llX", (PTR)cr->R9);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R10: 0x%016llX", (PTR)cr->R10);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R11: 0x%016llX", (PTR)cr->R11);
        crash_handler_set_text( 8, 54, 0xFF, 0xFF, 0xFF,   "R12: 0x%016llX", (PTR)cr->R12);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R13: 0x%016llX", (PTR)cr->R13);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R14: 0x%016llX", (PTR)cr->R14);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R15: 0x%016llX", (PTR)cr->R15);
        crash_handler_set_text( 8, 62, 0xFF, 0xFF, 0xFF,   "RSI: 0x%016llX", (PTR)cr->Rsi);
        crash_handler_set_text(-1, 62, 0xFF, 0xFF, 0xFF, "  RDI: 0x%016llX", (PTR)cr->Rdi);
#else
        crash_handler_set_text( 8, 30, 0xFF, 0xFF, 0xFF,   "EAX: 0x%016llX", (PTR)cr->Eax);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  EBX: 0x%016llX", (PTR)cr->Ebx);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  ECX: 0x%016llX", (PTR)cr->Ecx);
        crash_handler_set_text( 8, 38, 0xFF, 0xFF, 0xFF,   "EDX: 0x%016llX", (PTR)cr->Edx);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  ESI: 0x%016llX", (PTR)cr->Esi);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  EDI: 0x%016llX", (PTR)cr->Edi);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  EBP: 0x%016llX", (PTR)cr->Ebp);
        crash_handler_set_text( 8, 46, 0xFF, 0xFF, 0xFF,   "EIP: 0x%016llX", (PTR)cr->Eip);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  ESP: 0x%016llX", (PTR)cr->Esp);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "   CS: 0x%016llX", (PTR)cr->SegCs);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "   DS: 0x%016llX", (PTR)cr->SegDs);
        crash_handler_set_text( 8, 54, 0xFF, 0xFF, 0xFF,   " ES: 0x%016llX", (PTR)cr->SegEs);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   FS: 0x%016llX", (PTR)cr->SegFs);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   GS: 0x%016llX", (PTR)cr->SegGs);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   SS: 0x%016llX", (PTR)cr->SegSs);
        crash_handler_set_text( 8, 62, 0xFF, 0xFF, 0xFF,   "DR0: 0x%016llX", (PTR)cr->Dr0);
        crash_handler_set_text(-1, 62, 0xFF, 0xFF, 0xFF, "  DR1: 0x%016llX", (PTR)cr->Dr1);
#endif
#elif __linux__
    if (context->uc_mcontext.gregs[REG_RSP] != 0) {
#if IS_64_BIT
        crash_handler_set_text( 8, 30, 0xFF, 0xFF, 0xFF,   "RSP: 0x%016llX", context->uc_mcontext.gregs[REG_RSP]);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  RBP: 0x%016llX", context->uc_mcontext.gregs[REG_RBP]);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  RIP: 0x%016llX", context->uc_mcontext.gregs[REG_RIP]);
        crash_handler_set_text( 8, 38, 0xFF, 0xFF, 0xFF,   "RAX: 0x%016llX", context->uc_mcontext.gregs[REG_RAX]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RBX: 0x%016llX", context->uc_mcontext.gregs[REG_RBX]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RCX: 0x%016llX", context->uc_mcontext.gregs[REG_RCX]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RDX: 0x%016llX", context->uc_mcontext.gregs[REG_RDX]);
        crash_handler_set_text( 8, 46, 0xFF, 0xFF, 0xFF,   "R08: 0x%016llX", context->uc_mcontext.gregs[REG_R8]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R09: 0x%016llX", context->uc_mcontext.gregs[REG_R9]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R10: 0x%016llX", context->uc_mcontext.gregs[REG_R10]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R11: 0x%016llX", context->uc_mcontext.gregs[REG_R11]);
        crash_handler_set_text( 8, 54, 0xFF, 0xFF, 0xFF,   "R12: 0x%016llX", context->uc_mcontext.gregs[REG_R12]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R13: 0x%016llX", context->uc_mcontext.gregs[REG_R13]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R14: 0x%016llX", context->uc_mcontext.gregs[REG_R14]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R15: 0x%016llX", context->uc_mcontext.gregs[REG_R15]);
        crash_handler_set_text( 8, 62, 0xFF, 0xFF, 0xFF,   "RSI: 0x%016llX", context->uc_mcontext.gregs[REG_RSI]);
        crash_handler_set_text(-1, 62, 0xFF, 0xFF, 0xFF, "  RDI: 0x%016llX", context->uc_mcontext.gregs[REG_RDI]);
#else
        crash_handler_set_text( 8, 30, 0xFF, 0xFF, 0xFF,   "EAX: 0x%016llX", context->uc_mcontext.gregs[REG_EAX]);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  EBX: 0x%016llX", context->uc_mcontext.gregs[REG_EBX]);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  ECX: 0x%016llX", context->uc_mcontext.gregs[REG_ECX]);
        crash_handler_set_text( 8, 38, 0xFF, 0xFF, 0xFF,   "EDX: 0x%016llX", context->uc_mcontext.gregs[REG_EDX]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  ESI: 0x%016llX", context->uc_mcontext.gregs[REG_ESI]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  EDI: 0x%016llX", context->uc_mcontext.gregs[REG_EDI]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  EBP: 0x%016llX", context->uc_mcontext.gregs[REG_EBP]);
        crash_handler_set_text( 8, 46, 0xFF, 0xFF, 0xFF,   "EIP: 0x%016llX", context->uc_mcontext.gregs[REG_EIP]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  ESP: 0x%016llX", context->uc_mcontext.gregs[REG_ESP]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "   CS: 0x%016llX", context->uc_mcontext.gregs[REG_CS]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "   DS: 0x%016llX", context->uc_mcontext.gregs[REG_DS]);
        crash_handler_set_text( 8, 54, 0xFF, 0xFF, 0xFF,   " ES: 0x%016llX", context->uc_mcontext.gregs[REG_ES]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   FS: 0x%016llX", context->uc_mcontext.gregs[REG_FS]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   GS: 0x%016llX", context->uc_mcontext.gregs[REG_GS]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   SS: 0x%016llX", context->uc_mcontext.gregs[REG_SS]);
        crash_handler_set_text( 8, 62, 0xFF, 0xFF, 0xFF,   "DR0: 0x%016llX", context->uc_mcontext.gregs[REG_RDI]);
        crash_handler_set_text(-1, 62, 0xFF, 0xFF, 0xFF, "  DR1: 0x%016llX", context->uc_mcontext.gregs[REG_RDX]);
#endif
#endif
    } else {
        crash_handler_set_text(8, 30, 0x80, 0x80, 0x80, "%s", "Unable to access the registers.");
    }

    // Stack trace
    crash_handler_set_text(8, 72, 0xFF, 0xFF, 0xFF, "%s", "Stack trace:");
#ifdef _WIN32
    if (ExceptionInfo && ExceptionInfo->ContextRecord) {
        static const char sGlobalFunctionIdentifier[] = "(sec1)(fl0x00)(ty20)(scl2)(nx0)0x";
        static const char sStaticFunctionIdentifier[] = "(sec1)(fl0x00)(ty20)(scl3)(nx0)0x";
        typedef struct Symbol { uintptr_t offset; char name[128]; struct Symbol *next; } Symbol;
        Symbol *symbols = NULL;
        Symbol* symbol0 = NULL;

        // Load symbols
        char filename[256] = { 0 };
        if (GetModuleFileName(NULL, filename, sizeof(filename))) {
            int index = strlen(filename);
            while (--index > 0) {
                if (filename[index] == '\\') {
                    filename[index] = '\0';
                    break;
                }
            }
            strncat(filename, "\\sm64pc.map", 255);
        } else {
            snprintf(filename, 256, "%s", "sm64pc.map");
        }

        FILE *f = fopen(filename, "r");
        if (f) {
            char buffer[1024];
            while (fgets(buffer, 1024, f)) {

                // Remove spaces
                char bufferNoSpace[1024] = { 0 };
                for (char *p0 = buffer, *p1 = bufferNoSpace; *p0 != 0; ++p0) {
                    if (*p0 > 0x20) {
                        *(p1++) = *p0;
                    }
                }

                // Try to find identifiers
                char *id0 = strstr(bufferNoSpace, sGlobalFunctionIdentifier);
                char *id1 = strstr(bufferNoSpace, sStaticFunctionIdentifier);
                if (id0 || id1) {
                    char *addr = (char *) max((uintptr_t) id0, (uintptr_t) id1) + sizeof(sGlobalFunctionIdentifier) - 1;
                    char* name = addr + SYMBOL_INCREMENT;

                    // New symbol
                    Symbol *newSymbol = MEMNEW(Symbol, 1);
                    snprintf(newSymbol->name, 128, "%s", name); *name = 0;
                    sscanf(addr, SYMBOL_SCAN_FORMAT, &newSymbol->offset);
                    newSymbol->next = NULL;

                    // Store symbol
                    if (symbols == NULL) {
                        symbols = newSymbol;
                    } else {
                        for (Symbol *symbol = symbols;; symbol = symbol->next) {
                            if (symbol->next == NULL) {
                                symbol->next = newSymbol;
                                break;
                            }
                            if (symbol->next->offset > newSymbol->offset) {
                                newSymbol->next = symbol->next;
                                symbol->next = newSymbol;
                                break;
                            }
                        }
                    }

                    // Reference
                    if (memcmp(newSymbol->name, "set_mario_action", sizeof("set_mario_action")) == 0) {
                        symbol0 = newSymbol;
                    }
                }
            }
            fclose(f);
        }
        uintptr_t addr0 = (symbol0 ? ((uintptr_t) set_mario_action - symbol0->offset) : 0);

        // Unwind and print call stack
        void *stack[64];
#if IS_64_BIT
        s32 frames = CaptureStackBackTrace(6, 64, stack, NULL);
#else
        s32 frames = CaptureStackWalkBackTrace(ExceptionInfo->ContextRecord, 0, 64, stack);
#endif
        for (s32 i = 1, j = 0; i < frames && j < 15; ++i) {
            s32 y = 80 + j++ * 8;
            crash_handler_set_text( 8, y, 0xFF, 0xFF, 0x00, "0x%016llX", (PTR) stack[i]);
            crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, "%s", ": ");
            for (Symbol *symbol = symbols;; symbol = symbol->next) {
                if (symbol == NULL || symbol->next == NULL) {
                    if (j != 0) {
                        crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", "????");
                    }
                    break;
                } else {
                    uintptr_t offset = (uintptr_t) stack[i] - addr0;
                    if (symbol->next->offset > offset) {
                        crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", symbol->name);
                        crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, " + 0x%llX", (PTR)(offset - symbol->offset));
                        break;
                    }
                }
            }
        }
#elif __linux__
    void *trace[15];
    int traceSize = backtrace(trace, 15);

    if (traceSize > 0) {
        // Unwind and print call stack
        char **messages = backtrace_symbols(trace, traceSize);
        for (s32 i = 1, j = 0; i < traceSize && j < 15; ++i) {
            s32 y = 80 + j++ * 8;
            crash_handler_set_text( 8, y, 0xFF, 0xFF, 0x00, "0x%016llX", (u64) strtoul(strstr(messages[i], "[") + 1, NULL, 16));
            crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, "%s", ": ");

            // dladdr gives us function names if -rdynamic/-export-dynamic is set in compiler flags
            Dl_info info;
            if (dladdr(trace[i], &info) && info.dli_sname) {
                crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", info.dli_sname);
                crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, " + 0x%lX", trace[i] - info.dli_saddr);
            } else {
                crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", "????");
            }
        }
#endif
    } else {
        crash_handler_set_text(8, 116, 0x80, 0x80, 0x80, "%s", "Unable to unwind the call stack.");
    }

    // Info
    crash_handler_add_info_str(&pText, 340, -4 + (8 * 0), "Arch", ARCHITECTURE_STR);
    crash_handler_add_info_str(&pText, 340, -4 + (8 * 1), "OS", OS_NAME);

    // sounds
#if defined(WAPI_SDL2)
    if (SDL_WasInit(SDL_INIT_AUDIO) || SDL_InitSubSystem(SDL_INIT_AUDIO) == 0) {
        SDL_AudioSpec want, have;
        want.freq = 32000;
        want.format = AUDIO_S16SYS;
        want.channels = 1;
        want.samples = 0x200;
        want.callback = NULL;
        want.userdata = NULL;
        s32 device = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
        if (device) {
            SDL_PauseAudioDevice(device, 0);
        }
    }
#endif

    // Main loop
    while (true) {
#if defined(WAPI_SDL1) || defined(WAPI_SDL2)
        gfx_sdl.main_loop(crash_handler_produce_one_frame);
#elif defined(WAPI_DXGI)
        gfx_dxgi.main_loop(crash_handler_produce_one_frame);
#endif
    }
    exit(0);
}

__attribute__((constructor)) static void init_crash_handler() {
#ifdef _WIN32
    // Windows
    SetUnhandledExceptionFilter(crash_handler);
#elif __linux__
    // Linux
    struct sigaction linux_crash_handler;

    linux_crash_handler.sa_handler = (void *)crash_handler;
    sigemptyset(&linux_crash_handler.sa_mask);
    linux_crash_handler.sa_flags = SA_SIGINFO; // Get extra info about the crash

    sigaction(SIGBUS, &linux_crash_handler, NULL);
    sigaction(SIGFPE, &linux_crash_handler, NULL);
    sigaction(SIGILL, &linux_crash_handler, NULL);
    sigaction(SIGSEGV, &linux_crash_handler, NULL);
#endif
}

#endif
