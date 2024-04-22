#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#ifndef TARGET_N64
#include <stdbool.h>
#else
#define bool int
#endif

#include "config.h"

#define CONFIGFILE_DEFAULT "sm64dsr_config.txt"

#define MAX_BINDS  3
#define MAX_VOLUME 127

typedef struct {
#if defined(TARGET_PORT_CONSOLE) && !defined(WAPI_SDL2)
    bool reset;
    bool settings_changed;
#else
    unsigned int x, y, w, h;
    bool vsync;
    bool reset;
    bool fullscreen;
    bool exiting_fullscreen;
    bool settings_changed;
#endif
} ConfigWindow;

extern ConfigWindow configWindow;
extern unsigned int configFiltering;
extern unsigned int configMasterVolume;
extern unsigned int configMusicVolume;
extern unsigned int configSfxVolume;
extern unsigned int configEnvVolume;
extern unsigned int configKeyA[];
extern unsigned int configKeyB[];
extern unsigned int configKeyX[];
extern unsigned int configKeyY[];
extern unsigned int configKeyStart[];
extern unsigned int configKeyL[];
extern unsigned int configKeyR[];
extern unsigned int configKeyZL[];
extern unsigned int configKeyZR[];
extern unsigned int configKeyCUp[];
extern unsigned int configKeyCDown[];
extern unsigned int configKeyCLeft[];
extern unsigned int configKeyCRight[];
extern unsigned int configKeyDUp[];
extern unsigned int configKeyDDown[];
extern unsigned int configKeyDLeft[];
extern unsigned int configKeyDRight[];
extern unsigned int configKeyStickUp[];
extern unsigned int configKeyStickDown[];
extern unsigned int configKeyStickLeft[];
extern unsigned int configKeyStickRight[];
extern unsigned int configStickDeadzone;
extern unsigned int configRumbleStrength;
#ifdef EXTERNAL_DATA
extern bool         configPrecacheRes;
#endif

extern bool         configHUD;
extern bool         configWallslide;
extern bool         configDive;
extern unsigned int configDash;
extern bool         configSkipIntro;
#ifdef DISCORDRPC
extern bool         configDiscordRPC;
#endif

void configfile_load(const char *filename);
void configfile_save(const char *filename);
const char *configfile_name(void);

#endif
