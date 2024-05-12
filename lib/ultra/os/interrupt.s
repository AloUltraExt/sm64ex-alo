#include "PR/R4300.h"
#include "PR/os.h"
#include "sys/asm.h"
#include "sys/regdef.h"

#ifdef BBPLAYER
.set mips2
#endif

.text
.set noreorder
LEAF(__osDisableInt)
#if LIBULTRA_VERSION >= OS_VER_J
    la    t2, __OSGlobalIntMask
    lw    t3, (t2)
    andi  t3, SR_IMASK
#endif
    mfc0  t0, C0_SR
    and   t1, t0, ~SR_IE
    mtc0  t1, C0_SR
    andi  v0, t0, SR_IE
#if LIBULTRA_VERSION >= OS_VER_J
    lw    t0, (t2)
    andi  t0, SR_IMASK
    beq   t0, t3, ret
    la   t2, __osRunningThread
    lw    t1, 280(t2)
    andi  t2, t1, SR_IMASK
    and   t2, t0
    and   t1, ~SR_IMASK
    or    t1, t2
    and   t1, ~SR_IE
    mtc0  t1, $12
    nop
#endif
    nop
ret:
    jr ra
    nop
END(__osDisableInt)

LEAF(__osRestoreInt)
    mfc0  t0, C0_SR
    or    t0, t0, a0
    mtc0  t0, C0_SR
    nop
    nop
    jr    ra
    nop
END(__osRestoreInt)
