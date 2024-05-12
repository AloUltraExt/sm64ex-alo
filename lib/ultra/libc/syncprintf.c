#include "stdarg.h"
#include "macros.h"

#if LIBULTRA_VERSION >= OS_VER_J
void __osSyncVPrintf(UNUSED const char *fmt, UNUSED va_list args) {
    // these functions intentionally left blank.  ifdeffed out in rom release
}
#endif

#if LIBULTRA_VERSION > OS_VER_D
void osSyncPrintf(UNUSED const char *fmt, ...) {
    UNUSED int ans;
    UNUSED va_list ap;
    // these functions intentionally left blank.  ifdeffed out in rom release
}

void rmonPrintf(UNUSED const char *fmt, ...) {
    UNUSED int ans;
    UNUSED va_list ap;
}
#endif
