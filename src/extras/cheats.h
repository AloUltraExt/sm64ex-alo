#ifndef CHEATS_H
#define CHEATS_H

#ifndef TARGET_N64
#include <stdbool.h>
#else
#define bool int
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

#endif // CHEATS_H
