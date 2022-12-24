#ifndef INGAME_MENU_H
#define INGAME_MENU_H

#include <PR/ultratypes.h>
#include "types.h"

enum MenuMtxPushOp {
    MENU_MTX_NONE,
    MENU_MTX_PUSH,
    MENU_MTX_NOPUSH,
};

enum MenuScrollAxis {
    MENU_SCROLL_NONE,
    MENU_SCROLL_VERTICAL,
    MENU_SCROLL_HORIZONTAL,
};

enum MenuMode {
    MENU_MODE_NONE = -1,
    MENU_MODE_UNUSED_0,
    MENU_MODE_RENDER_PAUSE_SCREEN,
    MENU_MODE_RENDER_COURSE_COMPLETE_SCREEN,
    MENU_MODE_UNUSED_3
};

enum HUDFlashModes {
    HUD_FLASH_NONE,
    HUD_FLASH_STARS,
    HUD_FLASH_KEYS
};

extern s8 gHudFlash;

extern s8 gDialogCourseActNum;
extern u8 gInGameLanguage;
extern void *languageTable[][3];

struct AsciiCharLUTEntry {
    const Texture *texture;
    const s8 kerning;
};

// Convert an ASCII char to the index in the ASCII LUT. ASCII LUTs start at the space character.
#define ASCII_LUT_INDEX(c) ((c) - ' ')

// Macro to quickly get the kerning of the space character from an ASCII LUT.
#define SPACE_KERNING(lut) (((struct AsciiCharLUTEntry *)(lut))[ASCII_LUT_INDEX(' ')].kerning)

// The character used to indicate a color code in a generic string.
// As of now, must be an ASCII character.
#define CHAR_COLOR_CODE '@'

struct Utf8CharLUTEntry {
    u32 codepoint;
    s8 kerning;
    u16 flags; // used for diacritics and packed textures
    Texture *texture;
};

struct Utf8LUT {
    struct Utf8CharLUTEntry *lut2Bytes;
    struct Utf8CharLUTEntry *lut3Bytes;
    struct Utf8CharLUTEntry *lut4Bytes;
    u16 length2Bytes; // set these with the ARRAY_COUNT macro
    u16 length3Bytes;
    u16 length4Bytes;
    struct Utf8CharLUTEntry *missingChar;
};

struct DiacriticLUTEntry {
    s8 xOffset;
    s8 yOffset;
    char *str;
};

enum TextDiacriticMarks {
    TEXT_DIACRITIC_NONE,
    TEXT_DIACRITIC_CIRCUMFLEX,
    TEXT_DIACRITIC_CIRCUMFLEX_UPPERCASE,
    TEXT_DIACRITIC_ACUTE,
    TEXT_DIACRITIC_ACUTE_UPPERCASE,
    TEXT_DIACRITIC_GRAVE,
    TEXT_DIACRITIC_GRAVE_UPPERCASE,
    TEXT_DIACRITIC_TILDE,
    TEXT_DIACRITIC_TILDE_UPPERCASE,
    TEXT_DIACRITIC_UMLAUT,
    TEXT_DIACRITIC_UMLAUT_UPPERCASE,
    TEXT_DIACRITIC_CEDILLA,
#ifdef JAPANESE_CHARACTERS
    TEXT_DIACRITIC_DAKUTEN,
    TEXT_DIACRITIC_HANDAKUTEN,
#endif
};

enum TextAlignments {
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT,
};

#define TEXT_FLAG_PACKED 0x8000
#define TEXT_DIACRITIC_MASK 0x00FF
// bits 0x0100 through 0x4000 are free for use, and the mask can be reduced if necessary

struct DialogEntry {
    /*0x00*/ s32 voice;
    /*0x04*/ s8 linesPerBox;
    /*0x06*/ s16 leftOffset;
    /*0x08*/ s16 width;
    /*0x0C*/ const char *str;
};

// gDialogResponse
enum DialogResponseDefines {
    DIALOG_RESPONSE_NONE,
    DIALOG_RESPONSE_YES,
    DIALOG_RESPONSE_NO,
    DIALOG_RESPONSE_NOT_DEFINED,
    DIALOG_RESPONSE_MAXIMUM = 32
};

// Types and defines for handling language arrays
#ifdef MULTILANG

enum MultilangLanguages {
    LANGUAGE_ENGLISH,
    LANGUAGE_FRENCH,
    LANGUAGE_GERMAN,
    LANGUAGE_JAPANESE,
    LANGUAGE_COUNT
};

typedef char * LangArray[LANGUAGE_COUNT];
#define LANG_ARRAY(cmd) ((cmd)[gInGameLanguage])
#define DEFINE_LANGUAGE_ARRAY(english, french, german, japanese) {english, french, german, japanese}

#else

// If multilang is off, ignore all other languages and only include English.
#define LANGUAGE_ENGLISH 0

typedef char * LangArray;
#define LANG_ARRAY(cmd) (cmd)
#define DEFINE_LANGUAGE_ARRAY(english, french, german, japanese) english

#endif

typedef union {
    s32 asInt;
    char *asStr;
} DialogVariable;

extern s32 gDialogResponse;
extern u16 gDialogColorFadeTimer;
extern s8  gLastDialogLineNum;
extern DialogVariable gDialogVariable;
extern u16 gDialogTextAlpha;
extern s8  gRedCoinsCollected;

/*
 * Regarding get_str_x_pos_from_center / get_str_x_pos_from_center_scale:
 * They cannot use a macro due to the new print_generic_string function.
 * Instead as a replacement you can  use print_generic_string_aligned and
 * set TEXT_ALIGN_CENTER as it's alignment value.
*/

u8 check_number_string_in_course_name(char *courseName);

void create_dl_identity_matrix(void);
void create_dl_translation_matrix(s8 pushOp, f32 x, f32 y, f32 z);
void create_dl_ortho_matrix(void);
void create_dl_scale_matrix(s8 pushOp, f32 x, f32 y, f32 z);

s32 get_string_width(char *str, struct AsciiCharLUTEntry *asciiLut, struct Utf8LUT *utf8LUT);
void format_int_to_string(char *buf, s32 value);
#define int_to_str(int, str)    format_int_to_string(str, int); // backwards compatibility
void print_generic_string(s16 x, s16 y, char *str);
void print_hud_lut_string(s16 x, s16 y, char *str);
void print_menu_generic_string(s16 x, s16 y, char *str);
void print_credits_string(s16 x, s16 y, char *str);
void print_generic_string_aligned(s16 x, s16 y, char *str, u32 alignment);
void print_hud_lut_string_aligned(s16 x, s16 y, char *str, u32 alignment);
void print_menu_generic_string_aligned(s16 x, s16 y, char *str, u32 alignment);
void print_credits_string_aligned(s16 x, s16 y, char *str, u32 alignment);

void handle_menu_scrolling(s8 scrollDirection, s8 *currentIndex, s8 minIndex, s8 maxIndex);
void print_hud_my_score_coins(s32 useCourseCoinScore, s8 fileIndex, s8 courseIndex, s16 x, s16 y);
s32 get_dialog_id(void);
void create_dialog_box(s16 dialog);
void create_dialog_box_with_int_var(s16 dialog, s32 dialogVar);
void create_dialog_box_with_str_var(s16 dialog, char *dialogVar);
void create_dialog_box_with_var(s16 dialog, DialogVariable dialogVar);
void create_dialog_inverted_box(s16 dialog);
void create_dialog_box_with_response(s16 dialog);
void reset_dialog_render_state(void);
void set_menu_mode(s16 mode);
void reset_cutscene_msg_fade(void);
void dl_rgba16_begin_cutscene_msg_fade(void);
void dl_rgba16_stop_cutscene_msg_fade(void);
void set_cutscene_message(s16 msgIndex, s16 msgDuration);
void do_cutscene_handler(void);
void render_hud_cannon_reticle(void);
void reset_red_coins_collected(void);
s32 render_menus_and_dialogs(void);

#endif // INGAME_MENU_H
