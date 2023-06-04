#include "sys/asm.h"
#include "sys/regdef.h"
#include "PR/R4300.h"
#include "PR/ultratypes.h"
#include "PR/bcp.h"
#include "PR/rcp.h"

#ifdef BBPLAYER

#define SK_FUNC(name, num)              \
    LEAF(name)                         ;\
    .set noreorder                     ;\
        li  v0, num                    ;\
        li  t0, PHYS_TO_K1(0x04300014) ;\
        lw  t1, (t0)                   ;\
        nop                            ;\
        jr ra                          ;\
         nop                           ;\
    .set reorder                       ;\
    END(name)

SK_FUNC(skGetId,                0)
SK_FUNC(skLaunchSetup,          1)
SK_FUNC(skLaunch,               2)
SK_FUNC(skRecryptListValid,     3)
SK_FUNC(skRecryptBegin,         4)
SK_FUNC(skRecryptData,          5)
SK_FUNC(skRecryptComputeState,  6)
SK_FUNC(skRecryptEnd,           7)
SK_FUNC(skSignHash,             8)
SK_FUNC(skVerifyHash,           9)
SK_FUNC(skGetConsumption,       10)
SK_FUNC(skAdvanceTicketWindow,  11)
SK_FUNC(skSetLimit,             12)
SK_FUNC(skExit,                 13)
SK_FUNC(skKeepAlive,            14)
SK_FUNC(skGetRandomKeyData,     15)
SK_FUNC(skDumpVirage,           16)
SK_FUNC(skTest2,                17)
SK_FUNC(skTest3,                18)
SK_FUNC(skResetWindow,          19)
SK_FUNC(skValidateRls,          20)

#endif
