#ifndef MACROS_H
#define MACROS_H

#include "platform_info.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#define GLUE(a, b) a ## b
#define GLUE2(a, b) GLUE(a, b)

// Avoid compiler warnings for unused variables
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

#ifdef __GNUC__
#define FALL_THROUGH __attribute__((fallthrough))
#else
#define FALL_THROUGH
#endif

// Avoid undefined behaviour for non-returning functions
#ifdef __GNUC__
#define NORETURN __attribute__((noreturn))
#else
#define NORETURN
#endif

// Avoid inline a function
#ifdef __GNUC__
#define NO_INLINE inline __attribute__((noinline))
#else
#define NO_INLINE inline
#endif

// Always inline a function
#ifdef __GNUC__
#define ALWAYS_INLINE inline __attribute__((always_inline))
#else
#define ALWAYS_INLINE inline
#endif

// Use Os when compiling the function
#ifdef __GNUC__
#define OPTIMIZE_OS __attribute__((optimize("Os")))
#else
#define OPTIMIZE_OS
#endif

// Use Ofast when compiling the function
#ifdef __GNUC__
#define OPTIMIZE_OFAST __attribute__((optimize("Ofast")))
#else
#define OPTIMIZE_OFAST
#endif

// Static assertions
#ifdef __GNUC__
#define STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#else
#define STATIC_ASSERT(cond, msg) typedef char GLUE2(static_assertion_failed, __LINE__)[(cond) ? 1 : -1]
#endif

// Align to 8-byte boundary (for DMA requirements)
#ifdef __GNUC__
#define ALIGNED8 __attribute__((aligned(8)))
#else
#define ALIGNED8
#endif

// Align to 16-byte boundary (for audio lib requirements)
#ifdef __GNUC__
#define ALIGNED16 __attribute__((aligned(16)))
#else
#define ALIGNED16
#endif

// Align to 32-byte boundary
#ifdef __GNUC__
#define ALIGNED32 __attribute__((aligned(32)))
#else
#define ALIGNED32
#endif

// Align to 64-byte boundary
#ifdef __GNUC__
#define ALIGNED64 __attribute__((aligned(64)))
#else
#define ALIGNED64
#endif

#ifndef NO_SEGMENTED_MEMORY
// convert a virtual address to physical.
#define VIRTUAL_TO_PHYSICAL(addr)   ((uintptr_t)(addr) & 0x1FFFFFFF)

// convert a physical address to virtual.
#define PHYSICAL_TO_VIRTUAL(addr)   ((uintptr_t)(addr) | 0x80000000)

// another way of converting virtual to physical
#define VIRTUAL_TO_PHYSICAL2(addr)  ((u8 *)(addr) - 0x80000000U)
#else
// no conversion for pc port other than cast
#define VIRTUAL_TO_PHYSICAL(addr)   ((uintptr_t)(addr))
#define PHYSICAL_TO_VIRTUAL(addr)   ((uintptr_t)(addr))
#define VIRTUAL_TO_PHYSICAL2(addr)  ((void *)(addr))
#endif

// Byteswap macros
#define BSWAP16(x) (((x) & 0xFF) << 8 | (((x) >> 8) & 0xFF))
#define BSWAP32(x) \
    ( (((x) >> 24) & 0x000000FF) | (((x) >>  8) & 0x0000FF00) | \
      (((x) <<  8) & 0x00FF0000) | (((x) << 24) & 0xFF000000) )

// Convenience macros for endian conversions
#if IS_BIG_ENDIAN
# define BE_TO_HOST16(x) (x)
# define BE_TO_HOST32(x) (x)
# define LE_TO_HOST16(x) BSWAP16(x)
# define LE_TO_HOST32(x) BSWAP32(x)
#else
# define BE_TO_HOST16(x) BSWAP16(x)
# define BE_TO_HOST32(x) BSWAP32(x)
# define LE_TO_HOST16(x) (x)
# define LE_TO_HOST32(x) (x)
#endif

#endif // MACROS_H
