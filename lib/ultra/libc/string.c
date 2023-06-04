#include "PR/os_version.h"
#include <string.h>

// Functions swapped from 2.0I onwards
#if LIBULTRA_VERSION >= OS_VER_I
char *strchr(const char *s, int c) {
    char ch = c;
    while (*s != ch) {
        if (*s == 0) {
            return NULL;
        }
        s++;
    }
    return (char *) s;
}

size_t strlen(const char *s) {
    const char *sc = s;
    while (*sc) {
        sc++;
    }
    return sc - s;
}
#endif

void *memcpy(void *dst, const void *src, size_t size) {
    u8 *_dst = dst;
    const u8 *_src = src;
    while (size > 0) {
        *_dst++ = *_src++;
        size--;
    }
    return dst;
}

#if LIBULTRA_VERSION < OS_VER_I
size_t strlen(const char *s) {
    const unsigned char *sc = (const unsigned char *) s;
    while (*sc) {
        sc++;
    }
    return (const char *) sc - s;
}

char *strchr(const char *s, int c) {
    unsigned char ch = c;
    while (*(unsigned char *)s != ch) {
        if (*(unsigned char *)s == 0) {
            return NULL;
        }
        s++;
    }
    return (char *) s;
}
#endif
