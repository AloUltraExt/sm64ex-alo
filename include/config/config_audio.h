#pragma once

/// Increase audio heap size to allow for larger/more custom sequences/banks/sfx to be imported without causing issues.
#define EXPAND_AUDIO_HEAP (0 || RM2C || EXTERNAL_DATA)

/**
 * The maximum number of notes (sfx inclusive) that can sound at any given time.
 * Lower values may cause notes to get cut more easily but can potentially improve performance slightly.
 * Lower values may cause problems with streamed audio if a sequence used for it is missing channel priority data.
 * Vanilla by default only generally allocates 16 or 20 notes at once. Memory usage is always determined by the largest of the two values here (~7200 bytes per US/JP note).
 */
#if EXPAND_AUDIO_HEAP
    #define MAX_SIMULTANEOUS_NOTES_EXTERNAL 40
    #define MAX_SIMULTANEOUS_NOTES_CONSOLE  24
#else
    #define MAX_SIMULTANEOUS_NOTES_EXTERNAL 20
    #define MAX_SIMULTANEOUS_NOTES_CONSOLE  16
#endif

#if (MAX_SIMULTANEOUS_NOTES_EXTERNAL >= MAX_SIMULTANEOUS_NOTES_CONSOLE)
    #define MAX_SIMULTANEOUS_NOTES MAX_SIMULTANEOUS_NOTES_EXTERNAL
#else
    #define MAX_SIMULTANEOUS_NOTES MAX_SIMULTANEOUS_NOTES_CONSOLE
#endif

/// Fixes intro castle dialog music so it plays current stage music
#define FIX_INTRO_CASTLE_DIALOG_MUSIC (0 || QOL_FIXES)

/// Fixes missing sounds in key exit cutscene
#define RESTORE_MISSING_SOUNDS_KEY_EXIT (0 || QOL_FIXES)

/// Fixes drowing sound continously playing while being Metal Mario
#define NO_DROWING_SOUND_METAL (0 || QOL_FIXES)

/// Do not restart the music on cap grabs
#define PERSISTENT_CAP_MUSIC (0 || QOL_FEATURES)

/// SAFEGUARDS

// Anything higher than 64 will most likely crash on boot. Even if it doesn't, it's still dangerous.
#if (MAX_SIMULTANEOUS_NOTES > 64)
    #undef MAX_SIMULTANEOUS_NOTES
    #define MAX_SIMULTANEOUS_NOTES 64
#elif (MAX_SIMULTANEOUS_NOTES < 0)
    #undef MAX_SIMULTANEOUS_NOTES
    #define MAX_SIMULTANEOUS_NOTES 0
#endif
