#ifdef BETTERCAMERA

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
#include "gfx_dimensions.h"

#include "pc/configfile.h"

#ifdef MOUSE_ACTIONS
#include "pc/controller/controller_mouse.h"
#endif

#define OFFSET 30.0f
#define STEPS 1
#define DECELERATION 0.75f
#define DEADZONE 20
#define SCRIPT_MEMORY_POOL 0x1000
#define MAX_PUPPYCAM_VOLUMES 50

struct gPuppyStruct gPuppyCam;
struct sPuppyVolume *sPuppyVolumeStack[];
s16 sFloorHeight = 0;
u16 gPuppyVolumeCount = 0;
struct MemoryPool *gPuppyMemoryPool;
s32 gPuppyError = 0;
//Some macros for the sake of basic human sanity.
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define ABS(x) ((x) > 0.f ? (x) : -(x))

s16 LENSIN(s16 length, s16 direction)
{
    return (length * sins(direction));
}
s16 LENCOS(s16 length, s16 direction)
{
    return (length * coss(direction));
}

static void puppycam_analogue_stick(void)
{
    #ifdef TARGET_N64
    if (!gPuppyCam.options.analogue)
        return;

    //I make the X axis negative, so that the movement reflects the Cbuttons.
    gPuppyCam.stick2[0] = -gPlayer2Controller->rawStickX;
    gPuppyCam.stick2[1] = gPlayer2Controller->rawStickY;

    if (ABS(gPuppyCam.stick2[0]) < DEADZONE)
    {
        gPuppyCam.stick2[0] = 0;
        gPuppyCam.stickN[0] = 0;
    }
    if (ABS(gPuppyCam.stick2[1]) < DEADZONE)
    {
        gPuppyCam.stick2[1] = 0;
        gPuppyCam.stickN[1] = 0;
    }
    #endif
}

#ifdef TARGET_N64 // TODO: save to eeprom
// BetterCamera settings
bool         configEnableCamera  = true;
bool         configCameraInvertX = true;
bool         configCameraInvertY = true;
unsigned int configCameraXSens   = 100;
unsigned int configCameraYSens   = 100;
unsigned int configCameraAggr    = 100;
bool         configCameraAnalog  = false;
#endif

void puppycam_default_config(void) {
    gPuppyCam.enabled = configEnableCamera;
#ifdef MOUSE_ACTIONS
    gPuppyCam.mouse = configCameraMouse;
#endif
    gPuppyCam.options.invertX = configCameraInvertX;
    gPuppyCam.options.invertY = configCameraInvertY;
    gPuppyCam.options.sensitivityX = configCameraXSens;
    gPuppyCam.options.sensitivityY = configCameraYSens;
    gPuppyCam.options.turnAggression = configCameraAggr;
    gPuppyCam.options.analogue = configCameraAnalog;
}

//Initial setup. Ran at the beginning of the game and never again.
void puppycam_boot(void)
{
    gPuppyCam.zoomPoints[0] = 500;
    gPuppyCam.zoomPoints[1] = 1000;
    gPuppyCam.zoomPoints[2] = 1500;
    gPuppyCam.povHeight = 125;
    gPuppyCam.stick2[0] = 0;
    gPuppyCam.stick2[1] = 0;
    gPuppyCam.stickN[0] = 0;
    gPuppyCam.stickN[1] = 0;
    gPuppyMemoryPool = mem_pool_init(MAX_PUPPYCAM_VOLUMES * sizeof(struct sPuppyVolume), MEMORY_POOL_LEFT);
    gPuppyVolumeCount = 0;

    //puppycam_get_save();
}

extern struct SaveBuffer gSaveBuffer;

///CORE

//Set up values. Runs on level load.
void puppycam_init(void)
{

    if (gMarioState->marioObj)
        gPuppyCam.targetObj = gMarioState->marioObj;
    gPuppyCam.targetObj2 = NULL;

    gPuppyCam.intendedFlags = PUPPYCAM_BEHAVIOUR_DEFAULT;

    if (gCurrLevelNum == LEVEL_PSS || (gCurrLevelNum == LEVEL_TTM && gCurrAreaIndex == 2) || (gCurrLevelNum == LEVEL_CCM && gCurrAreaIndex == 2))
        gPuppyCam.intendedFlags |= PUPPYCAM_BEHAVIOUR_SLIDE_CORRECTION;
    gPuppyCam.flags = gPuppyCam.intendedFlags;
    gPuppyCam.zoom = gPuppyCam.zoomPoints[1];
    gPuppyCam.zoomSet = 1;
    gPuppyCam.zoomTarget = gPuppyCam.zoom;
    gPuppyCam.yaw = gMarioState->faceAngle[1]+0x8000;
    gPuppyCam.yawTarget = gPuppyCam.yaw;
    gPuppyCam.pitch = 0x3000;
    gPuppyCam.pitchTarget = gPuppyCam.pitch;
    gPuppyCam.yawAcceleration = 0;
    gPuppyCam.pitchAcceleration = 0;
    gPuppyCam.shakeFrames = 0;
    gPuppyCam.shake[0] = 0;
    gPuppyCam.shake[1] = 0;
    gPuppyCam.shake[2] = 0;
    gPuppyCam.pos[0] = 0;
    gPuppyCam.pos[1] = 0;
    gPuppyCam.pos[2] = 0;
    gPuppyCam.focus[0] = 0;
    gPuppyCam.focus[1] = 0;
    gPuppyCam.focus[2] = 0;
    gPuppyCam.pan[0] = 0;
    gPuppyCam.pan[1] = 0;//gMarioState->pos[1];
    gPuppyCam.pan[2] = 0;
    gPuppyCam.posHeight[0] = 0;
    gPuppyCam.posHeight[1] = 0;
    gPuppyCam.targetFloorHeight = gPuppyCam.pan[1];
    gPuppyCam.lastTargetFloorHeight = gMarioState->pos[1];
    gPuppyCam.opacity = 255;
    gPuppyCam.swimPitch = 0;

}

//Handles C Button inputs for modes that have held inputs, rather than presses.
static void puppycam_input_hold(void)
{
    f32 ivX = ((gPuppyCam.options.invertX*2)-1)*(gPuppyCam.options.sensitivityX/100.f);
    s8 stickMag = 0;

    gPuppyCam.framesSinceC[0]++;
    gPuppyCam.framesSinceC[1]++;

    //Analogue Camera stuff. If it fails to find an input, then it just sets stickmag to 100, which after calculations means the value goes unchanged.
    if (gPuppyCam.options.analogue)
        stickMag = gPuppyCam.stick2[0]*1.25f;
    else
        stickMag = 100;

    //In theory this shouldn't be necessary, but it's nice to cover all bases.
    if (!(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_YAW_ROTATION))
        return;

    if (!gPuppyCam.options.analogue && gPlayer1Controller->buttonPressed & L_CBUTTONS && gPuppyCam.framesSinceC[0] <= 5)
    {
        gPuppyCam.yawTarget -= 0x4000*ivX;
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
    }
    else
    if (!gPuppyCam.options.analogue && gPlayer1Controller->buttonPressed & R_CBUTTONS && gPuppyCam.framesSinceC[1] <= 5)
    {
        gPuppyCam.yawTarget += 0x4000*ivX;
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gGlobalSoundSource);
    }

    if ((gPlayer1Controller->buttonDown & L_CBUTTONS && !gPuppyCam.options.analogue) || gPuppyCam.stick2[0] != 0)
    {
        gPuppyCam.yawAcceleration -= 40*(gPuppyCam.options.sensitivityX/100.f);
        gPuppyCam.framesSinceC[0] = 0;
    }
    else
    if ((gPlayer1Controller->buttonDown & R_CBUTTONS && !gPuppyCam.options.analogue) || gPuppyCam.stick2[0] != 0)
    {
        gPuppyCam.yawAcceleration += 40*(gPuppyCam.options.sensitivityX/100.f);
        gPuppyCam.framesSinceC[1] = 0;
    }
    else
        gPuppyCam.yawAcceleration = approach_f32_asymptotic(gPuppyCam.yawAcceleration, 0, DECELERATION);

    gPuppyCam.yawAcceleration = CLAMP(gPuppyCam.yawAcceleration, -100, 100);

    gPuppyCam.yawTarget += (12*gPuppyCam.yawAcceleration*ivX)*(stickMag*0.01f);
}

//Handles C Button inputs for modes that have pressed inputs, rather than held.
static void puppycam_input_press(void)
{
    f32 ivX = ((gPuppyCam.options.invertX*2)-1)*(gPuppyCam.options.sensitivityX/100.f);

    //Just in case it happens to be nonzero.
    gPuppyCam.yawAcceleration = 0;

    //In theory this shouldn't be necessary, but it's nice to cover all bases.
    if (!(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_YAW_ROTATION))
        return;

    if ((gPlayer1Controller->buttonPressed & L_CBUTTONS && !gPuppyCam.options.analogue) || (gPuppyCam.stickN[0] == 0 && gPuppyCam.stick2[0] < -DEADZONE))
    {
        gPuppyCam.stickN[0] = 1;
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR)
            gPuppyCam.yawTarget -= 0x2000*ivX;
        else
            gPuppyCam.yawTarget -= 0x4000*ivX;
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN,gGlobalSoundSource);
    }

    if ((gPlayer1Controller->buttonPressed & R_CBUTTONS && !gPuppyCam.options.analogue) || (gPuppyCam.stickN[0] == 0 && gPuppyCam.stick2[0] > DEADZONE))
    {
        gPuppyCam.stickN[0] = 1;
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR)
            gPuppyCam.yawTarget += 0x2000*ivX;
        else
            gPuppyCam.yawTarget += 0x4000*ivX;
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN,gGlobalSoundSource);
    }
}

#ifdef MOUSE_ACTIONS
//Mouse control support for PC Platforms
static void puppycam_input_mouse(void) {
    f32 ivX = ((gPuppyCam.options.invertX*2)-1)*(gPuppyCam.options.sensitivityX/100.f);
    f32 ivY = ((gPuppyCam.options.invertY*2)-1)*(gPuppyCam.options.sensitivityY/100.f);

    if (configMouse && gPuppyCam.mouse) {
        gPuppyCam.yawTarget += ivX * gMouseXPos * 16;
        gPuppyCam.pitchTarget += ivY * gMouseYPos * 16;
    }
}
#endif

static void puppycam_view_panning(void)
{
    f32 panFloor, panMulti;
    s16 height = gPuppyCam.targetObj->oPosY;
    u8 panEx = (gPuppyCam.zoomTarget >= 1000) * 250; //Removes the basic panning when idling if the zoom level is at the closest.

    panMulti = CLAMP(gPuppyCam.zoom/(f32)gPuppyCam.zoomPoints[2], 0.f, 1.f);

    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_PANSHIFT && gMarioState->action != ACT_HOLDING_BOWSER && gMarioState->action != ACT_SLEEPING && gMarioState->action != ACT_START_SLEEPING)
    {
        gPuppyCam.pan[0] = approach_f32_asymptotic(gPuppyCam.pan[0], LENSIN(panEx+(500*(gMarioState->forwardVel/32.f)), gMarioState->faceAngle[1])*panMulti, 0.02f);
        gPuppyCam.pan[2] = approach_f32_asymptotic(gPuppyCam.pan[2], LENCOS(panEx+(500*(gMarioState->forwardVel/32.f)), gMarioState->faceAngle[1])*panMulti, 0.02f);
        if (gMarioState->vel[1] == 0.0f)
        {
            panFloor = CLAMP(find_floor_height((s16)(gPuppyCam.targetObj->oPosX+gPuppyCam.pan[0]),(s16)(gPuppyCam.targetObj->oPosY + 200),
            (s16)(gPuppyCam.targetObj->oPosZ+gPuppyCam.pan[2])),gPuppyCam.targetObj->oPosY-50,gPuppyCam.targetObj->oPosY+50);
            gPuppyCam.pan[1] = approach_f32_asymptotic(gPuppyCam.pan[1], panFloor-height, 0.25f);
        }
        else
            gPuppyCam.pan[1] = approach_f32_asymptotic(gPuppyCam.pan[1], 0, 0.5f);
    }
    else
    {
        gPuppyCam.pan[0] = 0;
        gPuppyCam.pan[1] = 0;
        gPuppyCam.pan[2] = 0;
    }
}

//Sets the
static void puppycam_view_height_offset(void)
{
    s16 floorTemp;
    s16 tempDist = sqrtf((gPuppyCam.pos[0] - gPuppyCam.focus[0]) * (gPuppyCam.pos[0] - gPuppyCam.focus[0]) + (gPuppyCam.pos[1] - gPuppyCam.focus[1]) *
                         (gPuppyCam.pos[1] - gPuppyCam.focus[1]) + (gPuppyCam.pos[2] - gPuppyCam.focus[2]) * (gPuppyCam.pos[2] - gPuppyCam.focus[2]));

    floorTemp = find_floor_height(gPuppyCam.targetObj->oPosX, gPuppyCam.targetObj->oPosY+200, gPuppyCam.targetObj->oPosZ);
    if (floorTemp > gPuppyCam.targetObj->oPosY - 200 && !(gMarioState->action & ACT_FLAG_SWIMMING))
    {
        gPuppyCam.posHeight[0] = approach_f32_asymptotic(gPuppyCam.posHeight[0],floorTemp-gPuppyCam.targetFloorHeight,0.05f);
        //if (gPuppyCam.posHeight[0]-gPuppyCam.shake[1] - gPuppyCam.floorY[1] < floorTemp)
        //    gPuppyCam.posHeight[0] = floorTemp-gPuppyCam.shake[1]+gPuppyCam.povHeight - gPuppyCam.floorY[1];
    }
    else
    {
            gPuppyCam.posHeight[0] = approach_f32_asymptotic(gPuppyCam.posHeight[0],0,0.1f);
    }


    floorTemp = find_floor_height(gPuppyCam.targetObj->oPosX + LENSIN(tempDist,gPuppyCam.yaw), gPuppyCam.targetObj->oPosY+200, gPuppyCam.targetObj->oPosZ + LENCOS(tempDist,gPuppyCam.yaw));
    if (floorTemp > gPuppyCam.targetObj->oPosY - 200 && !(gMarioState->action & ACT_FLAG_SWIMMING))
    {
        gPuppyCam.posHeight[1] = approach_f32_asymptotic(gPuppyCam.posHeight[1],floorTemp-gPuppyCam.targetFloorHeight,0.05f);
        //if (gPuppyCam.posHeight[1]-gPuppyCam.shake[1] - gPuppyCam.floorY[0] < floorTemp)
        //    gPuppyCam.posHeight[1] = floorTemp-gPuppyCam.shake[1]+gPuppyCam.povHeight - gPuppyCam.floorY[0];
    }
    else
    {
            gPuppyCam.posHeight[1] = approach_f32_asymptotic(gPuppyCam.posHeight[1],0,0.1f);
    }
}

//Raycasting
s32 ray_surface_intersect(Vec3f orig, Vec3f dir, f32 dir_length, struct Surface *surface, Vec3f hit_pos, f32 *length)
{
    Vec3f v0, v1, v2, e1, e2, h, s, q;
    f32 a, f, u, v;
    Vec3f add_dir;
    Vec3f norm;

    //Ignore certain surface types.
    if (surface->type == SURFACE_INTANGIBLE || surface->flags & SURFACE_FLAG_NO_CAM_COLLISION)
        return FALSE;

    // Get surface normal and some other stuff
    norm[0] = surface->normal.x;
    norm[1] = surface->normal.y;
    norm[2] = surface->normal.z;
    vec3f_mul(norm,OFFSET);

    vec3s_to_vec3f(v0, surface->vertex1);
    vec3s_to_vec3f(v1, surface->vertex2);
    vec3s_to_vec3f(v2, surface->vertex3);

    vec3f_add(v0, norm);
    vec3f_add(v1, norm);
    vec3f_add(v2, norm);

    vec3f_dif(e1, v1, v0);
    vec3f_dif(e2, v2, v0);

    vec3f_cross(h, dir, e2);

    // Check if we're perpendicular from the surface
    a = vec3f_dot(e1, h);
    if (a > -0.00001f && a < 0.00001f)
        return FALSE;

    // Check if we're making contact with the surface
    f = 1.0f / a;

    vec3f_dif(s, orig, v0);
    u = f * vec3f_dot(s, h);
    if (u < 0.0f || u > 1.0f)
        return FALSE;

    vec3f_cross(q, s, e1);
    v = f * vec3f_dot(dir, q);
    if (v < 0.0f || u + v > 1.0f)
        return FALSE;

    // Get the length between our origin and the surface contact point
    *length = f * vec3f_dot(e2, q);
    if (*length <= 0.00001 || *length > dir_length)
        return FALSE;

    // Successful contact
    vec3f_copy(add_dir, dir);
    vec3f_mul(add_dir, *length);
    vec3f_sum(hit_pos, orig, add_dir);
    return TRUE;
}

void find_surface_on_ray_list(struct SurfaceNode *list, Vec3f orig, Vec3f dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length)
{
    s32 hit;
    f32 length;
    Vec3f chk_hit_pos;
    f32 top, bottom;

    // Get upper and lower bounds of ray
    if (dir[1] >= 0.0f)
    {
        top = orig[1] + dir[1] * dir_length;
        bottom = orig[1];
    }
    else
    {
        top = orig[1];
        bottom = orig[1] + dir[1] * dir_length;
    }

    // Iterate through every surface of the list
    for (; list != NULL; list = list->next)
    {
        // Reject surface if out of vertical bounds
        if (list->surface->lowerY > top || list->surface->upperY < bottom)
            continue;

        // Check intersection between the ray and this surface
        if ((hit = ray_surface_intersect(orig, dir, dir_length, list->surface, chk_hit_pos, &length)) != 0)
        {
            if (length <= *max_length)
            {
                *hit_surface = list->surface;
                vec3f_copy(hit_pos, chk_hit_pos);
                *max_length = length;
            }
        }
    }
}


void find_surface_on_ray_cell(s16 cellX, s16 cellZ, Vec3f orig, Vec3f normalized_dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length)
{
	// Skip if OOB
	if (cellX >= 0 && cellX <= NUM_CELLS_INDEX && cellZ >= 0 && cellZ <= NUM_CELLS_INDEX)
	{
		// Iterate through each surface in this partition
		if (normalized_dir[1] > -0.99999f)
		{
			find_surface_on_ray_list(gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
			find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
		}
		if (normalized_dir[1] < 0.99999f)
		{
			find_surface_on_ray_list(gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
			find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
		}
		find_surface_on_ray_list(gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
		find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
	}
}

void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos)
{
    f32 max_length;
    s16 cellZ, cellX, cellPrevX, cellPrevZ;
    f32 fCellZ, fCellX;
    f32 dir_length;
    Vec3f normalized_dir;
    f32 step, dx, dz;
    u32 i;

    // Set that no surface has been hit
    *hit_surface = NULL;
    vec3f_sum(hit_pos, orig, dir);

    // Get normalized direction
    dir_length = vec3f_length(dir);
    max_length = dir_length;
    vec3f_copy(normalized_dir, dir);
    vec3f_normalize(normalized_dir);

    // Get our cell coordinate
    fCellX = (orig[0] + LEVEL_BOUNDARY_MAX) / CELL_SIZE;
    fCellZ = (orig[2] + LEVEL_BOUNDARY_MAX) / CELL_SIZE;
    cellX = (s16)fCellX;
    cellZ = (s16)fCellZ;

    // Don't do DDA if straight down
    if (normalized_dir[1] >= 0.99999f || normalized_dir[1] <= -0.99999f)
    {
		find_surface_on_ray_cell(cellX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length);
		return;
	}

    // Get cells we cross using DDA
    if (ABS(dir[0]) >= ABS(dir[2]))
        step = STEPS*ABS(dir[0]) / CELL_SIZE;
    else
        step = STEPS*ABS(dir[2]) / CELL_SIZE;

    dx = dir[0] / step / CELL_SIZE;
    dz = dir[2] / step / CELL_SIZE;

    for (i = 0; i < step && *hit_surface == NULL; i++)
    {
		find_surface_on_ray_cell(cellX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length);

        // Move cell coordinate
        fCellX += dx;
        fCellZ += dz;
        cellPrevX = cellX;
        cellPrevZ = cellZ;
        cellX = (s16)fCellX;
        cellZ = (s16)fCellZ;

        if ((cellPrevX != cellX) && (cellPrevZ != cellZ))
        {
            find_surface_on_ray_cell(cellX, cellPrevZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length);
            find_surface_on_ray_cell(cellPrevX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length);
        }
    }
}

//Checks the bounding box of a puppycam volume. If it's inside, then set the pointer to the current index.
static u8 puppycam_check_volume_bounds(struct sPuppyVolume *volume, u16 index)
{
    Vec3f rel;

    if (sPuppyVolumeStack[index]->room != gMarioCurrentRoom && sPuppyVolumeStack[index]->room != -1)
        return FALSE;

    //debug_box_pos_rot(sPuppyVolumeStack[index]->pos, sPuppyVolumeStack[index]->radius, sPuppyVolumeStack[index]->rot);

    //Fetch the relative position. to the triggeree.
    rel[0] = sPuppyVolumeStack[index]->pos[0] - gPuppyCam.targetObj->oPosX;
    rel[1] = sPuppyVolumeStack[index]->pos[1] - gPuppyCam.targetObj->oPosY;
    rel[2] = sPuppyVolumeStack[index]->pos[2] - gPuppyCam.targetObj->oPosZ;
    //Use the dark, forbidden arts of trig to rotate the volume.
    rel[0] = rel[2] * sins(sPuppyVolumeStack[index]->rot) + rel[0] * coss(sPuppyVolumeStack[index]->rot);
    rel[2] = rel[2] * coss(sPuppyVolumeStack[index]->rot) - rel[0] * sins(sPuppyVolumeStack[index]->rot);

    //Now compare values.
    if (-sPuppyVolumeStack[index]->radius[0] < rel[0] && rel[0] < sPuppyVolumeStack[index]->radius[0] &&
        -sPuppyVolumeStack[index]->radius[1] < rel[1] && rel[1] < sPuppyVolumeStack[index]->radius[1] &&
        -sPuppyVolumeStack[index]->radius[2] < rel[2] && rel[2] < sPuppyVolumeStack[index]->radius[2])
        {
            *volume = *sPuppyVolumeStack[index];
            return TRUE;
        }

    return FALSE;
}

//Adds support for wing mario tower
static void puppycam_wingmario_tower(void) {
    if (gMarioState->floor && gMarioState->floor->type == SURFACE_LOOK_UP_WARP
        && save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= 10) {
        if (gPuppyCam.pitch > -8000 && gMarioState->forwardVel == 0) {
            level_trigger_warp(gMarioState, WARP_OP_UNKNOWN_01);
        }
    }
}

//void puppycam_shake(s16 x, s16 y, s16 z) {
//}

///This is the highest level of the basic steps that go into the code. Anything above is called from these following functions.

//The centrepiece behind the input side of PuppyCam. The C buttons branch off.
static void puppycam_input_core(void)
{
    f32 ivY = ((gPuppyCam.options.invertY*2)-1)*(gPuppyCam.options.sensitivityY/100.f);
    s8 stickMag = 0;

    puppycam_analogue_stick();

    if (gPuppyCam.options.analogue)
        stickMag = gPuppyCam.stick2[1]*1.25f;
    else
        stickMag = 100;

    //Decide which input for left and right C buttons to use based on behaviour type.
    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_NORMAL)
        puppycam_input_hold();
    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR || gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_4DIR)
        puppycam_input_press();
    //Handles R button zooming.
    if (gPlayer1Controller->buttonPressed & R_TRIG && gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_ZOOM_CHANGE)
    {
        gPuppyCam.zoomSet++;

        if (gPuppyCam.zoomSet >= 3)
            gPuppyCam.zoomSet = 0;

        gPuppyCam.zoomTarget = gPuppyCam.zoomPoints[gPuppyCam.zoomSet];
        play_sound(SOUND_MENU_CLICK_CHANGE_VIEW,gGlobalSoundSource);
    }

    //Handles L button centering.
    if (gPlayer1Controller->buttonPressed & L_TRIG && gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_YAW_ROTATION &&
    !(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR) && !(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_4DIR) && !(gPlayer1Controller->buttonDown & U_JPAD))
    {
        gPuppyCam.yawTarget = gMarioState->faceAngle[1]+0x8000;
        play_sound(SOUND_MENU_CLICK_CHANGE_VIEW,gGlobalSoundSource);
    }

    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_PITCH_ROTATION)
    {
        //Handles vertical inputs.
        if (gPlayer1Controller->buttonDown & U_CBUTTONS || gPuppyCam.stick2[1] != 0)
            gPuppyCam.pitchAcceleration -= 15*(gPuppyCam.options.sensitivityY/100.f);
        else
        if (gPlayer1Controller->buttonDown & D_CBUTTONS || gPuppyCam.stick2[1] != 0)
            gPuppyCam.pitchAcceleration += 15*(gPuppyCam.options.sensitivityY/100.f);
        else
            gPuppyCam.pitchAcceleration = approach_f32_asymptotic(gPuppyCam.pitchAcceleration, 0, DECELERATION);

        gPuppyCam.pitchAcceleration = CLAMP(gPuppyCam.pitchAcceleration, -100, 100);
        gPuppyCam.pitchTarget += (8*gPuppyCam.pitchAcceleration*ivY)*(stickMag*0.01f);
    }

    //If the camera's in these modes, snap the yaw to prevent desync.
    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR)
    {
        if (gPuppyCam.yawTarget % 0x2000)
        gPuppyCam.yawTarget += 0x2000 - gPuppyCam.yawTarget % 0x2000;
    }
    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_4DIR)
        gPuppyCam.yawTarget %= 0x4000;
        
#ifdef MOUSE_ACTIONS
    puppycam_input_mouse();
#endif
}

//Calculates the base position the camera should be, before any modification.
static void puppycam_projection(void)
{
    Vec3s targetPos, targetPos2, targetPos3;
    u8 panD = (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_PANSHIFT)/8192;

    if (gPuppyCam.targetObj == gMarioState->marioObj)
    {
        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_SLIDE_CORRECTION && gMarioState->action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE)
        {
            gPuppyCam.yawTarget = gMarioState->faceAngle[1]+0x8000;
            gPuppyCam.pan[0] = 0;
            gPuppyCam.pan[1] = 0;
            gPuppyCam.pan[2] = 0;
        }
        if (!(gMarioState->action & ACT_FLAG_SWIMMING))
        {
            gPuppyCam.floorY[0] = CLAMP(gPuppyCam.targetObj->oPosY - gPuppyCam.lastTargetFloorHeight, 0, 300);
            gPuppyCam.floorY[1] = CLAMP(gPuppyCam.targetObj->oPosY - gPuppyCam.lastTargetFloorHeight, 0, 350);
            gPuppyCam.swimPitch = approach_f32_asymptotic(gPuppyCam.swimPitch,0,0.2f);
        }
        else
        {
            gPuppyCam.floorY[0] = 0;
            gPuppyCam.floorY[1] = 0;
            gPuppyCam.swimPitch = approach_f32_asymptotic(gPuppyCam.swimPitch,gMarioState->faceAngle[0]/10,0.05f);
            gPuppyCam.yawTarget  = gMarioState->faceAngle[1]+0x8000 - approach_s32((s16)(gMarioState->faceAngle[1]+0x8000 - gPuppyCam.yawTarget), 0,
            1000*(gMarioState->forwardVel/32), 1000*(gMarioState->forwardVel/32));
        }

        gPuppyCam.targetFloorHeight = find_floor_height(gPuppyCam.targetObj->oPosX, gPuppyCam.targetObj->oPosY, gPuppyCam.targetObj->oPosZ);

    if (gMarioState->vel[1] <= 0.0f)
        gPuppyCam.lastTargetFloorHeight = approach_f32_asymptotic(gPuppyCam.lastTargetFloorHeight,gPuppyCam.targetFloorHeight, 0.1f);

    if (gPuppyCam.options.turnAggression > 0 && gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_TURN_HELPER && !(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_8DIR) &&
        gMarioState->vel[1] == 0.0f && !(gMarioState->action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE) && !(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_INPUT_4DIR))
    {
        if (ABS(gPlayer1Controller->rawStickX) > 20)
            gPuppyCam.yawTarget  = gMarioState->faceAngle[1]+0x8000 - approach_s32((s16)(gMarioState->faceAngle[1]+0x8000 - gPuppyCam.yawTarget), 0,
            (gPuppyCam.options.turnAggression*10)*(gMarioState->forwardVel/32) * ABS(gPlayer1Controller->rawStickX/80.0f),
            (gPuppyCam.options.turnAggression*10)*(gMarioState->forwardVel/32) * ABS(gPlayer1Controller->rawStickX/80.0f));
    }

    if (gMarioState->action == ACT_SLEEPING || gMarioState->action == ACT_START_SLEEPING)
        gPuppyCam.zoom = approach_f32_asymptotic(gPuppyCam.zoom,gPuppyCam.zoomPoints[0],0.01f);
    else
        gPuppyCam.zoom = approach_f32_asymptotic(gPuppyCam.zoom,gPuppyCam.zoomTarget,0.1f);

    if (gPuppyCam.targetObj == gMarioState->marioObj)
    {
        if (gMarioState->action == ACT_SLEEPING || gMarioState->action == ACT_START_SLEEPING)
            gPuppyCam.zoom = approach_f32_asymptotic(gPuppyCam.zoom,gPuppyCam.zoomPoints[0],0.01f);
        else
            gPuppyCam.zoom = approach_f32_asymptotic(gPuppyCam.zoom,gPuppyCam.zoomTarget,0.1f);
    }
    else
    {
        gPuppyCam.floorY[0] = 0;
        gPuppyCam.floorY[1] = 0;
        gPuppyCam.swimPitch = 0;
    }
    }

    gPuppyCam.yaw = gPuppyCam.yawTarget - approach_f32_asymptotic((s16)(gPuppyCam.yawTarget - gPuppyCam.yaw), 0, 0.2f);
    gPuppyCam.pitch = gPuppyCam.pitchTarget - approach_f32_asymptotic((s16)(gPuppyCam.pitchTarget - gPuppyCam.pitch), 0, 0.1f);
    gPuppyCam.pitch = CLAMP(gPuppyCam.pitch,0x1000,0x7000);
    gPuppyCam.pitchTarget = CLAMP(gPuppyCam.pitchTarget,0x1000,0x7000);

    if (gPuppyCam.targetObj)
    {
        vec3s_set(targetPos, gPuppyCam.targetObj->oPosX, gPuppyCam.targetObj->oPosY, gPuppyCam.targetObj->oPosZ);
        vec3s_copy(targetPos3, targetPos);
        if (gPuppyCam.targetObj2)
        {
            vec3s_set(targetPos2, gPuppyCam.targetObj2->oPosX, gPuppyCam.targetObj2->oPosY, gPuppyCam.targetObj2->oPosZ);
            targetPos3[0] = (s16)approach_f32_asymptotic(targetPos[0], targetPos2[0], 0.5f);
            targetPos3[1] = (s16)approach_f32_asymptotic(targetPos[1], targetPos2[1], 0.5f);
            targetPos3[2] = (s16)approach_f32_asymptotic(targetPos[2], targetPos2[2], 0.5f);

        }

        puppycam_view_panning();

        if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_HEIGHT_HELPER)
        {
             puppycam_view_height_offset();
        }
        else
        {
            gPuppyCam.posHeight[0] = 0;
            gPuppyCam.posHeight[1] = 0;
        }

        gPuppyCam.focus[0] = targetPos3[0] + gPuppyCam.shake[0] + (gPuppyCam.pan[0]*gPuppyCam.collisionDistance/gPuppyCam.zoomPoints[2])*panD;
        gPuppyCam.focus[1] = targetPos3[1] + gPuppyCam.shake[1] + (gPuppyCam.pan[1]*gPuppyCam.collisionDistance/gPuppyCam.zoomPoints[2]) + gPuppyCam.povHeight - gPuppyCam.floorY[0] + gPuppyCam.posHeight[0] + (gPuppyCam.swimPitch/10);
        gPuppyCam.focus[2] = targetPos3[2] + gPuppyCam.shake[2] + (gPuppyCam.pan[2]*gPuppyCam.collisionDistance/gPuppyCam.zoomPoints[2])*panD;

        gPuppyCam.pos[0] = gPuppyCam.targetObj->oPosX + LENSIN(LENSIN(gPuppyCam.zoom,gPuppyCam.pitch),gPuppyCam.yaw) + gPuppyCam.shake[0];
        gPuppyCam.pos[1] = gPuppyCam.targetObj->oPosY + LENCOS(gPuppyCam.zoom,gPuppyCam.pitch+(gPuppyCam.swimPitch*5)) + gPuppyCam.shake[1] - gPuppyCam.floorY[1] + gPuppyCam.posHeight[1];
        gPuppyCam.pos[2] = gPuppyCam.targetObj->oPosZ + LENCOS(LENSIN(gPuppyCam.zoom,gPuppyCam.pitch),gPuppyCam.yaw) + gPuppyCam.shake[2];
    }
    
    puppycam_wingmario_tower();
}

//Calls any scripts to affect the camera, if applicable.
static void puppycam_script(void)
{
    u16 i = 0;
    struct sPuppyVolume volume;
    void (*func)();

    //Sets this before going through any possible modifications.
    gPuppyCam.flags = gPuppyCam.intendedFlags;

    if (gPuppyVolumeCount == 0 || !gPuppyCam.targetObj)
        return;

    for (i = 0; i < gPuppyVolumeCount; i++)
    {
        if (puppycam_check_volume_bounds(&volume, i))
        {
            //First applies pos and focus, for the most basic of volumes.
            if (volume.angles != NULL)
            {
                if (volume.angles->pos[0] != PUPPY_NULL)
                    gPuppyCam.pos[0] = volume.angles->pos[0];
                if (volume.angles->pos[1] != PUPPY_NULL)
                    gPuppyCam.pos[1] = volume.angles->pos[1];
                if (volume.angles->pos[2] != PUPPY_NULL)
                    gPuppyCam.pos[2] = volume.angles->pos[2];

                if (volume.angles->focus[0] != PUPPY_NULL)
                    gPuppyCam.focus[0] = volume.angles->focus[0];
                if (volume.angles->focus[1] != PUPPY_NULL)
                    gPuppyCam.focus[1] = volume.angles->focus[1];
                if (volume.angles->focus[2] != PUPPY_NULL)
                    gPuppyCam.focus[2] = volume.angles->focus[2];

                if (volume.angles->yaw != PUPPY_NULL)
                {
                    gPuppyCam.yawTarget = volume.angles->yaw;
                    gPuppyCam.yaw = volume.angles->yaw;

                    gPuppyCam.flags &= ~PUPPYCAM_BEHAVIOUR_YAW_ROTATION;
                }

                if (volume.angles->pitch != PUPPY_NULL)
                {
                    gPuppyCam.pitchTarget = volume.angles->pitch;
                    gPuppyCam.pitch = volume.angles->pitch;

                    gPuppyCam.flags &= ~PUPPYCAM_BEHAVIOUR_PITCH_ROTATION;
                }

                if (volume.angles->zoom != PUPPY_NULL)
                {
                    gPuppyCam.zoomTarget = volume.angles->zoom;
                    gPuppyCam.zoom = gPuppyCam.zoomTarget;

                    gPuppyCam.flags &= ~PUPPYCAM_BEHAVIOUR_ZOOM_CHANGE;
                }
            }

            //Adds and removes behaviour flags, as set.
            if (volume.flagsRemove != NULL)
                gPuppyCam.flags &= ~volume.flagsRemove;
            if (volume.flagsAdd != NULL)
                gPuppyCam.flags |= volume.flagsAdd;
            if (volume.flagPersistance == PUPPYCAM_BEHAVIOUR_PERMANENT)
            {
                //Adds and removes behaviour flags, as set.
                if (volume.flagsRemove != NULL)
                    gPuppyCam.intendedFlags &= ~volume.flagsRemove;
                if (volume.flagsAdd != NULL)
                    gPuppyCam.intendedFlags |= volume.flagsAdd;
            }

            //Last and probably least, check if there's a function attached, and call it, if so.
            if (volume.func != NULL)
            {
                func = volume.func;
                (func)();
            }
        }
    }
}

//Handles collision detection using ray casting.
static void puppycam_collision(void)
{
    struct Surface *surf;
    Vec3f camdir;
    Vec3f hitpos;
    Vec3f target;

    target[0] = gPuppyCam.targetObj->oPosX;
    target[1] = gPuppyCam.targetObj->oPosY+gPuppyCam.povHeight;
    target[2] = gPuppyCam.targetObj->oPosZ;

    camdir[0] = gPuppyCam.pos[0] - target[0];
    camdir[1] = gPuppyCam.pos[1] - target[1];
    camdir[2] = gPuppyCam.pos[2] - target[2];

    find_surface_on_ray(target, camdir, &surf, hitpos);
    gPuppyCam.collisionDistance = sqrtf((target[0] - hitpos[0]) * (target[0] - hitpos[0]) + (target[1] - hitpos[1]) * (target[1] - hitpos[1]) + (target[2] - hitpos[2]) * (target[2] - hitpos[2]));

    if (surf)
    {
        gPuppyCam.pos[0] = hitpos[0];
        gPuppyCam.pos[1] = hitpos[1];
        gPuppyCam.pos[2] = hitpos[2];
    }

    gPuppyCam.opacity = 255;

    if (gPuppyCam.collisionDistance <= 250 && (gPuppyCam.collisionDistance-150)*2.55 < 255)
    {
        if ((gPuppyCam.collisionDistance-150)*2.55 > 0)
            gPuppyCam.opacity = (gPuppyCam.collisionDistance-150)*2.55;
        else
            gPuppyCam.opacity = 0;
    }
    else
        gPuppyCam.opacity = 255;
}

//Applies the PuppyCam values to the actual game's camera, giving the final product.
static void puppycam_apply(void)
{
    gLakituState.pos[0] = gPuppyCam.pos[0];
    gLakituState.pos[1] = gPuppyCam.pos[1];
    gLakituState.pos[2] = gPuppyCam.pos[2];

    gLakituState.focus[0] = gPuppyCam.focus[0];
    gLakituState.focus[1] = gPuppyCam.focus[1];
    gLakituState.focus[2] = gPuppyCam.focus[2];

    gCamera->pos[0] = gPuppyCam.pos[0];
    gCamera->pos[1] = gPuppyCam.pos[1];
    gCamera->pos[2] = gPuppyCam.pos[2];

    gCamera->focus[0] = gPuppyCam.focus[0];
    gCamera->focus[1] = gPuppyCam.focus[1];
    gCamera->focus[2] = gPuppyCam.focus[2];

    gCamera->yaw = gPuppyCam.yaw;
}

extern Texture texture_hud_char_puppycam[];
extern void render_hud_tex_lut(s32 x, s32 y, u8 *texture);
extern void render_hud_small_tex_lut(s32 x, s32 y, u8 *texture);

//Puppycam HUD logic
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

    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}



//The basic loop sequence, which is called outside.
void puppycam_loop(void)
{
    puppycam_input_core();
    puppycam_projection();
    puppycam_script();
    if (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_COLLISION)
        puppycam_collision();
    else
        gPuppyCam.opacity = 255;

    puppycam_apply();
}

#endif
