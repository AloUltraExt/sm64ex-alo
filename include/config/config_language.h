/**
 * Adds support for multiple languages to the game.
 */
// #define MULTILANG

/**
 * Toggles for individual languages. Only works when MULTILANG is enabled.
 * Note that English will always be enabled.
 */
#define ENABLE_FRENCH
#define ENABLE_GERMAN
// #define ENABLE_JAPANESE

/**
 * This define enables support for Japanese characters even when multilang or Japanese is not enabled.
 * Requires a Japanese baserom.
 */
#define JAPANESE_CHARACTERS (0 || VERSION_JP || VERSION_SH || ENABLE_JAPANESE)

/**
 * This replaces translation specific defines to general ones to be used for more languages.
 */
//#define SIMPLE_MULTILANG_ASSETS

#ifndef MULTILANG
    #undef ENABLE_FRENCH
    #undef ENABLE_GERMAN
    #undef ENABLE_JAPANESE
#endif // !MULTILANG
