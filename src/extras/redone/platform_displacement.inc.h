#pragma once

#include <PR/ultratypes.h>

#include "types.h"

struct PlatformDisplacementInfo {
	Vec3f prevPos;
	Vec3f prevTransformedPos;
	Vec3f prevTransformedYawVec;
	s16 prevYaw;
	struct Object *prevPlatform;
	s32 prevTimer;
};

void update_mario_platform(void);
void apply_platform_displacement(struct PlatformDisplacementInfo *displaceInfo, Vec3f pos, s16 *yaw, struct Object *platform);
void apply_mario_platform_displacement(void);
