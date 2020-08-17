#ifndef PLATFORM_INFO_H
#define PLATFORM_INFO_H

#ifdef TARGET_N64
#define IS_64_BIT 0
#define IS_BIG_ENDIAN 1
#else
#include <stdint.h>
#define IS_64_BIT (UINTPTR_MAX == 0xFFFFFFFFFFFFFFFFU)
#define IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#endif

#ifdef TARGET_N64
#define DOUBLE_SIZE_ON_64_BIT(size) ((size) * (sizeof(void *) / 4))
#else
// Using 8 here instead of sizeof(size_t) to ensure compatibility
#define SIZEOF_POINTER (size_t)8
#define DOUBLE_SIZE_ON_64_BIT(size) ((size) * (SIZEOF_POINTER / 4))
#endif

#endif // PLATFORM_INFO_H
