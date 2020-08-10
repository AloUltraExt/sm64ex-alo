#ifndef _CHEATS_H
#define _CHEATS_H

#ifndef TARGET_N64
#include <stdbool.h>
#endif

struct CheatList {
    bool         EnableCheats;
    bool         MoonJump;
    bool         GodMode;
    bool         InfiniteLives;
    bool         SuperSpeed;
    bool         Responsive;
    bool         ExitAnywhere;
    bool         HugeMario;
    bool         TinyMario;
};

extern struct CheatList Cheats;

#endif // _CHEATS_H
