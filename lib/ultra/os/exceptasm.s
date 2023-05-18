/* Enforce registers to be 64 bits on modern GCC */
.set gp=64

#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"
#include "PR/os.h"
#include "PR/rcp.h"
#include "PR/rdb.h"
#include "exceptasm.h"
#include "threadasm.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

#define KMC_CODE_ENTRY  0xBFF00014
#define KMC_WPORT       0xBFF08000
#define KMC_STAT        0xBFF08004

#ifdef BBPLAYER
#define XOR_VALUE 0xFFFFFFFF
#else
#define XOR_VALUE ~0
#endif

#if LIBULTRA_VERSION >= OS_VER_K
#define INT_TABLE(arg1, arg2) .word arg1, arg2
#else
#define INT_TABLE(arg1, arg2) .word arg1
#endif

#if LIBULTRA_VERSION <= OS_VER_D
#define IP_H(arg) panic
#else
#define IP_H(arg) arg
#endif

.rdata

#define REDISPATCH 0x00
#define SW1 0x04
#define SW2 0x08
#define RCP 0x0c
#define CART 0x10
#define PRENMI 0x14
#define IP6_HDLR 0x18
#define IP7_HDLR 0x1c
#define COUNTER 0x20

__osIntOffTable:
    .byte REDISPATCH
    .byte PRENMI
    .byte IP6_HDLR
    .byte IP6_HDLR
    .byte IP7_HDLR
    .byte IP7_HDLR
    .byte IP7_HDLR
    .byte IP7_HDLR
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte REDISPATCH
    .byte SW1
    .byte SW2
    .byte SW2
    .byte RCP
    .byte RCP
    .byte RCP
    .byte RCP
    .byte CART
    .byte CART
    .byte CART
    .byte CART
    .byte CART
    .byte CART
    .byte CART
    .byte CART

__osIntTable:
    .word redispatch, sw1, sw2, rcp, cart, prenmi, IP_H(IP6_Hdlr), IP_H(IP7_Hdlr), counter

.data

EXPORT(__osHwIntTable)
    INT_TABLE(0, 0)
    INT_TABLE(0, 0)
    INT_TABLE(0, 0)
    INT_TABLE(0, 0)
    INT_TABLE(0, 0)

#if LIBULTRA_VERSION > OS_VER_D
EXPORT(__osPiIntTable)
    INT_TABLE(0, 0)
#endif

#if LIBULTRA_VERSION <= OS_VER_D || !defined(_FINALROM)
__os_Kdebug_Pkt:
    .word 0

__osRdb_Mesg:
    .word 0
#endif

.text

LEAF(__osExceptionPreamble)
    la      k0, __osException
    jr      k0
END(__osExceptionPreamble)

LEAF(__osException)
    la      k0, __osThreadSave
    /* save AT */
    sd      AT, THREAD_GP1(k0)
    /* save sr */
STAY2(mfc0  k1, C0_SR)
    sw      k1, THREAD_SR(k0)
    /* clear interrupts */
    and     k1, k1, -4
STAY2(mtc0  k1, C0_SR)
    /* save other regs */
    sd      $8, THREAD_GP8(k0)
    sd      $9, THREAD_GP9(k0)
    sd      $10, THREAD_GP10(k0)
    /* say fp has not been used */
    sw      zero, THREAD_FP(k0)
#if LIBULTRA_VERSION <= OS_VER_D || !defined(_FINALROM)
STAY2(mfc0  t0, C0_CAUSE)
    andi    t1, t0, 0x7c
    li      t2, 0
    bne     t1, t2, savecontext
    and     t1, k1, t0
    andi    t2, t1, 0x4000
    beqz    t2, rdb_message
    li      t1, 1
    sw      t1, __os_Kdebug_Pkt
    b       gp_threads
rdb_message:
    andi    t2, t1, 0x2000
    beqz    t2, savecontext
    li      t1, 1
    sw      t1, __osRdb_Mesg
    b       gp_threads
savecontext:
    sw      zero, __os_Kdebug_Pkt
    sw      zero, __osRdb_Mesg
#else
savecontext:
#endif
    move    t0, k0
    lw      k0, __osRunningThread
    ld      t1, THREAD_GP1(t0)
    sd      t1, THREAD_GP1(k0)
    ld      t1, THREAD_SR(t0)
    sd      t1, THREAD_SR(k0)
    ld      t1, THREAD_GP8(t0)
    sd      t1, THREAD_GP8(k0)
    ld      t1, THREAD_GP9(t0)
    sd      t1, THREAD_GP9(k0)
    ld      t1, THREAD_GP10(t0)
    sd      t1, THREAD_GP10(k0)
gp_threads: /* Only referenced on 2.0D but required for instruction ordering to match */
    sd      $2, THREAD_GP2(k0)
    sd      $3, THREAD_GP3(k0)
    sd      $4, THREAD_GP4(k0)
    sd      $5, THREAD_GP5(k0)
    sd      $6, THREAD_GP6(k0)
    sd      $7, THREAD_GP7(k0)
    sd      $11, THREAD_GP11(k0)
    sd      $12, THREAD_GP12(k0)
    sd      $13, THREAD_GP13(k0)
    sd      $14, THREAD_GP14(k0)
    sd      $15, THREAD_GP15(k0)
    sd      $16, THREAD_GP16(k0)
    sd      $17, THREAD_GP17(k0)
    sd      $18, THREAD_GP18(k0)
    sd      $19, THREAD_GP19(k0)
    sd      $20, THREAD_GP20(k0)
    sd      $21, THREAD_GP21(k0)
    sd      $22, THREAD_GP22(k0)
    sd      $23, THREAD_GP23(k0)
    sd      $24, THREAD_GP24(k0)
    sd      $25, THREAD_GP25(k0)
    sd      $28, THREAD_GP28(k0)
    sd      $29, THREAD_GP29(k0)
    sd      $30, THREAD_GP30(k0)
    sd      $31, THREAD_GP31(k0)

    mflo    t0
    sd      t0, THREAD_LO(k0)
    mfhi    t0
    sd      t0, THREAD_HI(k0)
#if LIBULTRA_VERSION > OS_VER_D
    lw      k1, THREAD_SR(k0)
    andi    t1, k1, SR_IMASK
    beqz    t1, savercp

/*if any interrupts are enabled*/
    la      t0, __OSGlobalIntMask
    lw      t0, 0(t0)
#if LIBULTRA_VERSION <= OS_VER_F
    xor     t0, t0, XOR_VALUE /* not except not using not */
    andi    t0, t0, SR_IMASK
    or      t1, t1, t0
    and     k1, k1, ~SR_IMASK
    or      k1, k1, t1
    sw      k1, THREAD_SR(k0)
#else
    xor     t2, t0, XOR_VALUE /* not except not using not */
    andi    t2, t2, SR_IMASK
    or      ta0, t1, t2
    and     t3, k1, ~SR_IMASK
    or      t3, t3, ta0
    sw      t3, THREAD_SR(k0)
    andi    t0, t0, SR_IMASK
    and     t1, t1, t0
    and     k1, k1, ~SR_IMASK
    or      k1, k1, t1
#endif
#endif
savercp:

#if LIBULTRA_VERSION > OS_VER_D
    lw      t1, PHYS_TO_K1(MI_INTR_MASK_REG)
    beqz    t1, endrcp

    la      t0, __OSGlobalIntMask
    lw      t0, 0(t0)

    srl     t0, t0, 0x10
    xor     t0, t0, XOR_VALUE
    andi    t0, t0, 0x3f
    lw      ta0, THREAD_RCP(k0)
    and     t0, t0, ta0
    or      t1, t1, t0
endrcp:
    sw      t1, THREAD_RCP(k0)
#endif
STAY2(mfc0  t0, C0_EPC)
    sw      t0, THREAD_PC(k0)
    lw      t0, THREAD_FP(k0)
    beqz    t0, 1f
STAY2(cfc1    t0, fcr31)
    NOP
    sw      t0, THREAD_FPCSR(k0)
    sdc1    $f0, THREAD_FP0(k0)
    sdc1    $f2, THREAD_FP2(k0)
    sdc1    $f4, THREAD_FP4(k0)
    sdc1    $f6, THREAD_FP6(k0)
    sdc1    $f8, THREAD_FP8(k0)
    sdc1    $f10, THREAD_FP10(k0)
    sdc1    $f12, THREAD_FP12(k0)
    sdc1    $f14, THREAD_FP14(k0)
    sdc1    $f16, THREAD_FP16(k0)
    sdc1    $f18, THREAD_FP18(k0)
    sdc1    $f20, THREAD_FP20(k0)
    sdc1    $f22, THREAD_FP22(k0)
    sdc1    $f24, THREAD_FP24(k0)
    sdc1    $f26, THREAD_FP26(k0)
    sdc1    $f28, THREAD_FP28(k0)
    sdc1    $f30, THREAD_FP30(k0)
1:
STAY2(mfc0  t0, C0_CAUSE)
    sw    t0, THREAD_CAUSE(k0)
#if LIBULTRA_VERSION <= OS_VER_D
    lw      t1, PHYS_TO_K1(MI_INTR_MASK_REG)
    sw      t1, THREAD_RCP(k0)
#endif
.set noreorder
    li      t1, OS_STATE_RUNNABLE
    sh      t1, THREAD_STATE(k0)
.set reorder
#if LIBULTRA_VERSION <= OS_VER_D || !defined(_FINALROM)
    lw      t1, __os_Kdebug_Pkt
    beqz    t1, no_kdebug
    la      t2, RDB_WRITE_INTR_REG
    sw      zero, (t2)
    lw      a0, K2BASE
    jal     kdebugserver
    b       __osDispatchThreadSave
no_kdebug:
    lw      t1, __osRdb_Mesg
    beqz    t1, no_rdb_mesg
    la      t2, RDB_READ_INTR_REG
    sw      zero, (t2)
    lw      t1, __osRdbSendMessage
    beqz    t1, rdb_write
    li      a0, 120
    jal     send_mesg
rdb_write:
    lw      t1, __osRdbWriteOK
    addi    t1, t1, 1
    sw      t1, __osRdbWriteOK
    b       __osDispatchThreadSave
no_rdb_mesg:
#endif
    andi    t1, t0, CAUSE_EXCMASK
    li      t2, EXC_BREAK
    beq     t1, t2, handle_break

    li      t2, EXC_CPU
    beq     t1, t2, handle_CpU

    li      t2, EXC_INT
    bne     t1, t2, panic

handle_interrupt:
    and     s0, k1, t0
next_interrupt:
    andi    t1, s0, SR_IMASK
    srl     t2, t1, 0xc
    bnez    t2, 1f

    srl     t2, t1, SR_IMASKSHIFT
    addi    t2, t2, 16
1:

    lbu     t2, __osIntOffTable(t2)

    lw      t2, __osIntTable(t2)
    jr      t2
#if LIBULTRA_VERSION > OS_VER_D
IP6_Hdlr:
    and     s0, s0, ~CAUSE_IP6
    b       next_interrupt

IP7_Hdlr:
    and     s0, s0, ~CAUSE_IP7
    b       next_interrupt
#endif
counter:
STAY2(mfc0  t1, C0_COMPARE)
STAY2(mtc0  t1, C0_COMPARE)
    li      a0, MESG(OS_EVENT_COUNTER)
    jal     send_mesg
    and     s0, s0, ~CAUSE_IP8
    b       next_interrupt

cart:
#if LIBULTRA_VERSION > OS_VER_D
    and     s0, s0, ~CAUSE_IP4
#endif
#if LIBULTRA_VERSION >= OS_VER_K
    la      t1, __osHwIntTable
    add     t1, HWINTR_SIZE
    lw      t2, HWINTR_CALLBACK(t1)

    beqz    t2, 1f

    lw      sp, HWINTR_SP(t1)
#else
	li      t2, HWINTR_SIZE
	lw      t2, __osHwIntTable(t2)
#if LIBULTRA_VERSION >= OS_VER_F
	la      sp, leoDiskStack
	li      a0, MESG(OS_EVENT_CART)

    addiu   sp, sp, OS_LEO_STACKSIZE-16
#endif
	beqz    t2, 1f
#endif
    jalr    t2
#if LIBULTRA_VERSION >= OS_VER_H && LIBULTRA_VERSION < OS_VER_K
    li      a0, MESG(OS_EVENT_CART)
#endif
#if LIBULTRA_VERSION > OS_VER_D
    beqz    v0, 1f
    b       redispatch
#endif
1:
#ifndef BBPLAYER
#if LIBULTRA_VERSION <= OS_VER_D
    li      a0, MESG(OS_EVENT_CART)
#endif
    jal     send_mesg
#else
    lw      s1, PHYS_TO_K1(MI_38_REG)

flash:
    andi    t1, s1, 0x40
    beqz    t1, flashx

    andi    s1, s1, 0x3f80
    li      t1, 0
    sw      t1, PHYS_TO_K1(PI_48_REG)
    li      a0, MESG(OS_EVENT_FLASH)
    jal     send_mesg
flashx:

md:
    andi    t1, s1, 0x2000
    beqz    t1, mdx

    andi    s1, s1, 0x1fc0
    li      t1, 0x2000
    sw      t1, PHYS_TO_K1(MI_38_REG)
    li      a0, MESG(OS_EVENT_MD)
    jal     send_mesg
mdx:

aes:
    andi    t1, s1, 0x80
    beqz    t1, aesx

    andi    s1, s1, 0x3f40
    li      t1, 0x4000
    sw      t1, PHYS_TO_K1(MI_3C_REG)
    li      a0, MESG(OS_EVENT_AES)
    jal     send_mesg
aesx:

ide:
    andi    t1, s1, 0x100
    beqz    t1, idex

    andi    s1, s1, 0x3ec0
    li      t1, 0x10000
    sw      t1, PHYS_TO_K1(MI_3C_REG)
    li      a0, MESG(OS_EVENT_IDE)
    jal     send_mesg
idex:

pi_err:
    andi    t1, s1, 0x200
    beqz    t1, pi_errx

    andi    s1, s1, 0x3dc0
    li      t1, 0x40000
    sw      t1, PHYS_TO_K1(MI_3C_REG)
    li      a0, MESG(OS_EVENT_PI_ERR)
    jal     send_mesg
pi_errx:

usb0:
    andi    t1, s1,0x400
    beqz    t1, usb0x

    andi    s1, s1, 0x3bc0
    li      t1, 0x100000
    sw      t1, PHYS_TO_K1(MI_3C_REG)
    li      a0, MESG(OS_EVENT_USB0)
    jal     send_mesg
usb0x:

usb1:
    andi    t1, s1, 0x800
    beqz    t1, usb1x

    andi    s1, s1, 0x37c0
    li      t1, 0x400000
    sw      t1, PHYS_TO_K1(MI_3C_REG)
    li      a0, MESG(OS_EVENT_USB1)
    jal     send_mesg
usb1x:

#endif
#if LIBULTRA_VERSION <= OS_VER_D
    and     s0, s0, ~CAUSE_IP4
#endif
    b       next_interrupt

rcp:
    lw      s1, PHYS_TO_K1(MI_INTR_REG)
#if LIBULTRA_VERSION > OS_VER_D
    la      t0, __OSGlobalIntMask
    lw      t0, (t0)
    srl     t0, t0, 0x10
    and     s1, s1, t0
#else
    andi    s1, s1, 0x3f
#endif
    andi    t1, s1, MI_INTR_SP
    beqz    t1, vi

    andi    s1, s1, 0x3e
    lw      ta0, PHYS_TO_K1(SP_STATUS_REG)
#if LIBULTRA_VERSION >= OS_VER_I
    li      t1, (SP_CLR_INTR | SP_CLR_SIG3)
#else
    li      t1, (SP_CLR_INTR)
#endif
    sw      t1, PHYS_TO_K1(SP_STATUS_REG)
    andi    ta0, ta0, 0x300
    beqz    ta0, sp_other_break

    li      a0, MESG(OS_EVENT_SP)
    jal     send_mesg

    beqz    s1, NoMoreRcpInts

    b       vi

sp_other_break:
    li      a0, MESG(OS_EVENT_SP_BREAK)
    jal     send_mesg

    beqz    s1, NoMoreRcpInts

vi:
    andi    t1, s1, 0x8
    beqz    t1, ai

    andi    s1, s1, 0x37

    sw      zero, PHYS_TO_K1(VI_CURRENT_REG)
    li      a0, MESG(OS_EVENT_VI)
    jal     send_mesg
    beqz    s1, NoMoreRcpInts

ai:
    andi    t1, s1, 0x4
    beqz    t1, si

    andi    s1, s1, 0x3b

    li      t1, 1
    sw      t1, PHYS_TO_K1(AI_STATUS_REG)

    li      a0, MESG(OS_EVENT_AI)
    jal     send_mesg
    beqz    s1, NoMoreRcpInts

si:
    andi    t1, s1, 0x2
    beqz    t1, pi

    andi    s1, s1, 0x3d
    /* any write clears interrupts */
    sw      zero, PHYS_TO_K1(SI_STATUS_REG)
    li      a0, MESG(OS_EVENT_SI)
    jal     send_mesg
    beqz    s1, NoMoreRcpInts

pi:
    andi    t1, s1, 0x10
    beqz    t1, dp

    andi    s1, s1, 0x2f

    li      t1, PI_STATUS_CLR_INTR
    sw      t1, PHYS_TO_K1(PI_STATUS_REG)
#if LIBULTRA_VERSION >= OS_VER_K
    la      t1, __osPiIntTable
    lw      t2, (t1)
    beqz    t2, 1f

    lw      sp, 4(t1)
    move    a0, v0
    jalr    t2

    bnez    v0, 2f
#endif
1:
    li      a0, MESG(OS_EVENT_PI)
    jal     send_mesg
2:
    beqz    s1, NoMoreRcpInts

dp:
    andi    t1, s1, 0x20
    beqz    t1, NoMoreRcpInts

    andi    s1, s1, 0x1f

    li      t1, MI_CLR_DP_INTR
    sw      t1, PHYS_TO_K1(MI_INIT_MODE_REG)

    li      a0, MESG(OS_EVENT_DP)
    jal     send_mesg

NoMoreRcpInts:
    and     s0, s0, ~CAUSE_IP3
    b       next_interrupt

prenmi:
    lw      k1, THREAD_SR(k0)

    and     k1, k1, ~CAUSE_IP5
    sw      k1, THREAD_SR(k0)
    la      t1, __osShutdown
    lw      t2, 0(t1)
    beqz    t2, firstnmi

    and     s0, s0, ~CAUSE_IP5
    b       redispatch

firstnmi:
    li      t2, 1
    sw      t2, 0(t1) /* __osShutdown */
    li      a0, MESG(OS_EVENT_PRENMI)
    jal     send_mesg

    and     s0, s0, ~CAUSE_IP5
    lw      t2, __osRunQueue
    lw      k1, THREAD_SR(t2)
    and     k1, k1, ~CAUSE_IP5
    sw      k1, THREAD_SR(t2)
    b       redispatch

sw2:
    and     t0, t0, ~CAUSE_SW2
STAY2(mtc0  t0, C0_CAUSE)

    li      a0, MESG(OS_EVENT_SW2)
    jal     send_mesg

    and     s0, s0, ~CAUSE_SW2
    b       next_interrupt

sw1:
    and     t0, t0, ~CAUSE_SW1
STAY2(mtc0  t0, C0_CAUSE)

    li      a0, MESG(OS_EVENT_SW1)
    jal     send_mesg

    and     s0, s0, ~CAUSE_SW1
    b       next_interrupt

handle_break:
    li      t1, OS_FLAG_CPU_BREAK
    sh      t1, THREAD_FLAGS(k0)
    li      a0, MESG(OS_EVENT_CPU_BREAK)
    jal     send_mesg
    b       redispatch

redispatch:
    lw      t1, THREAD_PRI(k0)
    lw      t2, __osRunQueue
    lw      t3, THREAD_PRI(t2)

    bge     t1, t3, enqueueRunning

    move    a1, k0
    la      a0, __osRunQueue

    jal     __osEnqueueThread

    j       __osDispatchThread

enqueueRunning:
    la      t1, __osRunQueue
    lw      t2, MQ_MTQUEUE(t1)
    sw      t2, THREAD_NEXT(k0)
    sw      k0, MQ_MTQUEUE(t1)
    j       __osDispatchThread
panic:
    sw      k0, __osFaultedThread
    li      t1, OS_STATE_STOPPED
    sh      t1, THREAD_STATE(k0)
    li      t1, OS_FLAG_FAULT
    sh      t1, THREAD_FLAGS(k0)

STAY2(mfc0  t2, C0_BADVADDR)

    sw      t2, THREAD_BADVADDR(k0)

    li      a0, MESG(OS_EVENT_FAULT)
    jal     send_mesg
    j       __osDispatchThread
END(__osException)

LEAF(send_mesg)
    move    s2, ra
    la      t2, __osEventStateTab
    addu    t2, t2, a0
    lw      t1, OS_EVENTSTATE_MESSAGE_QUEUE(t2)
    beqz    t1, send_done

    lw      t3, MQ_VALIDCOUNT(t1)
    lw      ta0, MQ_MSGCOUNT(t1)

    bge     t3, ta0, send_done

    lw      ta1, MQ_FIRST(t1)
    addu    ta1, ta1, t3

    rem     ta1, ta1, ta0
    lw      ta0, MQ_MSG(t1)
    mul     ta1, ta1, 4
    addu    ta0, ta0, ta1
    lw      ta1, OS_EVENTSTATE_MESSAGE(t2)
    sw      ta1, 0(ta0) /* msg[ta1] = */
    addiu   t2, t3, 1
    sw      t2, MQ_VALIDCOUNT(t1)
    lw      t2, MQ_MTQUEUE(t1)
    lw      t3, THREAD_NEXT(t2)
    beqz    t3, send_done

    move    a0, t1
    jal     __osPopThread

    move    t2, v0

    move    a1, t2
    la      a0, __osRunQueue
    jal     __osEnqueueThread
send_done:
    jr      s2
END(send_mesg)

LEAF(handle_CpU) /* coprocessor error */
    and     t1, t0, CAUSE_CEMASK
    srl     t1, t1, CAUSE_CESHIFT
    li      t2, 1 /* cp1 error */
    bne     t1, t2, panic

    /* enable cp1 (fpu) for this thread */
    li      t1, 1
    sw      t1, THREAD_FP(k0)
    lw      k1, THREAD_SR(k0)
    or      k1, k1, SR_CU1
    sw      k1, THREAD_SR(k0)
    b       enqueueRunning
END(handle_CpU)

LEAF(__osEnqueueAndYield)
    lw      a1, __osRunningThread
STAY2(mfc0  t0, C0_SR)
    ori     t0, t0, SR_EXL
    sw      t0, THREAD_SR(a1)
    sd      s0, THREAD_GP16(a1)
    sd      s1, THREAD_GP17(a1)
    sd      s2, THREAD_GP18(a1)
    sd      s3, THREAD_GP19(a1)
    sd      s4, THREAD_GP20(a1)
    sd      s5, THREAD_GP21(a1)
    sd      s6, THREAD_GP22(a1)
    sd      s7, THREAD_GP23(a1)
    sd      gp, THREAD_GP28(a1)
    sd      sp, THREAD_GP29(a1)
    sd      s8, THREAD_GP30(a1)
    sd      ra, THREAD_GP31(a1)
    sw      ra, THREAD_PC(a1)
    lw      k1, THREAD_FP(a1)
    beqz    k1, 1f
    cfc1    k1, fcr31
    sw      k1, THREAD_FPCSR(a1)
    sdc1    $f20, THREAD_FP20(a1)
    sdc1    $f22, THREAD_FP22(a1)
    sdc1    $f24, THREAD_FP24(a1)
    sdc1    $f26, THREAD_FP26(a1)
    sdc1    $f28, THREAD_FP28(a1)
    sdc1    $f30, THREAD_FP30(a1)
1:
#if LIBULTRA_VERSION > OS_VER_D
    lw      k1, THREAD_SR(a1)
    andi    t1, k1, SR_IMASK
    beqz    t1, 2f

    la      t0, __OSGlobalIntMask
    lw      t0, 0(t0)
    xor     t0, t0, XOR_VALUE
    andi    t0, t0, SR_IMASK
    or      t1, t1, t0
    and     k1, k1, ~SR_IMASK
    or      k1, k1, t1
    sw      k1, THREAD_SR(a1)
2:
#endif
    lw      k1, PHYS_TO_K1(MI_INTR_MASK_REG)
#if LIBULTRA_VERSION > OS_VER_D
    beqz    k1, 3f

    la      k0, __OSGlobalIntMask
    lw      k0, 0(k0)

    srl     k0, k0, 0x10
    xor     k0, k0, XOR_VALUE
    andi    k0, k0, 0x3f
    lw      t0, THREAD_RCP(a1)
    and     k0, k0, t0
    or      k1, k1, k0
3:
#endif
    sw      k1, THREAD_RCP(a1)
    beqz    a0, noEnqueue
    jal     __osEnqueueThread
noEnqueue:
    j       __osDispatchThread
END(__osEnqueueAndYield)

/*__osEnqueueThread(OSThread **, OSThread *)*/
LEAF(__osEnqueueThread)
    move    t9, a0
    lw      t8, 0(a0)
    lw      ta3, THREAD_PRI(a1)
    lw      ta2, THREAD_PRI(t8)
    blt     ta2, ta3, 1f
2:
    move    t9, t8
    lw      t8, THREAD_NEXT(t8)
    lw      ta2, THREAD_PRI(t8)
    bge     ta2, ta3, 2b
1:
    lw      t8, THREAD_NEXT(t9)
    sw      t8, THREAD_NEXT(a1)
    sw      a1, THREAD_NEXT(t9)
    sw      a0, THREAD_QUEUE(a1)
    jr      ra
END(__osEnqueueThread)

LEAF(__osPopThread)
    lw      v0, 0(a0) /* a0 is OSThread** */
    lw      t9, THREAD_NEXT(v0)
    sw      t9, 0(a0)
    jr      ra
END(__osPopThread)

#if LIBULTRA_VERSION >= OS_VER_K
LEAF(__osNop)
    jr      ra
END(__osNop)
#endif

LEAF(__osDispatchThread)
    la      a0, __osRunQueue
    jal     __osPopThread
    sw      v0, __osRunningThread
    li      t0, OS_STATE_RUNNING
    sh      t0, THREAD_STATE(v0)
    move    k0, v0
__osDispatchThreadSave:
#if LIBULTRA_VERSION > OS_VER_D
    lw      k1, THREAD_SR(k0)
    la      t0, __OSGlobalIntMask
    lw      t0, 0(t0)
    andi    t0, t0, SR_IMASK
    andi    t1, k1, SR_IMASK
    and     t1, t1, t0
    and     k1, k1, ~SR_IMASK
    or      k1, k1, t1
STAY2(mtc0  k1, C0_SR)
#endif
    ld      AT, THREAD_GP1(k0)
    ld      $2, THREAD_GP2(k0)
    ld      $3, THREAD_GP3(k0)
    ld      $4, THREAD_GP4(k0)
    ld      $5, THREAD_GP5(k0)
    ld      $6, THREAD_GP6(k0)
    ld      $7, THREAD_GP7(k0)
    ld      $8, THREAD_GP8(k0)
    ld      $9, THREAD_GP9(k0)
    ld      $10, THREAD_GP10(k0)
    ld      $11, THREAD_GP11(k0)
    ld      $12, THREAD_GP12(k0)
    ld      $13, THREAD_GP13(k0)
    ld      $14, THREAD_GP14(k0)
    ld      $15, THREAD_GP15(k0)
    ld      $16, THREAD_GP16(k0)
    ld      $17, THREAD_GP17(k0)
    ld      $18, THREAD_GP18(k0)
    ld      $19, THREAD_GP19(k0)
    ld      $20, THREAD_GP20(k0)
    ld      $21, THREAD_GP21(k0)
    ld      $22, THREAD_GP22(k0)
    ld      $23, THREAD_GP23(k0)
    ld      $24, THREAD_GP24(k0)
    ld      $25, THREAD_GP25(k0)
    ld      $28, THREAD_GP28(k0)
    ld      $29, THREAD_GP29(k0)
    ld      $30, THREAD_GP30(k0)
    ld      $31, THREAD_GP31(k0)
    ld      k1, THREAD_LO(k0)
    mtlo    k1
    ld      k1, THREAD_HI(k0)
    mthi    k1
    lw      k1, THREAD_PC(k0)
STAY2(mtc0  k1, C0_EPC)
#if LIBULTRA_VERSION <= OS_VER_D
    lw      k1, THREAD_SR(k0)
STAY2(mtc0  k1, C0_SR)
#endif
    lw      k1, THREAD_FP(k0)
    beqz    k1, 1f
    lw      k1, THREAD_FPCSR(k0)
STAY2(ctc1  k1, fcr31)
    ldc1    $f0, THREAD_FP0(k0)
    ldc1    $f2, THREAD_FP2(k0)
    ldc1    $f4, THREAD_FP4(k0)
    ldc1    $f6, THREAD_FP6(k0)
    ldc1    $f8, THREAD_FP8(k0)
    ldc1    $f10, THREAD_FP10(k0)
    ldc1    $f12, THREAD_FP12(k0)
    ldc1    $f14, THREAD_FP14(k0)
    ldc1    $f16, THREAD_FP16(k0)
    ldc1    $f18, THREAD_FP18(k0)
    ldc1    $f20, THREAD_FP20(k0)
    ldc1    $f22, THREAD_FP22(k0)
    ldc1    $f24, THREAD_FP24(k0)
    ldc1    $f26, THREAD_FP26(k0)
    ldc1    $f28, THREAD_FP28(k0)
    ldc1    $f30, THREAD_FP30(k0)
1:
.set noreorder
    lw      k1, THREAD_RCP(k0)
#if LIBULTRA_VERSION > OS_VER_D
    la      k0, __OSGlobalIntMask
    lw      k0, 0(k0)
    srl     k0, k0, 0x10
    and     k1, k1, k0
#endif
    sll     k1, k1, 0x1
    la      k0, __osRcpImTable
    addu    k1, k1, k0
    lhu     k1, 0(k1)
    la      k0, PHYS_TO_K1(MI_INTR_MASK_REG)
    sw      k1, 0(k0)   
    nop
    nop
    nop
    nop
    eret
.set reorder
END(__osDispatchThread)

LEAF(__osCleanupThread)  
    move    a0, zero
    jal     osDestroyThread
END(__osCleanupThread)
