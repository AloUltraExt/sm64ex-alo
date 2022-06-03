// Assembly Macros

#if defined(__APPLE__)
.macro .section label
    \label
.endm
#endif
#if defined(__APPLE__) || (defined(__MINGW32__) && !defined(__MINGW64__))
#    define cdecl(s) _##s
#else
#    define cdecl(s) s
#endif

.set K0BASE, 0x80000000
.set K1BASE, 0xA0000000
.set K2BASE, 0xC0000000

.macro glabel label
    .global cdecl(\label)
    .balign 4
    cdecl(\label):
.endm

.macro .word32 x
    .word \x
.endm
