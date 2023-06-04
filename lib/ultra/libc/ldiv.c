#include "PR/os_version.h"
#include "stdlib.h"

// Function swapped from 2.0I onwards
#if LIBULTRA_VERSION >= OS_VER_I
ldiv_t ldiv(long num, long denom) {
    ldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;

    if (ret.quot < 0 && ret.rem > 0) {
        ret.quot++;
        ret.rem -= denom;
    }

    return ret;
}
#endif

lldiv_t lldiv(long long num, long long denom) {
    lldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;

    if (ret.quot < 0 && ret.rem > 0) {
        ret.quot++;
        ret.rem -= denom;
    }

    return ret;
}

#if LIBULTRA_VERSION < OS_VER_I
ldiv_t ldiv(long num, long denom) {
    ldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;

    if (ret.quot < 0 && ret.rem > 0) {
        ret.quot++;
        ret.rem -= denom;
    }

    return ret;
}
#endif
