#ifndef QOL_DEFINES_H
#define QOL_DEFINES_H

// Quality of life defines
// Mostly a compilation of code provided by various people

// You can also stub the defines if you don't want them to be applied

// Framebuffer Detection
#ifdef TARGET_N64
#define HAS_FRAMEBUFFER 1
#elif (defined(RAPI_GL) || defined(RAPI_D3D11)) && !defined(OSX_BUILD)
#define HAS_FRAMEBUFFER 1
#else
#define HAS_FRAMEBUFFER 0
#endif

/// Fixes complete coins not giving lives every 50 coins after 150 coins
#define QOL_FIX_COMPLETE_COURSE_50_COINS (0 || QOL_FIXES)
/// Fixes instant warp offset not working when warping across different areas
#define QOL_FIX_INSTANT_WARP_OFFSET (1 || QOL_FIXES)
/// Fixes pss slide value not being reset on exit
#define QOL_FIX_RESET_PSS_SLIDE_STARTED (1 || QOL_FIXES)

// --| Unused Code Fixes (for convenience)
/// Fixes (or rather removes) 0 yaw code in Beta Chest object
#define QOL_FIX_UNUSED_BETA_CHEST_YAW (0 || QOL_FIXES)
/// Fixes play_mode_unused inclusion so it's "used" as a default "invalid" play mode switch
#define QOL_FIX_UNUSED_PLAY_MODE (0 || QOL_FIXES)

// --| Assets Fixes (Mostly on vanilla levels)
/// Fixes impossible coins (also fixes impossible Goomba since it's related)
#define QOL_FIX_ASSET_IMPOSSIBLE_COINS (0 || QOL_FIXES)
/// Fixes 1up locations in CCM slide
#define QOL_FIX_ASSET_CCM_SLIDE_1UPS (0 || QOL_FIXES)

#endif // QOL_DEFINES_H
