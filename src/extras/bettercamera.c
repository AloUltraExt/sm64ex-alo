#ifdef BETTERCAMERA

///Puppycam 2.2 by Fazana
///Extra features and fixes by AloXado320

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "sm64.h"
#include "types.h"
#include "game/level_update.h"
#include "bettercamera.h"
#include "audio/external.h"
#include "audio/data.h"
#include "game/game_init.h"
#include "engine/math_util.h"
#include "game/hud.h"
#include "game/print.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"
#include "include/text_strings.h"
#include "game/segment2.h"
#include "game/ingame_menu.h"
#include "game/memory.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "behavior_data.h"
#include "game/save_file.h"
#include "game/mario.h"
#include "gfx_dimensions.h"

#include "pc/configfile.h"

#ifdef MOUSE_ACTIONS
#include "pc/controller/controller_mouse.h"
#endif

#define PUPPYCAM_FLOOR_DIST_DOWN 350
#define PUPPYCAM_FLOOR_DIST_UP   300

#define PUPPYCAM_DECELERATION 0.66f
#define PUPPYCAM_DEADZONE        20
#define SCRIPT_MEMORY_POOL   0x1000

struct gPuppyStruct gPuppyCam;
struct sPuppyVolume *sPuppyVolumeStack[MAX_PUPPYCAM_VOLUMES];
s16 sFloorHeight = 0;
u16 gPuppyVolumeCount = 0;
struct MemoryPool *gPuppyMemoryPool;
s32 gPuppyError = 0;

#ifdef TARGET_N64 // TODO: save to EEPROM
// BetterCamera settings
ConfigPuppyCam configPuppyCam = {
    .enable = TRUE,
    .analog = FALSE,
#ifdef MOUSE_ACTIONS
    .mouse = FALSE,
#endif
    .invertX = TRUE,
    .invertY = TRUE,
    .sensX = 100,
    .sensY = 100,
    .aggression = 50,
    .scheme = 0, // PUPPYCAM_INPUT_TYPE_DOUBLE_TAB
    .opacity = 1, // PUPPYCAM_OPACITY_TYPE_FADE
    .debug = FALSE,
};
#endif

s16 LENSIN(s16 length, s16 direction) {
    return (length * sins(direction));
}
s16 LENCOS(s16 length, s16 direction) {
    return (length * coss(direction));
}

static inline float smooth(float x) {
    x = CLAMP(x, 0, 1);
    return x * x * (3.f - 2.f * x);
}

static inline float softClamp(float x, float a, float b) {
    return smooth((2.f / 3.f) * (x - a) / (b - a) + (1.f / 6.f)) * (b - a) + a;
}

/// CONFIG

const u8 optsPuppyCamStr[][32] = {
    { TEXT_OPT_PUPPYCAM },
    { TEXT_OPT_PUPPYON },
    { TEXT_OPT_ANALOGUE },
    { TEXT_OPT_CAMMOUSE },
    { TEXT_OPT_INVERTX },
    { TEXT_OPT_INVERTY },
    { TEXT_OPT_CAMX },
    { TEXT_OPT_CAMY },
    { TEXT_OPT_CAMC },
    { TEXT_OPT_CAMSCHEME },
    { TEXT_OPT_OPA_TYPE },
    { TEXT_OPT_DBG_CAM },
};

static const u8 optsPuppyCamSchemeStr[][64] = {
    { TEXT_OPT_CAM_SCH1 },
    { TEXT_OPT_CAM_SCH2 },
    { TEXT_OPT_CAM_SCH3 },
};

static const u8 *puppycamChoicesScheme[] = {
    optsPuppyCamSchemeStr[0],
    optsPuppyCamSchemeStr[1],
    optsPuppyCamSchemeStr[2],
};

static const u8 optsPuppyCamOpacityStr[][64] = {
    { TEXT_OPT_OPA_T1 },
    { TEXT_OPT_OPA_T2 },
    { TEXT_OPT_OPA_T3 },
};

static const u8 *puppycamChoicesOpacity[] = {
    optsPuppyCamOpacityStr[0],
    optsPuppyCamOpacityStr[1],
    optsPuppyCamOpacityStr[2],
};

static struct Option optsPuppyCam[] = {
    DEF_OPT_TOGGLE( optsPuppyCamStr[2], &configPuppyCam.analog ),
#ifdef MOUSE_ACTIONS
    DEF_OPT_TOGGLE( optsPuppyCamStr[3], &configPuppyCam.mouse ),
#endif
    DEF_OPT_TOGGLE( optsPuppyCamStr[4], &configPuppyCam.invertX ),
    DEF_OPT_TOGGLE( optsPuppyCamStr[5], &configPuppyCam.invertY ),
    DEF_OPT_SCROLL( optsPuppyCamStr[6], &configPuppyCam.sensX, 1, 100, 1 ),
    DEF_OPT_SCROLL( optsPuppyCamStr[7], &configPuppyCam.sensY, 1, 100, 1 ),
    DEF_OPT_SCROLL( optsPuppyCamStr[8], &configPuppyCam.aggression, 0, 100, 1 ),
    DEF_OPT_CHOICE( optsPuppyCamStr[9], &configPuppyCam.scheme, puppycamChoicesScheme ),
    DEF_OPT_CHOICE(optsPuppyCamStr[10], &configPuppyCam.opacity, puppycamChoicesOpacity ),
    DEF_OPT_TOGGLE(optsPuppyCamStr[11], &configPuppyCam.debug ),
};

struct SubMenu menuPuppyCam = DEF_SUBMENU( optsPuppyCamStr[0], optsPuppyCam );


void puppycam_default_config(void) {
    gPuppyCam.enabled = configPuppyCam.enable;
    gPuppyCam.options.analogue = configPuppyCam.analog;
#ifdef MOUSE_ACTIONS
    gPuppyCam.mouse = configPuppyCam.mouse;
#endif
    gPuppyCam.options.invertX = configPuppyCam.invertX;
    gPuppyCam.options.invertY = configPuppyCam.invertY;
    gPuppyCam.options.sensitivityX = configPuppyCam.sensX;
    gPuppyCam.options.sensitivityY = configPuppyCam.sensY;
    gPuppyCam.options.turnAggression = configPuppyCam.aggression;
    gPuppyCam.options.inputType = configPuppyCam.scheme;
    gPuppyCam.options.opacityType = configPuppyCam.opacity;
    gPuppyCam.options.debugCam = configPuppyCam.debug;
}

// Initial setup. Ran at the beginning of the game and never again.
void puppycam_boot(void) {
    gPuppyCam.zoomPoints[0] = 600;
    gPuppyCam.zoomPoints[1] = 1000;
    gPuppyCam.zoomPoints[2] = 1500;
    gPuppyCam.povHeight     = 125;
    gPuppyCam.stick2[0]     = 0;
    gPuppyCam.stick2[1]     = 0;
    gPuppyCam.stickN[0]     = 0;
    gPuppyCam.stickN[1]     = 0;
    gPuppyMemoryPool        = mem_pool_init(MAX_PUPPYCAM_VOLUMES * sizeof(struct sPuppyVolume), MEMORY_POOL_LEFT);
    gPuppyVolumeCount       = 0;

    // puppycam_get_save();
}

// Called when an instant warp is done.
void puppycam_warp(f32 displacementX, f32 displacementY, f32 displacementZ) {
    gPuppyCam.pos[0]                += displacementX;
    gPuppyCam.pos[1]                += displacementY;
    gPuppyCam.pos[2]                += displacementZ;
    gPuppyCam.targetFloorHeight     += displacementY;
    gPuppyCam.lastTargetFloorHeight += displacementY;
    gPuppyCam.floorY[0]             += displacementY;
    gPuppyCam.floorY[1]             += displacementY;
}

/// CUTSCENE

void puppycam_activate_cutscene(s32 (*scene)(), s32 lockinput) {
    gPuppyCam.cutscene   = 1;
    gPuppyCam.sceneTimer = 0;
    gPuppyCam.sceneFunc  = scene;
    gPuppyCam.sceneInput = lockinput;
}

// If you've read camera.c this will look familiar.
// It takes the next 4 spline points and extrapolates a curvature based positioning of the camera vector that's passed through.
// It's a standard B spline
static void puppycam_evaluate_spline(f32 progress, Vec3s pos, Vec3f spline1, Vec3f spline2, Vec3f spline3, Vec3f spline4) {
    Vec3f posf;
    vec3s_to_vec3f(posf, pos);
    evaluate_cubic_spline(progress, posf, spline1, spline2, spline3, spline4);
    vec3f_to_vec3s(pos, posf);
}

s32 puppycam_move_spline(struct sPuppySpline splinePos[], struct sPuppySpline splineFocus[], s32 mode, s32 index) {
    Vec3f tempPoints[4];
    f32 tempProgress[2] = {0.0f, 0.0f};
    f32 progChange = 0.0f;
    s32 i;
    Vec3f prevPos;

    if (gPuppyCam.splineIndex == 65000) {
        gPuppyCam.splineIndex = index;
    }
    if (splinePos[gPuppyCam.splineIndex + 0].index == -1
     || splinePos[gPuppyCam.splineIndex + 1].index == -1
     || splinePos[gPuppyCam.splineIndex + 2].index == -1) {
        return TRUE;
    }
    if (mode == PUPPYSPLINE_FOLLOW) {
        if (splineFocus[gPuppyCam.splineIndex + 0].index == -1
         || splineFocus[gPuppyCam.splineIndex + 1].index == -1
         || splineFocus[gPuppyCam.splineIndex + 2].index == -1) {
            return TRUE;
        }
    }
    vec3s_to_vec3f(prevPos, gPuppyCam.pos);

    for (i = 0; i < 4; i++) {
        vec3s_to_vec3f(tempPoints[i], splinePos[gPuppyCam.splineIndex + i].pos);
    }
    puppycam_evaluate_spline(gPuppyCam.splineProgress, gPuppyCam.pos, tempPoints[0], tempPoints[1], tempPoints[2], tempPoints[3]);
    if (mode == PUPPYSPLINE_FOLLOW) {
        for (i = 0; i < 4; i++) {
            vec3s_to_vec3f(tempPoints[i], splineFocus[gPuppyCam.splineIndex + i].pos);
        }
        puppycam_evaluate_spline(gPuppyCam.splineProgress, gPuppyCam.focus, tempPoints[0], tempPoints[1], tempPoints[2], tempPoints[3]);
    }

    if (splinePos[gPuppyCam.splineIndex + 1].speed != 0) {
        tempProgress[0] = 1.0f / splinePos[gPuppyCam.splineIndex + 1].speed;
    }
    if (splinePos[gPuppyCam.splineIndex + 2].speed != 0) {
        tempProgress[1] = 1.0f / splinePos[gPuppyCam.splineIndex + 2].speed;
    }
    progChange = (tempProgress[1] - tempProgress[0]) * gPuppyCam.splineProgress + tempProgress[0];

    gPuppyCam.splineProgress += progChange;

    if (gPuppyCam.splineProgress >= 1.0f) {
        gPuppyCam.splineIndex++;
        if (splinePos[gPuppyCam.splineIndex + 3].index == -1) {
            gPuppyCam.splineIndex = 0;
            gPuppyCam.splineProgress = 0;
            return TRUE;
        }
        gPuppyCam.splineProgress -= 1;
    }

    return FALSE;
}

static void puppycam_process_cutscene(void) {
    if (gPuppyCam.cutscene != 0) {
        if ((gPuppyCam.sceneFunc)() == 1) {
            gPuppyCam.cutscene = 0;
            gPuppyCam.sceneInput = 0;
            gPuppyCam.flags = gPuppyCam.intendedFlags;
        }
        gPuppyCam.sceneTimer++;
    }
}

//extern struct SaveBuffer gSaveBuffer;

/// CORE

// Just a function that sets a bunch of camera values to 0. It's a function because it's got shared functionality.
void puppycam_reset_values(void) {
    gPuppyCam.swimPitch      = 0;
    gPuppyCam.edgePitch      = 0;
    gPuppyCam.moveZoom       = 0;
    gPuppyCam.floorY[0]      = 0;
    gPuppyCam.floorY[1]      = 0;
    gPuppyCam.terrainPitch   = 0;
    gPuppyCam.splineIndex    = 0;
    gPuppyCam.splineProgress = 0;
}

// Set up values. Runs on level load.
void puppycam_init(void) {
    if (gMarioState->marioObj) {
        gPuppyCam.targetObj = gMarioState->marioObj;
    }
    gPuppyCam.targetObj2 = NULL;

    gPuppyCam.intendedFlags = PUPPYCAM_BEHAVIOUR_DEFAULT;
    // if (gCurrLevelNum == LEVEL_PSS || (gCurrLevelNum == LEVEL_TTM && gCurrAreaIndex == 2) || (gCurrLevelNum == LEVEL_CCM && gCurrAreaIndex == 2)) {
    //     gPuppyCam.intendedFlags |= PUPPYCAM_BEHAVIOUR_SLIDE_CORRECTION;
    // }
    gPuppyCam.flags                 = gPuppyCam.intendedFlags;
    gPuppyCam.zoom                  = gPuppyCam.zoomPoints[1];
    gPuppyCam.zoomSet               = 1;
    gPuppyCam.zoomTarget            = gPuppyCam.zoom;
    gPuppyCam.yaw                   = gMarioState->faceAngle[1] + 0x8000;
    gPuppyCam.yawTarget             = gPuppyCam.yaw;
    gPuppyCam.pitch                 = 0x3800;
    gPuppyCam.pitchTarget           = gPuppyCam.pitch;
    gPuppyCam.yawAcceleration       = 0;
    gPuppyCam.pitchAcceleration     = 0;
    gPuppyCam.shakeFrames           = 0;
    vec3_zero(gPuppyCam.shake);
    vec3_zero(gPuppyCam.pos);
    vec3_zero(gPuppyCam.focus);
    vec3_zero(gPuppyCam.pan); // gMarioState->pos[1];
    gPuppyCam.targetFloorHeight     = gPuppyCam.pan[1];
    gPuppyCam.lastTargetFloorHeight = gMarioState->pos[1];
    gPuppyCam.opacity               = 255;
    gPuppyCam.framesSinceC[0]       = 10; // This just exists to stop input type B being stupid.
    gPuppyCam.framesSinceC[1]       = 10; // This just exists to stop input type B being stupid.
    gPuppyCam.mode3Flags            = PUPPYCAM_MODE3_ZOOMED_MED;
    gPuppyCam.debugFlags            = PUPPYDEBUG_LOCK_CONTROLS;
    puppycam_reset_values();
}

void puppycam_input_pitch(void) {
    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_PITCH_ROTATION) {
        // Handles vertical inputs.
        if ((gPlayer1Controller->buttonDown & U_CBUTTONS) || gPuppyCam.stick2[1] != 0) {
            gPuppyCam.pitchAcceleration -= 50 * (gPuppyCam.options.sensitivityY / 100.f);
        } else if ((gPlayer1Controller->buttonDown & D_CBUTTONS) || gPuppyCam.stick2[1] != 0) {
            gPuppyCam.pitchAcceleration += 50 * (gPuppyCam.options.sensitivityY / 100.f);
        } else {
            gPuppyCam.pitchAcceleration = 0;
        }
        gPuppyCam.pitchAcceleration = CLAMP(gPuppyCam.pitchAcceleration, -100, 100);

        // When Mario's moving, his pitch is clamped pretty aggressively, so this exists so you can shift your view up and down momentarily at an actually usable range, rather than the otherwise baby range.
        if ((gMarioState->action & ACT_FLAG_MOVING) && (gPuppyCam.pitch >= 0x3800 || gPuppyCam.pitch <= 0x2000)) {
            gPuppyCam.moveFlagAdd = 8;
        }
    }
}

void puppycam_input_zoom(void) {
    // Update zoom if it doesn't match with the zoom target point
    if (gPuppyCam.zoomTarget != gPuppyCam.zoomPoints[gPuppyCam.zoomSet]) {
        gPuppyCam.zoomTarget = gPuppyCam.zoomPoints[gPuppyCam.zoomSet];
    }

    // Handles R button zooming.
    if ((gPlayer1Controller->buttonPressed & R_TRIG) && (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_ZOOM_CHANGE)) {
        gPuppyCam.zoomSet++;

        if (gPuppyCam.zoomSet >= 3) {
            gPuppyCam.zoomSet = 0;
        }
        gPuppyCam.zoomTarget = gPuppyCam.zoomPoints[gPuppyCam.zoomSet];
        play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gGlobalSoundSource);
    }
}

void puppycam_input_centre(void) {
    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_FREE) {
        return;
    }
    s32 inputDefault = L_TRIG;
    if (gPuppyCam.options.inputType == PUPPYCAM_INPUT_TYPE_CLASSIC) {
        inputDefault = R_TRIG;
    }
    // Handles L button centering.
    if ((gPlayer1Controller->buttonPressed & inputDefault)
     && (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_YAW_ROTATION)
     && !(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR)
     && !(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_4DIR)
     && !(gPlayer1Controller->buttonDown & U_JPAD)) {
        gPuppyCam.yawTarget = gMarioState->faceAngle[1] + 0x8000;
        play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gGlobalSoundSource);
    }
}

// The default control scheme. Hold the button down to turn the camera, and double tap to turn quickly.
static void puppycam_input_hold_preset1(f32 ivX) {
    if (!gPuppyCam.options.analogue && (gPlayer1Controller->buttonPressed & L_CBUTTONS) && gPuppyCam.framesSinceC[0] <= 5) {
        gPuppyCam.yawTarget -= 0x4000 * ivX;
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
    } else if (!gPuppyCam.options.analogue && (gPlayer1Controller->buttonPressed & R_CBUTTONS) && gPuppyCam.framesSinceC[1] <= 5) {
        gPuppyCam.yawTarget += 0x4000 * ivX;
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
    }

    if (((gPlayer1Controller->buttonDown & L_CBUTTONS) && !gPuppyCam.options.analogue) || gPuppyCam.stick2[0] != 0) {
        gPuppyCam.yawAcceleration -= 75 * (gPuppyCam.options.sensitivityX / 100.f);
        gPuppyCam.framesSinceC[0] = 0;
    } else if (((gPlayer1Controller->buttonDown & R_CBUTTONS) && !gPuppyCam.options.analogue) || gPuppyCam.stick2[0] != 0) {
        gPuppyCam.yawAcceleration += 75 * (gPuppyCam.options.sensitivityX / 100.f);
        gPuppyCam.framesSinceC[1] = 0;
    } else {
        gPuppyCam.yawAcceleration = 0;
    }
}

// An alternative control scheme, hold the button down to turn the camera, or press it once to turn it quickly.
static void puppycam_input_hold_preset2(f32 ivX) {
    // These set the initial button press.
    if (gPlayer1Controller->buttonPressed & L_CBUTTONS) gPuppyCam.framesSinceC[0] = 0;
    if (gPlayer1Controller->buttonPressed & R_CBUTTONS) gPuppyCam.framesSinceC[1] = 0;
    // These handle when you release the button
    if ((!(gPlayer1Controller->buttonDown & L_CBUTTONS)) && gPuppyCam.framesSinceC[0] <= 5) {
        gPuppyCam.yawTarget -= 0x3000 * ivX;
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
        gPuppyCam.framesSinceC[0] = 6;
    }

    if ((!(gPlayer1Controller->buttonDown & R_CBUTTONS)) && gPuppyCam.framesSinceC[1] <= 5) {
        gPuppyCam.yawTarget += 0x3000 * ivX;
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
        gPuppyCam.framesSinceC[1] = 6;
    }

    // Handles continuous movement as normal, as long as the button's held.
    if (gPlayer1Controller->buttonDown & L_CBUTTONS) {
        gPuppyCam.yawAcceleration -= 75 * (gPuppyCam.options.sensitivityX / 100.f);
    } else if (gPlayer1Controller->buttonDown & R_CBUTTONS) {
        gPuppyCam.yawAcceleration += 75 * (gPuppyCam.options.sensitivityX / 100.f);
    } else {
        gPuppyCam.yawAcceleration = 0;
    }
}

// Another alternative control scheme. This one aims to mimic the parallel camera scheme down to the last bit from the original game.
static void puppycam_input_hold_preset3(void) {
    f32 stickMag[2] = { gPlayer1Controller->rawStickX * 0.65f, gPlayer1Controller->rawStickY * 0.2f };
    // Just in case it happens to be nonzero.
    gPuppyCam.yawAcceleration = 0;

    // In theory this shouldn't be necessary, but it's nice to cover all bases.
    if (!(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_YAW_ROTATION)) {
        return;
    }
    if (gPuppyCam.mode3Flags & PUPPYCAM_MODE3_ZOOMED_IN) {
        gPuppyCam.flags &= ~PUPPYCAM_BEHAVIOUR_COLLISION;

        // Handles continuous movement as normal, as long as the button's held.
        if (abss(gPlayer1Controller->rawStickX) > PUPPYCAM_DEADZONE) {
            gPuppyCam.yawAcceleration -= (gPuppyCam.options.sensitivityX / 100.f) * stickMag[0];
        } else {
            gPuppyCam.yawAcceleration = 0;
        }
        if (abss(gPlayer1Controller->rawStickY) > PUPPYCAM_DEADZONE) {
            gPuppyCam.pitchAcceleration -= (gPuppyCam.options.sensitivityY / 100.f) * stickMag[1];
        } else {
            gPuppyCam.pitchAcceleration = approach_f32_asymptotic(gPuppyCam.pitchAcceleration, 0, PUPPYCAM_DECELERATION);
        }
    } else {
        if ((gPlayer1Controller->buttonPressed & L_TRIG) && (gPuppyCam.yawTarget % 0x2000)) {
            gPuppyCam.yawTarget += 0x2000 - (gPuppyCam.yawTarget % 0x2000);
        }

        if (gPuppyCam.mode3Flags & PUPPYCAM_MODE3_ZOOMED_MED) gPuppyCam.pitchTarget = approach_s32(gPuppyCam.pitchTarget, 0x3800, 0x200, 0x200);
        if (gPuppyCam.mode3Flags & PUPPYCAM_MODE3_ZOOMED_OUT) gPuppyCam.pitchTarget = approach_s32(gPuppyCam.pitchTarget, 0x3000, 0x200, 0x200);

        if (((gPlayer1Controller->buttonPressed & L_CBUTTONS) && !gPuppyCam.options.analogue) || (gPuppyCam.stick2[0] > PUPPYCAM_DEADZONE && !gPuppyCam.stickN[0])) {
            gPuppyCam.stickN[0] = 1;
            gPuppyCam.yawTarget -= 0x2000;
            play_sound(SOUND_MENU_CAMERA_TURN, gGlobalSoundSource);
        }
        if (((gPlayer1Controller->buttonPressed & R_CBUTTONS) && !gPuppyCam.options.analogue) || (gPuppyCam.stick2[0] < -PUPPYCAM_DEADZONE && !gPuppyCam.stickN[0])) {
            gPuppyCam.stickN[0] = 1;
            gPuppyCam.yawTarget += 0x2000;
            play_sound(SOUND_MENU_CAMERA_TURN, gGlobalSoundSource);
        }
    }

    // Handles zooming in. Works just like vanilla.
    if ((gPlayer1Controller->buttonPressed & U_CBUTTONS && !gPuppyCam.options.analogue) || (gPuppyCam.stick2[1] > PUPPYCAM_DEADZONE && !gPuppyCam.stickN[1])) {
        if ((gPuppyCam.mode3Flags & PUPPYCAM_MODE3_ZOOMED_MED) && !(gMarioState->action & ACT_FLAG_AIR) && !(gMarioState->action & ACT_FLAG_SWIMMING)) {
            gPuppyCam.stickN[1] = 1;
            gPuppyCam.mode3Flags |= (PUPPYCAM_MODE3_ZOOMED_IN | PUPPYCAM_MODE3_ENTER_FIRST_PERSON);
            gPuppyCam.mode3Flags &= ~PUPPYCAM_MODE3_ZOOMED_MED;
            gPuppyCam.zoomTarget = 200;

            play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
        } else if (gPuppyCam.mode3Flags & PUPPYCAM_MODE3_ZOOMED_OUT) {
            gPuppyCam.stickN[1] = 1;
            gPuppyCam.mode3Flags |= PUPPYCAM_MODE3_ZOOMED_MED;
            gPuppyCam.mode3Flags &= ~PUPPYCAM_MODE3_ZOOMED_OUT;
            gPuppyCam.zoomTarget = gPuppyCam.zoomPoints[1];

            play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
        }
    } else  if (((gPlayer1Controller->buttonPressed & D_CBUTTONS) && !gPuppyCam.options.analogue) || (gPuppyCam.stick2[1] < -PUPPYCAM_DEADZONE && !gPuppyCam.stickN[1])) { // Otherwise handle zooming out.
        if (gPuppyCam.mode3Flags & PUPPYCAM_MODE3_ZOOMED_MED) {
            gPuppyCam.stickN[1] = 1;
            gPuppyCam.mode3Flags |= PUPPYCAM_MODE3_ZOOMED_OUT;
            gPuppyCam.mode3Flags &= ~PUPPYCAM_MODE3_ZOOMED_MED;
            gPuppyCam.zoomTarget = gPuppyCam.zoomPoints[2];

            play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
        }
    }
    if (((gPlayer1Controller->buttonPressed & D_CBUTTONS) && !gPuppyCam.options.analogue)
     || (gPuppyCam.stick2[1] < -PUPPYCAM_DEADZONE && !gPuppyCam.stickN[1])
     || (gPlayer1Controller->buttonPressed & (A_BUTTON | B_BUTTON))) {
        if (gPuppyCam.mode3Flags & PUPPYCAM_MODE3_ZOOMED_IN) {
            gPuppyCam.stickN[1] = 1;
            gPuppyCam.mode3Flags |= PUPPYCAM_MODE3_ZOOMED_MED;
            gPuppyCam.mode3Flags &= ~(PUPPYCAM_MODE3_ZOOMED_IN | PUPPYCAM_MODE3_ENTER_FIRST_PERSON);
            gPuppyCam.zoomTarget = gPuppyCam.zoomPoints[1];

            play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
        }
    }
}

// Handles C Button inputs for modes that have held inputs, rather than presses.
static void puppycam_input_hold(void) {
    f32 ivX = ((gPuppyCam.options.invertX * 2) - 1) * (gPuppyCam.options.sensitivityX / 100.f);
    f32 ivY = ((gPuppyCam.options.invertY * 2) - 1) * (gPuppyCam.options.sensitivityY / 100.f);
    s8 stickMag[2] = { 100, 100 };

    if (gPuppyCam.options.debugCam) {
        gPuppyCam.flags = PUPPYCAM_BEHAVIOUR_FREE | PUPPYCAM_BEHAVIOUR_YAW_ROTATION | PUPPYCAM_BEHAVIOUR_PITCH_ROTATION;
#ifdef MOUSE_ACTIONS
        if (configMouse && gPuppyCam.mouse) {
            return;
        }
#endif
    } else {
        gPuppyCam.flags &= ~PUPPYCAM_BEHAVIOUR_FREE;
    }

    // Analogue Camera stuff. If it fails to find an input, then it just sets stickmag to 100, which after calculations means the value goes unchanged.
    if (gPuppyCam.options.analogue && gPuppyCam.options.inputType != PUPPYCAM_INPUT_TYPE_CLASSIC) {
        stickMag[0] = gPuppyCam.stick2[0] * 1.25f;
        stickMag[1] = gPuppyCam.stick2[1] * 1.25f;
    }

    // In theory this shouldn't be necessary, but it's nice to cover all bases.
    if (!(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_YAW_ROTATION)) {
        return;
    }

    if ((!gPuppyCam.options.analogue || gPuppyCam.options.inputType == PUPPYCAM_INPUT_TYPE_CLASSIC) && !(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_FREE)) {
        switch (gPuppyCam.options.inputType) {
            default: 
            case PUPPYCAM_INPUT_TYPE_DOUBLE_TAP:   puppycam_input_hold_preset1(ivX); puppycam_input_pitch(); puppycam_input_zoom(); puppycam_input_centre(); break;
            case PUPPYCAM_INPUT_TYPE_SINGLE_PRESS: puppycam_input_hold_preset2(ivX); puppycam_input_pitch(); puppycam_input_zoom(); puppycam_input_centre(); break;
            case PUPPYCAM_INPUT_TYPE_CLASSIC:      puppycam_input_hold_preset3();                                                   puppycam_input_centre(); break;
        }
    } else {
        puppycam_input_hold_preset1(ivX);
        puppycam_input_pitch();
        puppycam_input_zoom();
        puppycam_input_centre();
    }

    gPuppyCam.framesSinceC[0]++;
    gPuppyCam.framesSinceC[1]++;

    gPuppyCam.yawAcceleration = CLAMP(gPuppyCam.yawAcceleration, -100, 100);

    gPuppyCam.yawTarget += (12 * gPuppyCam.yawAcceleration * ivX) * (stickMag[0] * 0.01f);
    gPuppyCam.pitchTarget += ((4 + gPuppyCam.moveFlagAdd) * gPuppyCam.pitchAcceleration * ivY) * (stickMag[1] * 0.01f);
}

// Handles C Button inputs for modes that have pressed inputs, rather than held.
static void puppycam_input_press(void)
{
    f32 ivX = ((gPuppyCam.options.invertX * 2) - 1) * (gPuppyCam.options.sensitivityX / 100.f);
    f32 ivY = ((gPuppyCam.options.invertY * 2) - 1) * (gPuppyCam.options.sensitivityY / 100.f);
    s8 stickMag = 0;

    // Analogue Camera stuff. If it fails to find an input, then it just sets stickmag to 100, which after calculations means the value goes unchanged.
    if (gPuppyCam.options.analogue) {
        stickMag = gPuppyCam.stick2[0] * 1.25f;
    } else {
        stickMag = 100;
    }
    // Just in case it happens to be nonzero.
    gPuppyCam.yawAcceleration = 0;

    // In theory this shouldn't be necessary, but it's nice to cover all bases.
    if (!(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_YAW_ROTATION)) {
        return;
    }

    if (((gPlayer1Controller->buttonPressed & L_CBUTTONS) && !gPuppyCam.options.analogue) || (gPuppyCam.stickN[0] == 0 && gPuppyCam.stick2[0] < -PUPPYCAM_DEADZONE)) {
        gPuppyCam.stickN[0] = 1;
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR) {
            gPuppyCam.yawTarget -= 0x2000 * ivX;
        } else {
            gPuppyCam.yawTarget -= 0x4000 * ivX;
        }
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
    }

    if (((gPlayer1Controller->buttonPressed & R_CBUTTONS) && !gPuppyCam.options.analogue) || (gPuppyCam.stickN[0] == 0 && gPuppyCam.stick2[0] > PUPPYCAM_DEADZONE)) {
        gPuppyCam.stickN[0] = 1;
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR) {
            gPuppyCam.yawTarget += 0x2000 * ivX;
        } else {
            gPuppyCam.yawTarget += 0x4000 * ivX;
        }
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
    }
    puppycam_input_pitch();
    puppycam_input_zoom();
    puppycam_input_centre();
    gPuppyCam.pitchTarget += ((4 + gPuppyCam.moveFlagAdd) * gPuppyCam.pitchAcceleration * ivY) * (stickMag * 0.01f);
}

void puppycam_debug_view(void) {
    if (gPuppyCam.debugFlags & PUPPYDEBUG_LOCK_CONTROLS) {
        if (abss(gPlayer1Controller->rawStickX) > PUPPYCAM_DEADZONE) {
            gPuppyCam.pos[0] += (gPlayer1Controller->rawStickX / 4) * -sins(gPuppyCam.yawTarget);
            gPuppyCam.pos[2] += (gPlayer1Controller->rawStickX / 4) *  coss(gPuppyCam.yawTarget);
        }
        if (abss(gPlayer1Controller->rawStickY) > PUPPYCAM_DEADZONE) {
            gPuppyCam.pos[0] += (gPlayer1Controller->rawStickY / 4) *  coss(gPuppyCam.yawTarget);
            gPuppyCam.pos[1] += (gPlayer1Controller->rawStickY / 4) *  sins(gPuppyCam.pitchTarget);
            gPuppyCam.pos[2] += (gPlayer1Controller->rawStickY / 4) *  sins(gPuppyCam.yawTarget);
        }
        if (gPlayer1Controller->buttonDown & (Z_TRIG | L_TRIG)) {
            gPuppyCam.pos[1] -= 20;
        }
        if (gPlayer1Controller->buttonDown & R_TRIG) {
            gPuppyCam.pos[1] += 20;
        }
        gPuppyCam.focus[0] = gPuppyCam.pos[0] + (100 * coss(gPuppyCam.yawTarget));
        gPuppyCam.focus[1] = gPuppyCam.pos[1] + (100 * sins(gPuppyCam.pitchTarget));
        gPuppyCam.focus[2] = gPuppyCam.pos[2] + (100 * sins(gPuppyCam.yawTarget));
    } else {
        if (gPuppyCam.debugFlags & PUPPYDEBUG_TRACK_MARIO) {
            vec3_copy(gPuppyCam.focus, &gPuppyCam.targetObj->oPosX);
        }

        gPuppyCam.yawTarget   = atan2s(gPuppyCam.pos[2] - gPuppyCam.focus[2], gPuppyCam.pos[0] - gPuppyCam.focus[0]);
        gPuppyCam.pitchTarget = atan2s(gPuppyCam.pos[1] - gPuppyCam.focus[1], 100);
    }

    gPuppyCam.yaw   = gPuppyCam.yawTarget;
    gPuppyCam.pitch = gPuppyCam.pitchTarget;

    if ((gPlayer1Controller->buttonPressed & A_BUTTON) && (gPuppyCam.debugFlags & PUPPYDEBUG_LOCK_CONTROLS)) {
        vec3f_set(gMarioState->pos, gPuppyCam.pos[0], gPuppyCam.pos[1], gPuppyCam.pos[2]);
    }
    if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        gPuppyCam.debugFlags ^= PUPPYDEBUG_LOCK_CONTROLS;
    }

    if ((gPlayer1Controller->buttonPressed & R_TRIG) && !(gPuppyCam.debugFlags & PUPPYDEBUG_LOCK_CONTROLS)) {
        gPuppyCam.debugFlags ^= PUPPYDEBUG_TRACK_MARIO;
    }
}

#ifdef MOUSE_ACTIONS
// Mouse control support for PC Platforms
static void puppycam_input_mouse(void) {
    f32 ivX = ((gPuppyCam.options.invertX * 2) - 1) * (gPuppyCam.options.sensitivityX / 100.f);
    f32 ivY = ((gPuppyCam.options.invertY * 2) - 1) * (gPuppyCam.options.sensitivityY / 100.f);

    if (configMouse && gPuppyCam.mouse && gPuppyCam.options.inputType != PUPPYCAM_INPUT_TYPE_CLASSIC) {
        gMouseHasCenterControl = TRUE;

        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_FREE) {
            if (gPlayer1Controller->buttonDown & A_BUTTON) {
                gPuppyCam.yawTarget += ivX * gMouseXPos * 32;
                gPuppyCam.pitchTarget += ivY * gMouseYPos * 32;
            }
        } else {
            gPuppyCam.yawTarget += ivX * gMouseXPos * 16;
            gPuppyCam.pitchTarget += ivY * gMouseYPos * 16;
        }
    } else {
        gMouseHasCenterControl = FALSE;
    }
}

// Free debug view to better fit with a mouse
void puppycam_debug_view_mouse(void)
{
    gPuppyCam.debugFlags |= PUPPYDEBUG_LOCK_CONTROLS;
    gPuppyCam.debugFlags &= ~PUPPYDEBUG_TRACK_MARIO;

    // Stick controls
    if (ABS(gPlayer1Controller->rawStickX) > PUPPYCAM_DEADZONE)
    {
        gPuppyCam.pos[0] += (gPlayer1Controller->rawStickX/2) * -sins(gPuppyCam.yawTarget);
        gPuppyCam.pos[2] += (gPlayer1Controller->rawStickX/2) * coss(gPuppyCam.yawTarget);
    }

    if (ABS(gPlayer1Controller->rawStickY) > PUPPYCAM_DEADZONE)
    {
        gPuppyCam.pos[0] += (gPlayer1Controller->rawStickY/2) * coss(gPuppyCam.yawTarget);
        gPuppyCam.pos[1] += (gPlayer1Controller->rawStickY/2) * sins(gPuppyCam.pitchTarget);
        gPuppyCam.pos[2] += (gPlayer1Controller->rawStickY/2) * sins(gPuppyCam.yawTarget);
    }

#define STATIC_SPEED 64
    // C - Controls
    if (gPlayer1Controller->buttonDown & D_CBUTTONS)
        gPuppyCam.pos[1] -= STATIC_SPEED;

    if (gPlayer1Controller->buttonDown & U_CBUTTONS)
        gPuppyCam.pos[1] += STATIC_SPEED;

    if (gPlayer1Controller->buttonDown & L_CBUTTONS)
    {
        gPuppyCam.pos[0] += (-STATIC_SPEED) * -sins(gPuppyCam.yawTarget);
        gPuppyCam.pos[2] += (-STATIC_SPEED) * coss(gPuppyCam.yawTarget);
    }

    if (gPlayer1Controller->buttonDown & R_CBUTTONS)
    {
        gPuppyCam.pos[0] += (STATIC_SPEED) * -sins(gPuppyCam.yawTarget);
        gPuppyCam.pos[2] += (STATIC_SPEED) * coss(gPuppyCam.yawTarget);
    }
#undef STATIC_SPEED

    gPuppyCam.focus[0] = gPuppyCam.pos[0] + (100 *coss(gPuppyCam.yawTarget));
    gPuppyCam.focus[1] = gPuppyCam.pos[1] + (100 *sins(gPuppyCam.pitchTarget));
    gPuppyCam.focus[2] = gPuppyCam.pos[2] + (100 *sins(gPuppyCam.yawTarget));

    gPuppyCam.yaw = gPuppyCam.yawTarget;
    gPuppyCam.pitch = gPuppyCam.pitchTarget;

    if (gPlayer1Controller->buttonPressed & B_BUTTON)
    {
        vec3f_set(gMarioState->pos, gPuppyCam.pos[0], gPuppyCam.pos[1], gPuppyCam.pos[2]);
    }
}
#endif

static void puppycam_view_panning(void) {
    s32 expectedPanX, expectedPanZ;
    s32 height = gPuppyCam.targetObj->oPosY;
    s32 panEx = (gPuppyCam.zoomTarget >= 1000) * 160; // Removes the basic panning when idling if the zoom level is at the closest.
    f32 slideSpeed = 1;

    f32 panMulti = CLAMP(gPuppyCam.zoom / (f32)gPuppyCam.zoomPoints[2], 0.f, 1.f);
    if (gPuppyCam.options.inputType == PUPPYCAM_INPUT_TYPE_CLASSIC) {
        panMulti /= 2;
    }

    if ((gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_PANSHIFT)
     && gMarioState->action != ACT_HOLDING_BOWSER
     && gMarioState->action != ACT_SLEEPING
     && gMarioState->action != ACT_START_SLEEPING) {
        if (gMarioState->action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE) {
            slideSpeed = 10;
        }

        expectedPanX = LENSIN(panEx + (200 * (gMarioState->forwardVel / 320.f)), gMarioState->faceAngle[1]) * panMulti;
        expectedPanZ = LENCOS(panEx + (200 * (gMarioState->forwardVel / 320.f)), gMarioState->faceAngle[1]) * panMulti;

        slideSpeed *= 0.02f;
        gPuppyCam.pan[0] = approach_f32_asymptotic(gPuppyCam.pan[0], expectedPanX, slideSpeed);
        gPuppyCam.pan[2] = approach_f32_asymptotic(gPuppyCam.pan[2], expectedPanZ, slideSpeed);
        if (gMarioState->vel[1] == 0.0f) {
            f32 panFloor = find_floor_height((s16)(gPuppyCam.targetObj->oPosX + expectedPanX),
                                             (s16)(gPuppyCam.targetObj->oPosY + 200),
                                             (s16)(gPuppyCam.targetObj->oPosZ + expectedPanZ));
            panFloor = CLAMP(panFloor, (gPuppyCam.targetObj->oPosY - 50), (gPuppyCam.targetObj->oPosY + 50));
            // If the floor is lower than 150 units below Mario, then ignore the Y value and tilt the camera instead.
            if (panFloor <= gPuppyCam.targetObj->oPosY - 150) {
                panFloor = gPuppyCam.targetObj->oPosY;
                gPuppyCam.edgePitch = approach_s32(gPuppyCam.edgePitch, -0x2000, 0x80, 0x80);
            } else {
                gPuppyCam.edgePitch = approach_s32(gPuppyCam.edgePitch, 0, 0x100, 0x100);
            }
            gPuppyCam.pan[1] = approach_f32_asymptotic(gPuppyCam.pan[1], panFloor - height, 0.025f);
        } else {
            gPuppyCam.pan[1] = approach_f32_asymptotic(gPuppyCam.pan[1], 0, 0.05f);
        }
    } else {
        vec3_zero(gPuppyCam.pan);
    }
}

void puppycam_terrain_angle(void) {
    f32 adjustSpeed;
    s32 floor2 = find_floor_height(gPuppyCam.pos[0], gPuppyCam.pos[1] + 100, gPuppyCam.pos[2]);
    s32 ceil = CELL_HEIGHT_LIMIT; // find_ceil(gPuppyCam.pos[0], gPuppyCam.pos[1] + 100, gPuppyCam.pos[2]);
    s32 farFromSurface;
    s16 floorPitch;
    s32 gotTheOkay = FALSE;

    if ((gMarioState->action & ACT_FLAG_SWIMMING) || !(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_HEIGHT_HELPER)) {
        gPuppyCam.intendedTerrainPitch = 0;
        adjustSpeed = 0.25f;
        farFromSurface = TRUE;
    } else {
        adjustSpeed = CLAMP(MAX(gMarioState->forwardVel / 400.0f, gPuppyCam.yawAcceleration / 100.0f), 0.05f, 1.0f);

        f32 x = gPuppyCam.targetObj->oPosX - (10 * sins(gPuppyCam.yaw));
        f32 z = gPuppyCam.targetObj->oPosZ - (10 * coss(gPuppyCam.yaw));

        f32 floorHeight = find_floor_height(x, gPuppyCam.targetObj->oPosY + 100, z);
        f32 diff = gMarioState->floorHeight - floorHeight;

        if (absf(diff) > 50.f) {
            gPuppyCam.intendedTerrainPitch = 0;
        } else {
            floorPitch = -atan2s(30.0f, diff);
            gPuppyCam.intendedTerrainPitch = approach_f32_asymptotic(gPuppyCam.intendedTerrainPitch, floorPitch, adjustSpeed);
            gotTheOkay = TRUE;
        }

        // Ensures that the camera is below and above floors and ceilings. It ignores this rule for each if the camera's headed upwards anyway.
        farFromSurface = ((gPuppyCam.pos[1] > floor2 + 50 || gPuppyCam.intendedTerrainPitch < gPuppyCam.terrainPitch) && (gPuppyCam.pos[1] < ceil - 50 || gPuppyCam.intendedTerrainPitch > gPuppyCam.terrainPitch));

        // If the camera is too close to a vertical obstruction, it'll make the intended pitch much further away, making it swivel faster.
        if (!farFromSurface && gotTheOkay) {
            gPuppyCam.intendedTerrainPitch = approach_f32_asymptotic(gPuppyCam.intendedTerrainPitch, floorPitch, adjustSpeed * 3);
        }
    }

    if (farFromSurface) {
        gPuppyCam.terrainPitch = approach_f32_asymptotic(gPuppyCam.terrainPitch, gPuppyCam.intendedTerrainPitch, adjustSpeed);
    }
}

// Checks the bounding box of a puppycam volume. If it's inside, then set the pointer to the current index.
static s32 puppycam_check_volume_bounds(struct sPuppyVolume *volume, s32 index) {
    s32 rel[3];
    s32 pos[2];

    if (sPuppyVolumeStack[index]->room != gMarioCurrentRoom && sPuppyVolumeStack[index]->room != -1) {
        return FALSE;
    }
    if (sPuppyVolumeStack[index]->shape == PUPPYVOLUME_SHAPE_BOX) {
        // Fetch the relative position. to the triggeree.
        vec3_diff(rel, sPuppyVolumeStack[index]->pos, &gPuppyCam.targetObj->oPosX);
        // Use the dark, forbidden arts of trig to rotate the volume.
        pos[0] = (rel[2] * sins(sPuppyVolumeStack[index]->rot)) + (rel[0] * coss(sPuppyVolumeStack[index]->rot));
        pos[1] = (rel[2] * coss(sPuppyVolumeStack[index]->rot)) - (rel[0] * sins(sPuppyVolumeStack[index]->rot));

        // Now compare values.
        if (-sPuppyVolumeStack[index]->radius[0] < pos[0] && pos[0] < sPuppyVolumeStack[index]->radius[0]
         && -sPuppyVolumeStack[index]->radius[1] < rel[1] && rel[1] < sPuppyVolumeStack[index]->radius[1]
         && -sPuppyVolumeStack[index]->radius[2] < pos[1] && pos[1] < sPuppyVolumeStack[index]->radius[2]) {
            *volume = *sPuppyVolumeStack[index];
            return TRUE;
        }
    } else if (sPuppyVolumeStack[index]->shape == PUPPYVOLUME_SHAPE_CYLINDER) {
        // s16 dir;
        vec3_diff(rel, sPuppyVolumeStack[index]->pos, &gPuppyCam.targetObj->oPosX);
        f32 dist = (sqr(rel[0]) + sqr(rel[2]));

        f32 distCheck = (dist < sqr(sPuppyVolumeStack[index]->radius[0]));

        if (-sPuppyVolumeStack[index]->radius[1] < rel[1] && rel[1] < sPuppyVolumeStack[index]->radius[1] && distCheck) {
            *volume = *sPuppyVolumeStack[index];
            return TRUE;
        }
    }

    return FALSE;
}

// Handles wall adjustment when wall kicking.
void puppycam_wall_angle(void) {
    struct Surface *wall;
    struct WallCollisionData cData;

    if (!(gMarioState->action & ACT_WALL_KICK_AIR) || ((gMarioState->action & ACT_FLAG_AIR) && absf(gMarioState->forwardVel) < 16.0f) || !(gMarioState->action & ACT_FLAG_AIR)) {
        return;
    }
    cData.x = gPuppyCam.targetObj->oPosX;
    cData.y = gPuppyCam.targetObj->oPosY;
    cData.z = gPuppyCam.targetObj->oPosZ;
    cData.radius = 150.0f;
    cData.offsetY = 0;

    if (find_wall_collisions(&cData)) {
        wall = cData.walls[cData.numWalls - 1];
    } else {
        return;
    }
    s16 wallYaw = atan2s(wall->normal.z, wall->normal.x) + 0x4000;

    wallYaw -= gPuppyCam.yawTarget;
    if (wallYaw % 0x4000) {
        wallYaw += 0x4000 - (wallYaw % 0x4000);
    }
    gPuppyCam.yawTarget = approach_s32(gPuppyCam.yawTarget, wallYaw, 0x200, 0x200);
}

void puppycam_projection_behaviours(void) {
    f32 turnRate = 1;
    f32 turnMag = absf(gPlayer1Controller->rawStickX / 80.0f);

    // This will only be executed if Mario's the target. If it's not, it'll reset the
    if (gPuppyCam.targetObj == gMarioState->marioObj) {
        if ((
             (gPuppyCam.options.turnAggression > 0)
          && (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_TURN_HELPER)
          && !(gPuppyCam.flags & (PUPPYCAM_BEHAVIOUR_INPUT_8DIR | PUPPYCAM_BEHAVIOUR_INPUT_4DIR))
          && gMarioState->vel[1] == 0.0f
          && gPuppyCam.options.inputType != PUPPYCAM_INPUT_TYPE_CLASSIC
         ) || gMarioState->action == ACT_SHOT_FROM_CANNON
           || gMarioState->action == ACT_FLYING) { // Holy hell this is getting spicy.
            // With turn aggression enabled, or if Mario's sliding, adjust the camera view behind mario.
            if (gPuppyCam.options.turnAggression > 0 || gMarioState->action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE || gMarioState->action == ACT_SHOT_FROM_CANNON || gMarioState->action == ACT_FLYING) {
                if (gMarioState->action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE) {
                    turnRate = 4; // If he's sliding, do it 4x as fast.
                }
                if (gMarioState->action == ACT_SHOT_FROM_CANNON || gMarioState->action == ACT_FLYING) {
                    turnMag = 1;
                }
                // The deal here, is if Mario's moving, or he's sliding and the camera's within 90 degrees behind him, it'll auto focus behind him, with an intensity based on the camera's centre speed.
                // It also scales with forward velocity, so it's a gradual effect as he speeds up.
                if ((abss(gPlayer1Controller->rawStickX) > 20 && !(gMarioState->action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE))
                 || (gMarioState->action == ACT_SHOT_FROM_CANNON)
                 || ((gMarioState->action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE) && (s16)absi((((gPuppyCam.yaw + 0x8000) % 0xFFFF) - 0x8000) - (((gMarioState->faceAngle[1]) % 0xFFFF) - 0x8000)) < 0x3000)) {
                    gPuppyCam.yawTarget = approach_angle(gPuppyCam.yawTarget, (gMarioState->faceAngle[1] + 0x8000), ((gPuppyCam.options.turnAggression * 10) * absf(gMarioState->forwardVel / 32) * turnMag * turnRate));
                }
            }
        } else { // If none of the above is true, it'll attempt to do this instead.
            // If the camera's in these modes, snap the yaw to prevent desync.
            if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR) {
                if (gPuppyCam.yawTarget % 0x2000) {
                    gPuppyCam.yawTarget += 0x2000 - (gPuppyCam.yawTarget % 0x2000);
                }
            }
            if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_4DIR) {
                if (gPuppyCam.yawTarget % 0x4000) {
                    gPuppyCam.yawTarget += 0x4000 - (gPuppyCam.yawTarget % 0x4000);
                }
            }
        }

        // This is the base floor height when stood on the ground. It's used to set a baseline for where the camera sits while Mario remains a height from this point, so it keeps a consistent motion.
        f32 floorHeight = find_floor_height(gPuppyCam.targetObj->oPosX, gPuppyCam.targetObj->oPosY, gPuppyCam.targetObj->oPosZ);
        gPuppyCam.targetFloorHeight = CLAMP(floorHeight, gPuppyCam.targetObj->oPosY - 350, gPuppyCam.targetObj->oPosY + 300);
        gPuppyCam.lastTargetFloorHeight = approach_f32_asymptotic(gPuppyCam.lastTargetFloorHeight, gPuppyCam.targetFloorHeight,
                                                                  CLAMP((absf(gMarioState->vel[1]) - 17.f) / 200.f, 0, 0.1f)
                                                                + CLAMP((absf(gPuppyCam.targetFloorHeight - gPuppyCam.lastTargetFloorHeight) - 30.f) / 300.f, 0, 0.1f));

        if (gMarioState->action == ACT_SLEEPING || gMarioState->action == ACT_START_SLEEPING) {
            gPuppyCam.zoom = approach_f32_asymptotic(gPuppyCam.zoom, gPuppyCam.zoomPoints[0], 0.01f);
        } else if ((gMarioState->action & ACT_FLAG_SWIMMING_OR_FLYING && gMarioState->waterLevel - 100 - gMarioState->pos[1] > 5) || gMarioState->action == ACT_FLYING) {
            // When moving underwater or flying, the camera will zoom in on Mayro.
            gPuppyCam.zoom = approach_f32_asymptotic(gPuppyCam.zoom, MAX(gPuppyCam.zoomTarget / 1.5f, gPuppyCam.zoomPoints[0]), 0.2f);
        } else {
            gPuppyCam.zoom = approach_f32_asymptotic(gPuppyCam.zoom, gPuppyCam.zoomTarget, 0.2f);
        }
        // Attempts at automatic adjustment that only apply when moving or jumping.
        if ((gMarioState->action & (ACT_FLAG_MOVING | ACT_FLAG_AIR)) || ((gMarioState->action & ACT_FLAG_SWIMMING) && !(gMarioState->waterLevel - 100 - gMarioState->pos[1] > 5) && gMarioState->forwardVel != 0.0f)) {
            // Clamp the height when moving. You can still look up and down to a reasonable degree but it readjusts itself the second you let go.
            if (gPuppyCam.pitchTarget > 0x3800) gPuppyCam.pitchTarget = approach_f32_asymptotic(gPuppyCam.pitchTarget, 0x3800, 0.2f);
            if (gPuppyCam.pitchTarget < 0x2000) gPuppyCam.pitchTarget = approach_f32_asymptotic(gPuppyCam.pitchTarget, 0x2000, 0.2f);
        }

        // Applies a light outward zoom to the camera when moving. Sets it back to 0 when not moving.
        if (gMarioState->forwardVel > 0) {
            gPuppyCam.moveZoom = approach_f32(gPuppyCam.moveZoom, (100.0f * (gMarioState->forwardVel / 32.0f)), (gMarioState->forwardVel / 10), (gMarioState->forwardVel / 10));
        } else {
            gPuppyCam.moveZoom = approach_f32(gPuppyCam.moveZoom, 0, 5, 5);
        }

        // Zooms the camera in further when underwater.
        // 0x38C0 = ~80 Degrees
        if (gPuppyCam.pitch > 0x38C0 && abss(gPuppyCam.swimPitch) < 100) {
            gPuppyCam.zoom = approach_f32_asymptotic((f32)gPuppyCam.zoom, 250.0f, CLAMP((f32)((gPuppyCam.pitch - 0x38C0) / 3072.0f), 0.0f, 1.0f));
        }

        if (!(gMarioState->action & ACT_FLAG_SWIMMING_OR_FLYING)) {
            gPuppyCam.floorY[0] = softClamp(gPuppyCam.targetObj->oPosY - gPuppyCam.lastTargetFloorHeight, -180, PUPPYCAM_FLOOR_DIST_UP);
            gPuppyCam.floorY[1] = softClamp(gPuppyCam.targetObj->oPosY - gPuppyCam.lastTargetFloorHeight, -180, PUPPYCAM_FLOOR_DIST_DOWN);
            gPuppyCam.swimPitch = approach_f32_asymptotic(gPuppyCam.swimPitch, 0, 0.2f);
        } else {
            gPuppyCam.floorY[0] = 0;
            gPuppyCam.floorY[1] = 0;
            gPuppyCam.targetFloorHeight     = gPuppyCam.targetObj->oPosY;
            gPuppyCam.lastTargetFloorHeight = gPuppyCam.targetObj->oPosY;

            gPuppyCam.yawTarget = approach_angle(gPuppyCam.yawTarget, (gMarioState->faceAngle[1] + 0x8000), (1000 * (gMarioState->forwardVel / 32)));
            if ((gMarioState->waterLevel - 100 - gMarioState->pos[1] > 5 && (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_PITCH_ROTATION)) || gMarioState->action == ACT_FLYING || gMarioState->action == ACT_SHOT_FROM_CANNON) {
                gPuppyCam.swimPitch = approach_f32_asymptotic(gPuppyCam.swimPitch, gMarioState->faceAngle[0] / 10, 0.05f);
            } else {
                gPuppyCam.swimPitch = approach_f32_asymptotic(gPuppyCam.swimPitch, 0, 0.2f);
            }
        }

        // This sets the view offset from Mario. It accentuates a bit further when moving.
        puppycam_view_panning();

        // This sets a pseudo tilt offset based on the floor heights in front and behind mario.
        puppycam_terrain_angle();

        // This will shift the intended yaw when wall kicking, to align with the wall being kicked.
        // puppycam_wall_angle();

    } else {
        puppycam_reset_values();
    }
}

// Support for most vanilla camera actions
static void puppycam_vanilla_actions(void) {
    // Adds support for wing mario tower
    if (gMarioState->floor && gMarioState->floor->type == SURFACE_LOOK_UP_WARP
        && save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= WING_CAP_WARP_STAR_REQ) {
        if (gPuppyCam.pitch > 0x6000 && gMarioState->forwardVel == 0
            && (gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE) {
            level_trigger_warp(gMarioState, WARP_OP_UNKNOWN_01);
        }
    }

    if (gSecondCameraFocus != NULL) {
        // Adds support for Bowser second camera focus
        if (gCurrLevelNum == LEVEL_BOWSER_1 || gCurrLevelNum == LEVEL_BOWSER_2 || gCurrLevelNum == LEVEL_BOWSER_3) {
            gPuppyCam.targetObj2 = gSecondCameraFocus;
        }

        // Adds support for BOB - WF bosses second camera focus
        if (gMarioState->floor && gMarioState->floor->type == SURFACE_BOSS_FIGHT_CAMERA) {
            gPuppyCam.targetObj2 = gSecondCameraFocus;
        } else {
            gPuppyCam.targetObj2 = NULL;
        }

    } else {
        gPuppyCam.targetObj2 = NULL;
    }
}

//void puppycam_shake(s16 x, s16 y, s16 z) {
//}

static void puppycam_analogue_stick(void)
{
    if (!gPuppyCam.options.analogue)
        return;

    // I make the X axis negative, so that the movement reflects the Cbuttons.
    #ifdef TARGET_N64
    gPuppyCam.stick2[0] = -gPlayer2Controller->rawStickX;
    gPuppyCam.stick2[1] = gPlayer2Controller->rawStickY;
    #else
    gPuppyCam.stick2[0] = -gPlayer1Controller->extStickX;
    gPuppyCam.stick2[1] = gPlayer1Controller->extStickY;
    #endif

    if (absi(gPuppyCam.stick2[0]) < PUPPYCAM_DEADZONE) {
        gPuppyCam.stick2[0] = 0;
        gPuppyCam.stickN[0] = 0;
    }
    if (absi(gPuppyCam.stick2[1]) < PUPPYCAM_DEADZONE) {
        gPuppyCam.stick2[1] = 0;
        gPuppyCam.stickN[1] = 0;
    }
}

/// This is the highest level of the basic steps that go into the code. Anything above is called from these following functions.

// The centrepiece behind the input side of PuppyCam. The C buttons branch off.
static void puppycam_input_core(void) {
    puppycam_analogue_stick();
    gPuppyCam.moveFlagAdd = 0;

    // Decide which input for left and right C buttons to use based on behaviour type.
    if (gPuppyCam.flags & (PUPPYCAM_BEHAVIOUR_INPUT_NORMAL | PUPPYCAM_BEHAVIOUR_FREE)) {
        puppycam_input_hold();
    } else if (gPuppyCam.flags & (PUPPYCAM_BEHAVIOUR_INPUT_8DIR | PUPPYCAM_BEHAVIOUR_INPUT_4DIR)) {
        puppycam_input_press();
    }

#ifdef MOUSE_ACTIONS
    puppycam_input_mouse();
#endif
}

// Calculates the base position the camera should be, before any modification.
static void puppycam_projection(void) {
    Vec3s targetPos, targetPos2, targetPos3;
    s16 pitchTotal;
    s32 panD = (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_PANSHIFT) / 8192;

    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_FREE) {
        puppycam_reset_values();
#ifdef MOUSE_ACTIONS
        if (configMouse && gPuppyCam.mouse) {
            puppycam_debug_view_mouse();
        } else {
            puppycam_debug_view();
        }
#else
        puppycam_debug_view();
#endif
        return;
    }

    // Extra behaviours that get tacked onto the projection. Will be completely ignored if there is no target object.
    puppycam_projection_behaviours();
    // These are what the base rotations aspire to be.
    gPuppyCam.pitch       = CLAMP(gPuppyCam.pitch,       0x1000, 0x7000);
    gPuppyCam.pitchTarget = CLAMP(gPuppyCam.pitchTarget, 0x1000, 0x7000);
    // These are the base rotations going to be used.
    gPuppyCam.yaw   = gPuppyCam.yawTarget   - approach_f32_asymptotic((s16)(gPuppyCam.yawTarget   - gPuppyCam.yaw  ), 0, 0.3335f);
    gPuppyCam.pitch = gPuppyCam.pitchTarget - approach_f32_asymptotic((s16)(gPuppyCam.pitchTarget - gPuppyCam.pitch), 0, 0.3335f);
    // This adds the pitch effect when underwater, which is capped so it doesn't get out of control. If you're not swimming, swimpitch is 0, so it's normal.
    pitchTotal = CLAMP(gPuppyCam.pitch + (gPuppyCam.swimPitch * 10) + gPuppyCam.edgePitch + gPuppyCam.terrainPitch, 800, 0x7800);

    if (gPuppyCam.targetObj) {
        vec3f_to_vec3s(targetPos, &gPuppyCam.targetObj->oPosX);
        vec3s_copy(targetPos3, targetPos);
        if (gPuppyCam.targetObj2) {
            vec3f_to_vec3s(targetPos2, &gPuppyCam.targetObj2->oPosX);
            targetPos3[0] = (s16)approach_f32_asymptotic(targetPos[0], targetPos2[0], 0.5f);
            targetPos3[1] = (s16)approach_f32_asymptotic(targetPos[1], targetPos2[1], 0.5f);
            targetPos3[2] = (s16)approach_f32_asymptotic(targetPos[2], targetPos2[2], 0.5f);
            Vec3s d;
            vec3_diff(d, targetPos, targetPos2);
            gPuppyCam.targetDist[0] = approach_f32_asymptotic(gPuppyCam.targetDist[0], (absi(LENCOS(sqrtf(sqr(d[0]) + sqr(d[2])),
                            (s16)absi((((gPuppyCam.yaw + 0x8000) % 0xFFFF) - 0x8000) - ((atan2s(d[2], d[0])) % 0xFFFF) - 0x8000) + 0x4000))), 0.2f);
        } else {
            gPuppyCam.targetDist[0] = approach_f32_asymptotic(gPuppyCam.targetDist[0], 0, 0.2f);
        }

        gPuppyCam.targetDist[1] = gPuppyCam.targetDist[0] + gPuppyCam.zoom + gPuppyCam.moveZoom;

        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_X_MOVEMENT) gPuppyCam.focus[0] = targetPos3[0] + gPuppyCam.shake[0] + (gPuppyCam.pan[0] * gPuppyCam.targetDist[1] / gPuppyCam.zoomPoints[2]) * panD;
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_Y_MOVEMENT) gPuppyCam.focus[1] = targetPos3[1] + gPuppyCam.shake[1] + (gPuppyCam.pan[1] * gPuppyCam.targetDist[1] / gPuppyCam.zoomPoints[2]) + gPuppyCam.povHeight - gPuppyCam.floorY[0] + (gPuppyCam.swimPitch / 10);
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_Z_MOVEMENT) gPuppyCam.focus[2] = targetPos3[2] + gPuppyCam.shake[2] + (gPuppyCam.pan[2] * gPuppyCam.targetDist[1] / gPuppyCam.zoomPoints[2]) * panD;

        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_X_MOVEMENT) gPuppyCam.pos[0] = gPuppyCam.targetObj->oPosX + LENSIN(LENSIN(gPuppyCam.targetDist[1], pitchTotal), gPuppyCam.yaw) + gPuppyCam.shake[0];
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_Y_MOVEMENT) gPuppyCam.pos[1] = gPuppyCam.targetObj->oPosY + gPuppyCam.povHeight + LENCOS(gPuppyCam.targetDist[1], pitchTotal) + gPuppyCam.shake[1] - gPuppyCam.floorY[1];
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_Z_MOVEMENT) gPuppyCam.pos[2] = gPuppyCam.targetObj->oPosZ + LENCOS(LENSIN(gPuppyCam.targetDist[1], pitchTotal), gPuppyCam.yaw) + gPuppyCam.shake[2];
    }

    puppycam_vanilla_actions();
}

// Calls any scripts to affect the camera, if applicable.
static void puppycam_script(void) {
    u16 i = 0;
    struct sPuppyVolume volume;

    if (gPuppyVolumeCount == 0 || !gPuppyCam.targetObj) {
        return;
    }
    for (i = 0; i < gPuppyVolumeCount; i++) {
        if (puppycam_check_volume_bounds(&volume, i)) {
            // First applies pos and focus, for the most basic of volumes.
            if (volume.angles != NULL) {
                if (volume.angles->pos[0]   != PUPPY_NULL) gPuppyCam.pos[0]   = volume.angles->pos[0];
                if (volume.angles->pos[1]   != PUPPY_NULL) gPuppyCam.pos[1]   = volume.angles->pos[1];
                if (volume.angles->pos[2]   != PUPPY_NULL) gPuppyCam.pos[2]   = volume.angles->pos[2];

                if (volume.angles->focus[0] != PUPPY_NULL) gPuppyCam.focus[0] = volume.angles->focus[0];
                if (volume.angles->focus[1] != PUPPY_NULL) gPuppyCam.focus[1] = volume.angles->focus[1];
                if (volume.angles->focus[2] != PUPPY_NULL) gPuppyCam.focus[2] = volume.angles->focus[2];


                if (volume.angles->yaw != PUPPY_NULL) {
                    gPuppyCam.yawTarget = volume.angles->yaw;
                    gPuppyCam.yaw       = volume.angles->yaw;

                    gPuppyCam.flags &= ~PUPPYCAM_BEHAVIOUR_YAW_ROTATION;
                } else {
                    gPuppyCam.yaw = atan2s(gPuppyCam.pos[2] - gPuppyCam.focus[2], gPuppyCam.pos[0] - gPuppyCam.focus[0]);
                }


                if (volume.angles->pitch != PUPPY_NULL) {
                    gPuppyCam.pitchTarget = volume.angles->pitch;
                    gPuppyCam.pitch       = volume.angles->pitch;

                    gPuppyCam.flags &= ~PUPPYCAM_BEHAVIOUR_PITCH_ROTATION;
                }

                if (volume.angles->zoom != PUPPY_NULL) {
                    gPuppyCam.zoomTarget = volume.angles->zoom;
                    gPuppyCam.zoom       = gPuppyCam.zoomTarget;

                    gPuppyCam.flags &= ~PUPPYCAM_BEHAVIOUR_ZOOM_CHANGE;
                }
            }

            // Adds and removes behaviour flags, as set.
            if (volume.flagsRemove) gPuppyCam.flags &= ~volume.flagsRemove;
            if (volume.flagsAdd   ) gPuppyCam.flags |=  volume.flagsAdd;
            if (volume.flagPersistance == PUPPYCAM_BEHAVIOUR_PERMANENT) {
                // Adds and removes behaviour flags, as set.
                if (volume.flagsRemove) gPuppyCam.intendedFlags &= ~volume.flagsRemove;
                if (volume.flagsAdd   ) gPuppyCam.intendedFlags |=  volume.flagsAdd;
            }

            // Last and probably least, check if there's a function attached, and call it, if so.
            if (volume.func) {
                volume.func();
            }
        }
    }
}

void puppycam_script_clear(void) {
    s32 i = 0;
    for (i = 0; i < gPuppyVolumeCount; i++) {
        mem_pool_free(gPuppyMemoryPool, sPuppyVolumeStack[i]);
    }
    gPuppyVolumeCount = 0;
}

// PUPPYCAM_OPACITY_TYPE_FADE
#define PUPPYCAM_OPACITY_FADE_START_DIST 500
#define PUPPYCAM_OPACITY_FADE_END_DIST   250

// PUPPYCAM_OPACITY_TYPE_POP
#define PUPPYCAM_OPACITY_POP_THRESHOLD   320

static void puppycam_opacity(void) {
    s16 fadeTypeStartDist = PUPPYCAM_OPACITY_FADE_START_DIST;
    s16 fadeTypeEndDist   = PUPPYCAM_OPACITY_FADE_END_DIST;

    s16 fadePopthreshold  = PUPPYCAM_OPACITY_POP_THRESHOLD;

    switch (gPuppyCam.options.opacityType) {
        default: // PUPPYCAM_OPACITY_TYPE_OFF
            gPuppyCam.opacity = 255;
            break;
        case PUPPYCAM_OPACITY_TYPE_FADE:
            gPuppyCam.opacity = CLAMP((f32)(((gPuppyCam.zoom-fadeTypeEndDist)/255.0f)*(fadeTypeStartDist-fadeTypeEndDist)), 0, 255);
            break;
        case PUPPYCAM_OPACITY_TYPE_POP:
            gPuppyCam.opacity = approach_s32(gPuppyCam.opacity, ((gPuppyCam.zoom > fadePopthreshold) ? 255 : 0), 51, 51);
            break;
    }
}

// Handles collision detection using ray casting.
static void puppycam_collision(void) {
    struct Surface *surf[2];
    Vec3f camdir[2];
    Vec3f hitpos[2];
    Vec3f target[2];
    s16 pitchTotal = CLAMP((gPuppyCam.pitch + (gPuppyCam.swimPitch * 10) + gPuppyCam.edgePitch + gPuppyCam.terrainPitch), 800, 0x7800);
    s32 dist[2];

    if (gPuppyCam.targetObj == NULL) {
        return;
    }
    // The ray, starting from the top
    vec3f_copy_y_off(target[0], &gPuppyCam.targetObj->oPosX, (gPuppyCam.povHeight - CLAMP(gPuppyCam.targetObj->oPosY - gPuppyCam.targetFloorHeight, 0, 300)));
    // The ray, starting from the bottom
    vec3f_copy_y_off(target[1], &gPuppyCam.targetObj->oPosX, (gPuppyCam.povHeight * 0.4f));

    camdir[0][0] = LENSIN(LENSIN(gPuppyCam.zoomTarget, pitchTotal), gPuppyCam.yaw) + gPuppyCam.shake[0];
    camdir[0][1] = LENCOS(gPuppyCam.zoomTarget, pitchTotal) + gPuppyCam.shake[1];
    camdir[0][2] = LENCOS(LENSIN(gPuppyCam.zoomTarget, pitchTotal), gPuppyCam.yaw) + gPuppyCam.shake[2];

    vec3f_copy(camdir[1], camdir[0]);

    find_surface_on_ray(target[0], camdir[0], &surf[0], hitpos[0], RAYCAST_FIND_SOLID);
    find_surface_on_ray(target[1], camdir[1], &surf[1], hitpos[1], RAYCAST_FIND_SOLID);
    resolve_and_return_wall_collisions(hitpos[0], 0.0f, 25.0f);
    resolve_and_return_wall_collisions(hitpos[1], 0.0f, 25.0f);
    Vec3f d;
    vec3f_diff(d, target[0], hitpos[0]);
    dist[0] = vec3_sumsq(d);
    vec3f_diff(d, target[1], hitpos[1]);
    dist[1] = vec3_sumsq(d);

    gPuppyCam.collisionDistance = gPuppyCam.zoomTarget;

    if (surf[0] && surf[1]) {
        gPuppyCam.collisionDistance = sqrtf(MAX(dist[0], dist[1]));
        if (gPuppyCam.zoom > gPuppyCam.collisionDistance) {
            gPuppyCam.zoom = MIN(gPuppyCam.collisionDistance, gPuppyCam.zoomTarget);
            if (gPuppyCam.zoom - gPuppyCam.zoomTarget < 5) {
                if (dist[0] >= dist[1]) {
                    vec3_copy(gPuppyCam.pos, hitpos[0]);
                } else {
                    vec3_copy_y_off(gPuppyCam.pos, hitpos[1], (gPuppyCam.povHeight * 0.6f));
                }
            }
        }
    }

    puppycam_opacity();
}

extern Vec3f sOldPosition;
extern Vec3f sOldFocus;
extern struct PlayerGeometry sMarioGeometry;

// Applies the PuppyCam values to the actual game's camera, giving the final product.
static void puppycam_apply(void) {
    f32 posX = gPuppyCam.pos[0];
    f32 posY = gPuppyCam.pos[1];
    f32 posZ = gPuppyCam.pos[2];
    vec3f_set(gLakituState.pos,       posX, posY, posZ);
    vec3f_set(gLakituState.goalPos,   posX, posY, posZ);
    vec3f_set(gLakituState.curPos,    posX, posY, posZ);
    vec3f_set(gCamera->pos,           posX, posY, posZ);
    vec3f_set(sOldPosition,           posX, posY, posZ);

    f32 focX = gPuppyCam.focus[0];
    f32 focY = gPuppyCam.focus[1];
    f32 focZ = gPuppyCam.focus[2];
    vec3f_set(gLakituState.focus,     focX, focY, focZ);
    vec3f_set(gLakituState.goalFocus, focX, focY, focZ);
    vec3f_set(gLakituState.curFocus,  focX, focY, focZ);
    vec3f_set(gCamera->focus,         focX, focY, focZ);
    vec3f_set(sOldFocus,              focX, focY, focZ);

    s16 yaw = gPuppyCam.yaw;
    gCamera->yaw         = yaw;
    gCamera->nextYaw     = yaw;

    gLakituState.yaw     = yaw;
    gLakituState.nextYaw = yaw;
    gLakituState.oldYaw  = yaw;

    gLakituState.mode    = gCamera->mode;
    gLakituState.defMode = gCamera->defMode;
    gLakituState.roll    = 0;

    if (gMarioState->floor != NULL) {
        sMarioGeometry.prevFloor = sMarioGeometry.currFloor = gMarioState->floor;
        sMarioGeometry.prevFloorHeight = sMarioGeometry.currFloorHeight = gMarioState->floorHeight;
        sMarioGeometry.prevFloorType = sMarioGeometry.currFloorType = gMarioState->floor->type;
    }

    if (gMarioState->ceil != NULL) {
        sMarioGeometry.prevCeil = sMarioGeometry.currCeil = gMarioState->ceil;
        sMarioGeometry.prevCeilHeight = sMarioGeometry.currCeilHeight = gMarioState->ceilHeight;
        sMarioGeometry.prevCeilType = sMarioGeometry.currCeilType = gMarioState->ceil->type;
    }
    
    sMarioGeometry.waterHeight = gMarioState->waterLevel;
}

extern Texture texture_hud_char_puppycam[];
extern void render_hud_tex_lut(s32 x, s32 y, u8 *texture);
extern void render_hud_small_tex_lut(s32 x, s32 y, u8 *texture);

// Puppycam HUD logic
void puppycam_hud(void) {
    s32 x, y;
    u8 *(*ogCameraLUT)[6];
    s16 ogCamStatus = update_camera_hud_status(gCamera);

    ogCameraLUT = segmented_to_virtual(&main_hud_camera_lut);
    x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(54);
    y = 205;

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);

    // Main HUD Icons
    render_hud_tex_lut(x, y, (*ogCameraLUT)[GLYPH_CAM_CAMERA]);

    if (ogCamStatus & CAM_STATUS_FIXED) {
        render_hud_tex_lut(x + 16, y, (*ogCameraLUT)[GLYPH_CAM_FIXED]);
    } else {
        render_hud_tex_lut(x + 16, y, texture_hud_char_puppycam);
    }

    // Arrow Icons
    if (gPuppyCam.options.inputType != PUPPYCAM_INPUT_TYPE_CLASSIC) {
        switch (gPuppyCam.zoomSet) {
            case 0:
                render_hud_small_tex_lut(x + 4, y - 8, (*ogCameraLUT)[GLYPH_CAM_ARROW_UP]);
                break;
            case 1:
                break;
            case 2:
                render_hud_small_tex_lut(x + 4, y + 16, (*ogCameraLUT)[GLYPH_CAM_ARROW_DOWN]);
                break;
        }
    } else {
        switch (gPuppyCam.mode3Flags & PUPPYCAM_MODE3_GROUP) {
            case PUPPYCAM_MODE3_ZOOMED_IN:
                render_hud_small_tex_lut(x + 4, y - 8, (*ogCameraLUT)[GLYPH_CAM_ARROW_UP]);
                break;
            case PUPPYCAM_MODE3_ZOOMED_MED:
                break;
            case PUPPYCAM_MODE3_ZOOMED_OUT:
                render_hud_small_tex_lut(x + 4, y + 16, (*ogCameraLUT)[GLYPH_CAM_ARROW_DOWN]);
                break;
        }
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}



// The basic loop sequence, which is called outside.
void puppycam_loop(void)
{
    if (gPuppyCam.cutscene == 0 && sDelayedWarpOp == 0) {
        // Sets this before going through any possible modifications.
        gPuppyCam.flags = gPuppyCam.intendedFlags;
        puppycam_input_core();
        puppycam_projection();
        puppycam_script();
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_COLLISION) {
            puppycam_collision();
        } else {
            gPuppyCam.opacity = 255;
        }
    } else if (gPuppyCam.cutscene != 0) {
        gPuppyCam.opacity = 255;
        puppycam_process_cutscene();
    }
    puppycam_apply();
}

#endif
