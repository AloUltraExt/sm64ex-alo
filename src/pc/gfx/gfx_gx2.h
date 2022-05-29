#ifndef GFX_GX2_H
#define GFX_GX2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gfx_window_manager_api.h"
#include "gfx_rendering_api.h"

extern struct GfxWindowManagerAPI gfx_gx2_window;
extern struct GfxRenderingAPI gfx_gx2_api;

extern uint32_t g_window_width;
extern uint32_t g_window_height;

void gfx_gx2_free_vbo(void);
void gfx_gx2_free(void);

#ifdef __cplusplus
}
#endif

#endif
