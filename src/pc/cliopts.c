#ifdef COMMAND_LINE_OPTIONS

#include "cliopts.h"
#include "configfile.h"
#include "pc_main.h"
#include "platform.h"
#include "macros.h"


#ifdef CHEATS_ACTIONS
#include "extras/cheats.h"
#endif

#include <strings.h>
#include <stdlib.h>
#define __NO_MINGW_LFS //Mysterious error in MinGW.org stdio.h
#include <stdio.h>
#include <string.h>

struct PCCLIOptions gCLIOpts = { 0 };

static void print_help(void) {
    printf("Super Mario 64 PC Port\n");
#ifdef CHEATS_ACTIONS
    printf("%-20s\tEnables the cheat menu.\n", "--cheats");
#endif
    printf("%-20s\tSaves the configuration file as CONFIGNAME.\n", "--configfile CONFIGNAME");
    printf("%-20s\tSets additional data directory name (only 'res' is used by default).\n", "--gamedir DIRNAME");
    printf("%-20s\tOverrides the default save/config path ('!' expands to executable path).\n", "--savepath SAVEPATH");
    printf("%-20s\tStarts the game in full screen mode.\n", "--fullscreen");
    printf("%-20s\tSkips the Peach and Castle intro when starting a new game.\n", "--skip-intro");
    printf("%-20s\tStarts the game in windowed mode.\n", "--windowed");
    printf("%-20s\tOffers the user a level select menu.\n", "--levelselect");
    printf("%-20s\tEnables profiler bar on the screen bottom (Not functional).\n", "--profiler");
    printf("%-20s\tEnables simple debug display.\n", "--debug");
}

static inline int arg_string(const char *name, const char *value, char *target) {
    const unsigned int arglen = strlen(value);
    if (arglen >= SYS_MAX_PATH) {
        fprintf(stderr, "Supplied value for `%s` is too long.\n", name);
        return 0;
    }
    strncpy(target, value, arglen);
    target[arglen] = '\0';
    return 1;
}

static inline int arg_uint(UNUSED const char *name, const char *value, unsigned int *target) {
    const unsigned long int v = strtoul(value, NULL, 0);
    *target = v;
    return 1;
}

void set_cli_opts(void) {
    // might be redundant
    extern s16 gSkipGameIntro;
    extern s16 gDebugLevelSelect;
    extern s16 gShowProfiler;
    extern s16 gShowDebugText;
    if (gCLIOpts.SkipIntro) gSkipGameIntro = TRUE;
    if (gCLIOpts.LevelSelect) gDebugLevelSelect = TRUE;
    if (gCLIOpts.Profiler) gShowProfiler = TRUE;
    if (gCLIOpts.Debug) gShowDebugText = TRUE;
}

void parse_cli_opts(int argc, char* argv[]) {
    // Initialize options with false values.
    memset(&gCLIOpts, 0, sizeof(gCLIOpts));

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--skip-intro") == 0) // Skip Peach Intro
            gCLIOpts.SkipIntro = true;

        else if (strcmp(argv[i], "--fullscreen") == 0) // Open game in fullscreen
            gCLIOpts.FullScreen = 1;

        else if (strcmp(argv[i], "--windowed") == 0) // Open game in windowed mode
            gCLIOpts.FullScreen = 2;

        else if (strcmp(argv[i], "--levelselect") == 0) // Enable debug level select
            gCLIOpts.LevelSelect = 1;

        else if (strcmp(argv[i], "--profiler") == 0) // Enable N64 Profiler (not functional)
            gCLIOpts.Profiler = 1;

        else if (strcmp(argv[i], "--debug") == 0) // Enable simple debug info
            gCLIOpts.Debug = 1;

#ifdef CHEATS_ACTIONS
        else if (strcmp(argv[i], "--cheats") == 0) // Enable cheats menu
            Cheats.EnableCheats = true;
#endif

#ifndef USE_SYSTEM_MALLOC
        else if (strcmp(argv[i], "--poolsize") == 0) // Main pool size
            arg_uint("--poolsize", argv[++i], &gCLIOpts.PoolSize);
#endif

        else if (strcmp(argv[i], "--configfile") == 0 && (i + 1) < argc)
            arg_string("--configfile", argv[++i], gCLIOpts.ConfigFile);

        else if (strcmp(argv[i], "--gamedir") == 0 && (i + 1) < argc)
            arg_string("--gamedir", argv[++i], gCLIOpts.GameDir);

        else if (strcmp(argv[i], "--savepath") == 0 && (i + 1) < argc)
            arg_string("--savepath", argv[++i], gCLIOpts.SavePath);

        // Print help
        else if (strcmp(argv[i], "--help") == 0) {
            print_help();
            game_exit();
        }
    }
}

#endif
