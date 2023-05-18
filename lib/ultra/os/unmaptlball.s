#include "PR/R4300.h"
#include "PR/os.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
LEAF(osUnmapTLBAll)
    mfc0 t0, C0_ENTRYHI
#if LIBULTRA_VERSION >= OS_VER_I
    li t1, NTLBENTRIES-1 /* last reserved for rdb */
#else
    li t1, NTLBENTRIES
#endif
    li t2, KUSIZE
    mtc0 t2, C0_ENTRYHI
    mtc0 zero, C0_ENTRYLO0
    mtc0 zero, C0_ENTRYLO1
1:
    mtc0 t1, C0_INX
    nop
    tlbwi
    nop
    nop
    addi t1, t1,-1
#if LIBULTRA_VERSION >= OS_VER_I
    bgez t1, 1b
#else
    bnezl t1, 1b
#endif
    nop
    mtc0 t0, C0_ENTRYHI
    jr ra
    nop
END(osUnmapTLBAll)
