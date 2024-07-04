#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "macros.h"
#include "PR/ultratypes.h"
#include "game/ingame_menu.h"
#include "game/memory.h"
#include "game/save_file.h"
#include "pc/configfile.h"
#include "discordrpc.h"

#define DISCORDLIBFILE "libdiscord-rpc"

// Thanks Microsoft for being non posix compliant
#if defined(_WIN32)
# include <windows.h>
# define DISCORDLIBEXT ".dll"
# define dlopen(lib, flag) LoadLibrary(TEXT(lib))
# define dlerror() ""
# define dlsym(handle, func) (void *)GetProcAddress(handle, func)
# define dlclose(handle) FreeLibrary(handle)
#elif defined(__APPLE__)
# include <dlfcn.h>
# define DISCORDLIBEXT ".dylib"
#elif defined(__linux__) || defined(__FreeBSD__) // lets make the bold assumption for FreeBSD
# include <dlfcn.h>
# define DISCORDLIBEXT ".so"
#else
# error Unknown System
#endif

#define DISCORDLIB DISCORDLIBFILE DISCORDLIBEXT
#define DISCORD_APP_ID  "709083908708237342"
#define DISCORD_UPDATE_RATE 5

extern s16 gCurrCourseNum;
extern s16 gCurrActNum;
extern u8 seg2_course_name_table[];
extern u8 seg2_act_name_table[];

static time_t lastUpdatedTime;

static DiscordRichPresence discordRichPresence;
static bool initd = false;

static void* handle;

void (*Discord_Initialize)(const char *, DiscordEventHandlers *, int, const char *);
void (*Discord_Shutdown)(void);
void (*Discord_ClearPresence)(void);
void (*Discord_UpdatePresence)(DiscordRichPresence *);

static s16 lastCourseNum = -1;
static s16 lastActNum = -1;

#ifdef VERSION_EU
#include "eu_translation.h"
extern s32 gInGameLanguage;
#endif

static char stage[188];
static char act[188];

static char smallImageKey[5];
static char largeImageKey[5];

static void on_ready(UNUSED const DiscordUser* user) {
    discord_reset();
}

static void init_discord(void) {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = on_ready;

    Discord_Initialize(DISCORD_APP_ID, &handlers, false, "");

    initd = true;
}

static void set_details(void) {
    if (lastCourseNum != gCurrCourseNum) {
        // If we are in in Course 0 we are in the castle which doesn't have a string
        if (gCurrCourseNum) {
            void **courseNameTbl;

#ifndef VERSION_EU
            courseNameTbl = segmented_to_virtual(seg2_course_name_table);
#else
            switch (gInGameLanguage) {
                case LANGUAGE_ENGLISH:
                    courseNameTbl = segmented_to_virtual(course_name_table_eu_en);
                    break;
                case LANGUAGE_FRENCH:
                    courseNameTbl = segmented_to_virtual(course_name_table_eu_fr);
                    break;
                case LANGUAGE_GERMAN:
                    courseNameTbl = segmented_to_virtual(course_name_table_eu_de);
                    break;
            }
#endif
            u8 *courseName = segmented_to_virtual(courseNameTbl[gCurrCourseNum - 1]);
            
            strcpy(stage, check_number_string_in_course_name(courseName));
            captialize_first_character_only(stage);
        } else {
            strcpy(stage, "Peach's Castle");
        }

        lastCourseNum = gCurrCourseNum;
    }
}

static void set_state(void) {
    if (lastActNum != gCurrActNum || lastCourseNum != gCurrCourseNum) {
        // when exiting a stage the act doesn't get reset
        if (gCurrActNum && gCurrCourseNum) {
            // any stage over 19 is a special stage without acts
            if (gCurrCourseNum < COURSE_STAGES_MAX) {
                void **actNameTbl;
#ifndef VERSION_EU
                actNameTbl = segmented_to_virtual(seg2_act_name_table);
#else
                switch (gInGameLanguage) {
                    case LANGUAGE_ENGLISH:
                        actNameTbl = segmented_to_virtual(act_name_table_eu_en);
                        break;
                    case LANGUAGE_FRENCH:
                        actNameTbl = segmented_to_virtual(act_name_table_eu_fr);
                        break;
                    case LANGUAGE_GERMAN:
                        actNameTbl = segmented_to_virtual(act_name_table_eu_de);
                        break;
                }
#endif
                char *actName = segmented_to_virtual(actNameTbl[(gCurrCourseNum - 1) * 6 + gCurrActNum - 1]);

                strcpy(act, actName);
                captialize_first_character_only(act);
            } else {
                act[0] = '\0';
                gCurrActNum = 0;
            }
        } else { 
            act[0] = '\0';
        }

        lastActNum = gCurrActNum;
    }
}

void set_logo(void) {
    if (lastCourseNum)
        snprintf(largeImageKey, sizeof(largeImageKey), "%d", lastCourseNum);
    else 
        strcpy(largeImageKey, "0");

    /*
    if (lastActNum)
        snprintf(smallImageKey, sizeof(largeImageKey), "%d", lastActNum);
    else
        smallImageKey[0] = '\0';
    */

    discordRichPresence.largeImageKey = largeImageKey;
    //discordRichPresence.largeImageText = "";
    //discordRichPresence.smallImageKey = smallImageKey;
    //discordRichPresence.smallImageText = "";
}

void discord_update_rich_presence(void) {
    if (!configDiscordRPC || !initd) return;
    if (time(NULL) < lastUpdatedTime + DISCORD_UPDATE_RATE) return;

    lastUpdatedTime = time(NULL);

    set_state();
    set_details();
    set_logo();
    Discord_UpdatePresence(&discordRichPresence);
}

void discord_shutdown(void) {
    if (handle) {
        Discord_ClearPresence();
        Discord_Shutdown();
        dlclose(handle);
    }
}

void discord_init(void) {
    if (configDiscordRPC) {
        handle = dlopen(DISCORDLIB, RTLD_LAZY);
        if (!handle) {
            fprintf(stderr, "Unable to load Discord\n%s\n", dlerror());
            return;
        }

        Discord_Initialize = dlsym(handle, "Discord_Initialize");
        Discord_Shutdown = dlsym(handle, "Discord_Shutdown");
        Discord_ClearPresence = dlsym(handle, "Discord_ClearPresence");
        Discord_UpdatePresence = dlsym(handle, "Discord_UpdatePresence");

        init_discord();

        discordRichPresence.details = stage;
        discordRichPresence.state = act;

        lastUpdatedTime = 0;
    }
}

void discord_reset(void) {
    memset( &discordRichPresence, 0, sizeof( discordRichPresence ) );

    set_state();
    set_details();
    set_logo();
    Discord_UpdatePresence(&discordRichPresence);
}
