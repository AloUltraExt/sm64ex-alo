#include "PR/os_internal.h"
#include "PR/rcp.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

void osViSetMode(OSViMode *modep) {
    register u32 saveMask = __osDisableInt();

#ifdef BBPLAYER
    if (__osBbIsBb) {
        modep->comRegs.ctrl &= ~VI_CTRL_PIXEL_ADV_2;
    }
#endif

    __osViNext->modep = modep;
    __osViNext->state = VI_STATE_MODE_UPDATED;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;
    __osRestoreInt(saveMask);
}
