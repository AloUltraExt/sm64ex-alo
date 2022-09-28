/*
 * Redone description:
 * A backported version of the level select used in Zelda-engine games released on N64.
 * Replaces old debug level select.
 * Adapted to Super Mario 64 and improved by AloXado320.
 * Props to ZeldaRET for decompiling the code (z_select.c).
 */

#include "game/segment2.h"
#include "game/ingame_menu.h"
#include "extras/draw_util.h"

#define MAX_PAGE_STRINGS 12
#define PAGE_DOWN_STOPS_MAX (LEVEL_MAX / MAX_PAGE_STRINGS)

struct ZDebugLevelSelect {
    s32 count;
    s32 currentScene;
    s32 pageDownIndex; // Index of pageDownStops
    s32 pageDownStops[PAGE_DOWN_STOPS_MAX];
    s32 topDisplayedScene; // The scene which is currently at the top of the screen
    s32 verticalInputAccumulator;
    s32 verticalInput;
    s32 timerUp;
    s32 timerDown;
    s32 lockUp;
    s32 lockDown;
    s32 refreshRate;
    s32 toggleCourseLevelView;
    s32 toggleControlsView;
};

// Duplicate copy to initiate struct
struct ZDebugLevelSelect gZDbgLevelSelectInit;
struct ZDebugLevelSelect *gZDbgLevelSelect = &gZDbgLevelSelectInit;

void print_debug_level_select_menu(struct ZDebugLevelSelect *this) {
    s32 scene;
    s32 i;
    char *levelName;
    s32 courseNum;
    u8 *courseName;
    s32 xPos;
    char *chrTemp;
    u8 levelNumStr[4];
    u8 courseNumStr[4];

    gDPSetEnvColor(gDisplayListHead++, 255, 155, 150, 255);
    chrTemp = "SUPER MARIO LEVEL SELECT";
    xPos = get_str_x_pos_from_center_custom_ascii(LUT_TYPE_STR_ASCII, SCREEN_WIDTH / 2, chrTemp, FALSE, 0);
    print_generic_string_ascii(xPos, 210, chrTemp);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

    if (this->toggleControlsView) {
        return;
    }

    void **courseNameTbl;
#ifdef VERSION_EU
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
#else
    courseNameTbl = segmented_to_virtual(seg2_course_name_table);
#endif

    for (i = 0; i < MAX_PAGE_STRINGS; i++) {
        scene = (this->topDisplayedScene + i + this->count) % this->count;
        int_to_str(scene + 1, levelNumStr);

        if (scene == this->currentScene) {
            gDPSetEnvColor(gDisplayListHead++, 255, 126, 0, 255);
        } else {
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        }

        levelName = gLevelSelectStageNames[scene];
        if (levelName == NULL) {
            levelName = "--Null--";
        }
        courseNum = gLevelToCourseNumTable[scene];
        courseName = segmented_to_virtual(courseNameTbl[courseNum - 1]);
        int_to_str(courseNum, courseNumStr);

        if (this->toggleCourseLevelView) {
            chrTemp = "LEVEL    NAME";
            print_generic_string(72, 180 - i * 11, levelNumStr);
            print_generic_string_ascii(100, 180 - i * 11, levelName);
        } else {
            chrTemp = "COURSE   NAME";
            print_generic_string(72, 180 - i * 11, courseNumStr);
            if (courseName != NULL && courseNum >= COURSE_MIN && courseNum <= COURSE_MAX) {
                print_generic_string(100, 180 - i * 11, &courseName[3]);
            }
        }
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_generic_string_ascii(60, 194, chrTemp);
    }
}

void print_debug_level_select_settings(struct ZDebugLevelSelect *this) {
    u8 strSaveNum[4];
    u8 strActNum[4];
    char *chrTemp;

    s16 saveNum = gCurrSaveFileNum;
    s16 actNum = gDialogCourseActNum = gCurrActNum;
    int_to_str(saveNum, strSaveNum);
    int_to_str(actNum, strActNum);

    u8 *actName;
    void **actNameTbl;
    s32 courseNum;
#ifdef VERSION_EU
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
#else
    actNameTbl = segmented_to_virtual(seg2_act_name_table);
#endif

    courseNum = gLevelToCourseNumTable[this->currentScene];
    actName = segmented_to_virtual(actNameTbl[COURSE_NUM_TO_INDEX(courseNum) * 6 + actNum - 1]);

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

    chrTemp = "Save File: ";
    print_generic_string_ascii(20, 42, chrTemp);
    print_generic_string(20 + get_string_width_ascii(chrTemp), 42, strSaveNum);

    chrTemp = "Level Act: ";
    print_generic_string_ascii(20, 28, chrTemp);
    print_generic_string(20 + get_string_width_ascii(chrTemp), 28, strActNum);
    if (actName != NULL && courseNum >= COURSE_MIN && courseNum <= COURSE_STAGES_MAX) {
        print_generic_string(20 + 20 + get_string_width_ascii(chrTemp), 28, actName);
    }

    chrTemp = "(C Down) - Show-Hide Controls";
    print_generic_string_ascii(20, 14, chrTemp);
}

const char lvlSelectDbgCtrlStr[][40] = {
    "(D Pad) - Select Level",
    "(R) - Change List Page",
    "(Z) - Change Save File",
    "(B) - Change Act",
    "(C Up) - Change Level List",
    "(A)(L)(R) - Hold to Reset",
    "(A), (Start) - Load Level",
};

const char lvlSelectDbgCtrlViewStr[] = { "(C Down) - Show-Hide Controls" };

void print_debug_level_select_controls(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(lvlSelectDbgCtrlStr); i++) {
        print_generic_string_ascii(40, 186 - i * 16, lvlSelectDbgCtrlStr[i]);
    }

    print_generic_string_ascii(40, 38, lvlSelectDbgCtrlViewStr);
}

void print_debug_level_select_strings(struct ZDebugLevelSelect *this) {

    create_dl_ortho_matrix();

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

    print_debug_level_select_menu(this);

    if (this->toggleControlsView) {
        print_debug_level_select_controls();
    } else {
        print_debug_level_select_settings(this);
    }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

Gfx *geo_debug_level_select_strings(s16 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        print_debug_level_select_strings(gZDbgLevelSelect);
    }
    return NULL;
}

void debug_level_select_update(struct ZDebugLevelSelect *this) {
    if (this->verticalInputAccumulator == 0) {
        gCurrLevelNum = this->currentScene + 1;

        if (gPlayer1Controller->buttonPressed & D_CBUTTONS) {
            this->toggleControlsView ^= 1;
        }

        if (this->toggleControlsView) {
            return;
        }

        if (gPlayer1Controller->buttonPressed & U_CBUTTONS) {
            this->toggleCourseLevelView ^= 1;
        }

        if (gPlayer1Controller->buttonPressed & B_BUTTON) {
            gCurrActNum++;

            if (gCurrActNum > 6) {
                gCurrActNum = 1;
            }
        }

        if (gPlayer1Controller->buttonPressed & Z_TRIG) {
            gCurrSaveFileNum++;

            if (gCurrSaveFileNum > 4) {
                gCurrSaveFileNum = 1;
            }
        }

        if (gPlayer1Controller->buttonPressed & U_JPAD) {
            if (this->lockUp == TRUE) {
                this->timerUp = 0;
            }
            if (this->timerUp == 0) {
                this->timerUp = 20;
                this->lockUp = TRUE;
                play_sound(SOUND_GENERAL_LEVEL_SELECT_CHANGE, gGlobalSoundSource);
                this->verticalInput = this->refreshRate;
            }
        }

        if (gPlayer1Controller->buttonDown & U_JPAD && this->timerUp == 0) {
            play_sound(SOUND_GENERAL_LEVEL_SELECT_CHANGE, gGlobalSoundSource);
            this->verticalInput = this->refreshRate * 3;
        }

        if (gPlayer1Controller->buttonPressed & D_JPAD) {
            if (this->lockDown == TRUE) {
                this->timerDown = 0;
            }
            if (this->timerDown == 0) {
                this->timerDown = 20;
                this->lockDown = TRUE;
                play_sound(SOUND_GENERAL_LEVEL_SELECT_CHANGE, gGlobalSoundSource);
                this->verticalInput = -this->refreshRate;
            }
        }

        if (gPlayer1Controller->buttonDown & D_JPAD && this->timerDown == 0) {
            play_sound(SOUND_GENERAL_LEVEL_SELECT_CHANGE, gGlobalSoundSource);
            this->verticalInput = -this->refreshRate * 3;
        }

        if ((gPlayer1Controller->buttonPressed & L_JPAD) || (gPlayer1Controller->buttonDown & L_JPAD)) {
            play_sound(SOUND_GENERAL_LEVEL_SELECT_CHANGE, gGlobalSoundSource);
            this->verticalInput = this->refreshRate;
        }

        if ((gPlayer1Controller->buttonPressed & R_JPAD) || (gPlayer1Controller->buttonDown & R_JPAD)) {
            play_sound(SOUND_GENERAL_LEVEL_SELECT_CHANGE, gGlobalSoundSource);
            this->verticalInput = -this->refreshRate;
        }
    }

    if (gPlayer1Controller->buttonPressed & R_TRIG) {
        this->pageDownIndex++;
        this->pageDownIndex =
            (this->pageDownIndex + ARRAY_COUNT(this->pageDownStops)) % ARRAY_COUNT(this->pageDownStops);
        this->currentScene = this->topDisplayedScene = this->pageDownStops[this->pageDownIndex];
    }

    this->verticalInputAccumulator += this->verticalInput;

    if (this->verticalInputAccumulator < -7) {
        this->verticalInput = 0;
        this->verticalInputAccumulator = 0;

        this->currentScene++;
        this->currentScene = (this->currentScene + this->count) % this->count;

        if (this->currentScene == ((this->topDisplayedScene + this->count + MAX_PAGE_STRINGS) % this->count)) {
            this->topDisplayedScene++;
            this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;
        }
    }

    if (this->verticalInputAccumulator > 7) {
        this->verticalInput = 0;
        this->verticalInputAccumulator = 0;

        if (this->currentScene == this->topDisplayedScene) {
            this->topDisplayedScene -= 2;
            this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;
        }

        this->currentScene--;
        this->currentScene = (this->currentScene + this->count) % this->count;

        if (this->currentScene == ((this->topDisplayedScene + this->count) % this->count)) {
            this->topDisplayedScene--;
            this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;
        }
    }

    this->currentScene = (this->currentScene + this->count) % this->count;
    this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;

    if (this->timerUp != 0) {
        this->timerUp--;
    }

    if (this->timerUp == 0) {
        this->lockUp = FALSE;
    }

    if (this->timerDown != 0) {
        this->timerDown--;
    }

    if (this->timerDown == 0) {
        this->lockDown = FALSE;
    }
}

s32 lvl_init_intro_level_select(UNUSED s32 arg, UNUSED s32 unused) {
    s16 i;
    gCurrSaveFileNum = 1;
    gCurrActNum = 1;

    for (i = 0; i < ARRAY_COUNT(gZDbgLevelSelect->pageDownStops); i++) {
        gZDbgLevelSelect->pageDownStops[i] = MAX_PAGE_STRINGS * i;
    }

    gZDbgLevelSelect->count = ARRAY_COUNT(gLevelSelectStageNames);
    gZDbgLevelSelect->verticalInputAccumulator = 0;
    gZDbgLevelSelect->verticalInput = 0;
    gZDbgLevelSelect->timerUp = 0;
    gZDbgLevelSelect->timerDown = 0;
    gZDbgLevelSelect->lockUp = 0;
    gZDbgLevelSelect->lockDown = 0;

    gZDbgLevelSelect->currentScene = gCurrLevelNum - 1;
    gZDbgLevelSelect->topDisplayedScene = gCurrLevelNum - 1;

    gZDbgLevelSelect->pageDownIndex = 0;

    gZDbgLevelSelect->refreshRate = 1;

    gZDbgLevelSelect->toggleCourseLevelView = 0;
    gZDbgLevelSelect->toggleControlsView = 0;

    return 0;
}

s16 intro_level_select(void) {
    debug_level_select_update(gZDbgLevelSelect);

    // Don't perform any button actions if controls view is active
    if (gZDbgLevelSelect->toggleControlsView) {
        return 0;
    }

    // Resets the game and disables level select
    if (gPlayer1Controller->buttonDown == (A_BUTTON | L_TRIG | R_TRIG)) {
        play_sound(SOUND_MENU_ENTER_HOLE, gGlobalSoundSource);
        gDebugLevelSelect = FALSE;
        return -1;
    }

    // Starts level selected
    if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
        play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
        return gCurrLevelNum;
    }

    return 0;
}
