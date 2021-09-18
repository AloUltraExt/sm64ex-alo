#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#ifndef TARGET_N64
#include <stdbool.h>
#else
#define bool int
#endif

#define CONFIGFILE_DEFAULT "sm64config.txt"

#define MAX_BINDS  3
#define MAX_VOLUME 127

typedef struct {
#ifdef TARGET_WII_U
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
extern unsigned int configKeyStart[];
extern unsigned int configKeyL[];
extern unsigned int configKeyR[];
extern unsigned int configKeyZ[];
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
#ifdef BETTERCAMERA
extern bool         configEnableCamera;
extern bool         configCameraAnalog;
#ifdef MOUSE_ACTIONS
extern bool         configCameraMouse;
#endif
extern bool         configCameraInvertX;
extern bool         configCameraInvertY;
extern unsigned int configCameraXSens;
extern unsigned int configCameraYSens;
extern unsigned int configCameraAggr;
extern unsigned int configCameraScheme;
extern unsigned int configCameraOpacity;
extern bool         configDebugCamera;
#endif
extern bool         configHUD;
#ifdef MOUSE_ACTIONS
extern bool         configMouse;
#endif
extern bool         configSkipIntro;
#ifdef DISCORDRPC
extern bool         configDiscordRPC;
#endif

void configfile_load(const char *filename);
void configfile_save(const char *filename);
const char *configfile_name(void);

#endif
