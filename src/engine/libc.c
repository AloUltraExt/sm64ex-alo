#include <ultra64.h>

#include "sm64.h"

#if defined(TARGET_N64) && defined(__GNUC__)
extern void bcopy(const void *, void *, size_t);

/*
 * Due to GCC's freestanding requirements, memset, memcmp, and memmove
 * are required to be implemented here. (memcpy is already implemented
 * in libultra.)
 */

void *memset(void *dest, int c, size_t n) {
    u8 *local_dest = dest;
    int i;

    for(i = 0; i < n; i++) {
        local_dest[i] = c;
    }
    return dest;
}

int memcmp(const void *str1, const void *str2, size_t n) {
    u8 *local_str1 = str1;
    u8 *local_str2 = str2;

    while (n --> 0) {
        if (*local_str1++ != *local_str2++) {
            return local_str1[-1] < local_str2[-1] ? -1 : 1;
        }
    }
    return 0;
}

void *memmove(void *str1, const void *str2, size_t n) {
    bcopy(str2, str1, n);
    return str1;
}

int strcmp(char *s, char *t) {
    int i;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

#endif
