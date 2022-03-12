#ifndef _CLIOPTS_H
#define _CLIOPTS_H

#ifdef COMMAND_LINE_OPTIONS

#include "platform.h"

struct PCCLIOptions  {
    unsigned int SkipIntro;
    unsigned int FullScreen;
    unsigned int LevelSelect;
    unsigned int LevelNumOverride;
    unsigned int LevelActOverride;
    unsigned int Profiler;
    unsigned int Debug;
    unsigned int PoolSize;
    char ConfigFile[SYS_MAX_PATH];
    char SavePath[SYS_MAX_PATH];
    char GameDir[SYS_MAX_PATH];
};

extern struct PCCLIOptions gCLIOpts;

void parse_cli_opts(int argc, char* argv[]);
void set_cli_opts(void);

#endif

#endif // _CLIOPTS_H
