// This is a series of defines to edit commonly changed parameters in romhacks
// These are commonly referred to as tweaks

// These values are from vanilla, they don't get used if RM2C=1 because
// they use the ones in src/extras/rm2c/tweaks.h

// Booleans
#define DISABLE_LIVES 0
#define FALL_DAMAGE 1
#define SHOW_STAR_MILESTONES 1
#define CAMERA_MOVE_WHEN_PAUSE 1
#define EXIT_COURSE_ANYWHERE 0
// Miscellaneous 
#define MARIO_START_LIVES 4
#define START_LEVEL LEVEL_CASTLE_GROUNDS
#define COINS_REQ_COINSTAR 100
#define REDS_REQ 8
#define REDS_BOWSER_REQ 8
#define WING_CAP_WARP_STAR_REQ 10
#define LOCKED_CANNON_STAR_REQ 120
#define EXIT_COURSE LEVEL_CASTLE, 1, 31
#define STAR_MILESTONES 1, 3, 8, 30, 50, 70
// King bob-omb
#define KING_BOMB_FVEL 3.0f
#define KING_BOMB_YAWVEL 256
#define KING_BOMB_HEALTH 3
// King whomp
#define KING_WHOMP_HEALTH 3
// Koopa the quick
#define KOOPA_SPEED_RACE_END 8.0f
#define KOOPA_SPEED_THI 6.0f
#define KOOPA_SPEED_BOB 4.0f
// Mips rabbit
#define MIPS1_STAR_REQ 15
#define MIPS2_STAR_REQ 50
// Toad
#define TOAD_STAR_1_REQUIREMENT 12
#define TOAD_STAR_2_REQUIREMENT 25
#define TOAD_STAR_3_REQUIREMENT 35
#define TOAD_STAR_1_DIALOG DIALOG_082
#define TOAD_STAR_2_DIALOG DIALOG_076
#define TOAD_STAR_3_DIALOG DIALOG_083
#define TOAD_STAR_1_DIALOG_AFTER DIALOG_154
#define TOAD_STAR_2_DIALOG_AFTER DIALOG_155
#define TOAD_STAR_3_DIALOG_AFTER DIALOG_156
// Timers
#define SLIDE_TIME 630
#define MC_TIME 600
#define WC_TIME 1800
#define VC_TIME 600
#define MC_LEVEL_TIME 600
#define WC_LEVEL_TIME 1200
#define VC_LEVEL_TIME 600
// HUD booleans
#define SHOW_STARS 1
#define SHOW_COINS 1
#define SHOW_LIVES 1
#define SHOW_CAM 1
#define SHOW_TIMER 1
// Hud positions
#define HUD_LIVES_MARIO_X 22
#define HUD_LIVES_MARIO_Y 209
#define HUD_LIVES_CROSS_X 38
#define HUD_LIVES_CROSS_Y 209
#define HUD_LIVES_NUM_X 54
#define HUD_LIVES_NUM_Y 209
#define HUD_COINS_X 168
#define HUD_COINS_Y 209
#define HUD_COINS_CROSS_X 184
#define HUD_COINS_CROSS_Y 209
#define HUD_COINS_NUM_X 198
#define HUD_COINS_NUM_Y 209
#define HUD_STARS_X 242
#define HUD_STARS_Y 209
#define HUD_STARS_CROSS_X 258
#define HUD_STARS_CROSS_Y 209
#define HUD_STARS_NUM_X 258
#define HUD_STARS_NUM_Y 209
#define HUD_TIME_X 170
#define HUD_TIME_Y 185
#define HUD_TIME_MIN_X 229
#define HUD_TIME_MIN_A_X 239
#define HUD_TIME_SEC_X 249
#define HUD_TIME_SEC_AA_X 274
#define HUD_TIME_FSEC_X 283
#define HUD_TIME_A_Y 32
// Power meter
#define POWER_X 140
#define POWER_Y 166
