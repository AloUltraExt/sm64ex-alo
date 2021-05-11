#include <PR/ultratypes.h>

#include "macros.h"
#include "surface_terrains.h"
#include "types.h"
#include "make_const_nonconst.h"

#include "springboard/model.inc.c"
#ifdef PORT_MOP_OBJS
#include "src/extras/mop/actors/Beta_Trampoline_MOP/collision.inc.c"
#else
#include "springboard/collision.inc.c"
#endif
UNUSED static const u64 binid_0 = 0;

#include "capswitch/model.inc.c"
#include "capswitch/collision.inc.c"
UNUSED static const u64 binid_1 = 1;
