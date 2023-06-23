// Assembly Macros

#ifdef _LANGUAGE_ASSEMBLY
#undef _LANGUAGE_C
#endif

// macOS seems to use a different macro scheme, thanks Apple
#if defined(__APPLE__)
.macro .section label
    \label
.endm

.macro .global label
    .globl \label
.endm

#endif

// Underscore needed for these targets
#if defined(__APPLE__) || (defined(__MINGW32__) && !defined(__MINGW64__))
#    define cdecl(s) _##s
#else
#    define cdecl(s) s
#endif

.macro glabel label
    .global cdecl(\label)
    .balign 4
    cdecl(\label):
.endm

.macro .word32 x
    .word \x
.endm
