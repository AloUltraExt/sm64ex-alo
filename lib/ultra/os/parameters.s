#include "PR/R4300.h"
#include "PR/os.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text

ABS(leoBootID, 0x800001a0)
ABS(osTvType, 0x80000300)
ABS(osRomType, 0x80000304)
ABS(osRomBase, 0x80000308)
ABS(osResetType, 0x8000030c)
ABS(osCicId, 0x80000310)
ABS(osVersion, 0x80000314)
ABS(osMemSize, 0x80000318)
ABS(osAppNMIBuffer, 0x8000031c)

#ifdef BBPLAYER
ABS(__osBbEepromAddress, 0x8000035c)
ABS(__osBbEepromSize, 0x80000360)
ABS(__osBbFlashAddress, 0x80000364)
ABS(__osBbFlashSize, 0x80000368)
ABS(__osBbSramAddress, 0x8000036c)
ABS(__osBbSramSize, 0x80000370)
ABS(__osBbPakAddress, 0x80000374)
ABS(__osBbPakSize, 0x80000384)
ABS(__osBbIsBb, 0x80000388)
ABS(__osBbHackFlags, 0x8000038c)
ABS(__osBbStashMagic, 0x80000390)
ABS(__osBbPakBindings, 0x80000394)
ABS(__osBbStateName, 0x800003a4)
ABS(__osBbStateDirty, 0x800003b4)
ABS(__osBbAuxDataLimit, 0x800003b8)
#endif
