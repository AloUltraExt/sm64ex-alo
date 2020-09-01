#ifndef GFX_WHB_H
#define GFX_WHB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gfx_window_manager_api.h"
#include "gfx_rendering_api.h"

extern struct GfxWindowManagerAPI gfx_whb_window;
extern struct GfxRenderingAPI gfx_whb_api;
extern uint32_t window_height;

bool whb_window_is_running();
void whb_free_vbo(void);
void whb_free(void);

#ifdef __cplusplus
}
#endif

#endif
