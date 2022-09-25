#ifndef OBJ_BEHAVIORS_2_H
#define OBJ_BEHAVIORS_2_H

#include <PR/ultratypes.h>

#include "types.h"
#include "rm2c.h"

#define ATTACK_HANDLER_NOP 0
#define ATTACK_HANDLER_DIE_IF_HEALTH_NON_POSITIVE 1
#define ATTACK_HANDLER_KNOCKBACK 2
#define ATTACK_HANDLER_SQUISHED 3
#define ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL 4
#define ATTACK_HANDLER_SET_SPEED_TO_ZERO 5
#define ATTACK_HANDLER_SPECIAL_WIGGLER_JUMPED_ON 6
#define ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED 7
#define ATTACK_HANDLER_SQUISHED_WITH_BLUE_COIN 8

#ifdef RM2C_HAS_TRAJECTORIES
extern const Trajectory rr_seg7_trajectory_0702EC3C_RM2C_path[];
extern const Trajectory rr_seg7_trajectory_0702ECC0_RM2C_path[];
extern const Trajectory ccm_seg7_trajectory_0701669C_RM2C_path[];
extern const Trajectory bitfs_seg7_trajectory_070159AC_RM2C_path[];
extern const Trajectory hmc_seg7_trajectory_0702B86C_RM2C_path[];
extern const Trajectory lll_seg7_trajectory_0702856C_RM2C_path[];
extern const Trajectory lll_seg7_trajectory_07028660_RM2C_path[];
extern const Trajectory rr_seg7_trajectory_0702ED9C_RM2C_path[];
extern const Trajectory rr_seg7_trajectory_0702EEE0_RM2C_path[];
extern const Trajectory ccm_seg7_trajectory_penguin_race_RM2C_path[];
#endif

void shelled_koopa_attack_handler(s32 attackType);
void obj_spit_fire(s16 relativePosX, s16 relativePosY, s16 relativePosZ, f32 scale, ModelID32 model,
                   f32 startSpeed, f32 endSpeed, s16 movePitch);
void obj_set_speed_to_zero(void);

#endif // OBJ_BEHAVIORS_2_H
