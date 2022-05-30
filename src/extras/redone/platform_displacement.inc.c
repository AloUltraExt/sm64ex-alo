/*
 * Redone description:
 * A rewritten version of platform displacement (hence the 2).
 * Adds intertia so Mario has correct momentum on moving platforms.
 * Made by Arthurtilly.
 */

/**
 * Determine if Mario is standing on a platform object, meaning that he is
 * within 4 units of the floor. Set his referenced platform object accordingly.
 */
void update_mario_platform(void) {
    struct Surface *floor = gMarioState->floor;

    if (gMarioObject == NULL || floor == NULL) {
        return;
    }
    
    struct Object *floorObj = floor->object;

    if (floor != NULL
     && floorObj != NULL
     && absf(gMarioObject->oPosY - gMarioState->floorHeight) < 4.0f) {
        gMarioObject->platform = floorObj;
    } else {
        gMarioObject->platform = NULL;
    }
}

static struct PlatformDisplacementInfo sMarioDisplacementInfo;
static Vec3f sMarioAmountDisplaced;

extern s32 gGlobalTimer;

/**
 * Apply one frame of platform displacement to Mario or an object using the given
 * platform.
 */
void apply_platform_displacement(struct PlatformDisplacementInfo *displaceInfo, Vec3f pos, s16 *yaw, struct Object *platform) {
    Vec3f platformPos;
    Vec3f posDifference;
    Vec3f yawVec;
    Vec3f scaledPos;
    // Determine how much Mario turned on his own since last frame
    s16 yawDifference = *yaw - displaceInfo->prevYaw;

    // Avoid a crash if the platform unloaded its collision while stood on
    if (platform->header.gfx.throwMatrix == NULL) return;

    vec3f_copy(platformPos, (*platform->header.gfx.throwMatrix)[3]);

    // Determine how far Mario moved on his own since last frame
    vec3f_copy(posDifference, pos);
    vec3f_sub(posDifference, displaceInfo->prevPos);

    if ((platform == displaceInfo->prevPlatform) && (gGlobalTimer == displaceInfo->prevTimer + 1)) {
        // Upscale position
        vec3f_prod(scaledPos, displaceInfo->prevTransformedPos, platform->header.gfx.scale);

        // Transform from relative positions to world positions
        linear_mtxf_mul_vec3f(*platform->header.gfx.throwMatrix, pos, scaledPos);

        // Add on how much Mario moved in the previous frame
        vec3f_add(pos, posDifference);

        // Calculate new yaw
        linear_mtxf_mul_vec3f(*platform->header.gfx.throwMatrix, yawVec, displaceInfo->prevTransformedYawVec);
        *yaw = atan2s(yawVec[2], yawVec[0]) + yawDifference;
    } else {
        // First frame of standing on the platform, don't calculate a new position
        vec3f_sub(pos, platformPos);
    }

    // Apply velocity-based displacement for certain objects (like the TTC Treadmills)
    if (platform->oFlags & OBJ_FLAG_VELOCITY_PLATFORM) {
        vec3f_add(pos, &platform->oVelX);
    }

    // Transform from world positions to relative positions for use next frame
    linear_mtxf_transpose_mul_vec3f(*platform->header.gfx.throwMatrix, scaledPos, pos);

    // Downscale position
    vec3f_quot(displaceInfo->prevTransformedPos, scaledPos, platform->header.gfx.scale);
    vec3f_add(pos, platformPos);

    // If the object is Mario, set inertia
    if (pos == gMarioState->pos) {
        vec3f_copy(sMarioAmountDisplaced, pos);
        vec3f_sub(sMarioAmountDisplaced, displaceInfo->prevPos);
        vec3f_sub(sMarioAmountDisplaced, posDifference);

        // Make sure inertia isn't set on the first frame otherwise the previous value isn't cleared
        if ((platform != displaceInfo->prevPlatform) || (gGlobalTimer != displaceInfo->prevTimer + 1)) {
            vec3_zero(sMarioAmountDisplaced);
        }
    }

    // Update info for next frame
    // Update position
    vec3f_copy(displaceInfo->prevPos, pos);

    // Set yaw info
    vec3f_set(yawVec, sins(*yaw), 0, coss(*yaw));
    linear_mtxf_transpose_mul_vec3f(*platform->header.gfx.throwMatrix, displaceInfo->prevTransformedYawVec, yawVec);
    displaceInfo->prevYaw = *yaw;

    // Update platform and timer
    displaceInfo->prevPlatform = platform;
    displaceInfo->prevTimer = gGlobalTimer;
}

// Doesn't change in the code, set this to FALSE if you don't want inertia
u8 gDoInertia = TRUE;

static u8 sShouldApplyInertia = FALSE;
static u8 sInertiaFirstFrame = FALSE;

/**
 * Apply inertia based on Mario's last platform.
 */
static void apply_mario_inertia(void) {
    // On the first frame of leaving the ground, boost Mario's y velocity
    if (sInertiaFirstFrame) {
        gMarioState->vel[1] += sMarioAmountDisplaced[1];
    }

    // Apply sideways inertia
    gMarioState->pos[0] += sMarioAmountDisplaced[0];
    gMarioState->pos[2] += sMarioAmountDisplaced[2];

    // Drag
    sMarioAmountDisplaced[0] *= 0.97f;
    sMarioAmountDisplaced[2] *= 0.97f;

    // Stop applying inertia once Mario has landed, or when ground pounding
    if (!(gMarioState->action & ACT_FLAG_AIR) || (gMarioState->action == ACT_GROUND_POUND)) {
        sShouldApplyInertia = FALSE;
    }
}

/**
 * Apply platform displacement or inertia if required.
 */
void apply_mario_platform_displacement(void) {
    if (!(gTimeStopState & TIME_STOP_ACTIVE) && gMarioObject != NULL && !(gMarioState->action & ACT_FLAG_INTANGIBLE)) {
        struct Object *platform = gMarioObject->platform;

        if (platform != NULL) {
            apply_platform_displacement(&sMarioDisplacementInfo, gMarioState->pos, &gMarioState->faceAngle[1], platform);
            sShouldApplyInertia = TRUE;
            sInertiaFirstFrame = TRUE;
        } else if (sShouldApplyInertia && gDoInertia) {
            apply_mario_inertia();
            sInertiaFirstFrame = FALSE;
        }
    }
}
