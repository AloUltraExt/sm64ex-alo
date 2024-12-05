#ifndef GFX_PC_H
#define GFX_PC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
#include <unordered_map>
#include <list>
#include <cstddef>
#endif

//#include "libultraship/libultra/gbi.h"
//#include "libultraship/libultra/types.h"

#include <PR/ultratypes.h>
#include <PR/gbi.h>

typedef float MtxF_t[4][4];
typedef union {
    MtxF_t mf;
    struct {
        float xx, yx, zx, wx, xy, yy, zy, wy, xz, yz, zz, wz, xw, yw, zw, ww;
    };
} MtxF;

// TODO figure out why changing these to 640x480 makes the game only render in a quarter of the window
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#include "gfx_defines.h"

extern uintptr_t gfxFramebuffer;

struct GfxRenderingAPI;
struct GfxWindowManagerAPI;

struct XYWidthHeight {
    int16_t x, y;
    uint32_t width, height;
};

struct GfxDimensions {
    float internal_mul;
    uint32_t width, height;
    float aspect_ratio;
};

#ifdef __cplusplus
struct TextureCacheKey {
    const uint8_t* texture_addr;
    const uint8_t* palette_addrs[2];
    uint8_t fmt, siz;
    uint8_t palette_index;

    bool operator==(const TextureCacheKey&) const noexcept = default;

    struct Hasher {
        size_t operator()(const TextureCacheKey& key) const noexcept {
            uintptr_t addr = (uintptr_t)key.texture_addr;
            return (size_t)(addr ^ (addr >> 5));
        }
    };
};

typedef std::unordered_map<TextureCacheKey, struct TextureCacheValue, TextureCacheKey::Hasher> TextureCacheMap;
typedef std::pair<const TextureCacheKey, struct TextureCacheValue> TextureCacheNode;

struct TextureCacheValue {
    uint32_t texture_id;
    uint8_t cms, cmt;
    bool linear_filter;

    std::list<struct TextureCacheMapIter>::iterator lru_location;
};

struct TextureCacheMapIter {
    TextureCacheMap::iterator it;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern struct GfxDimensions gfx_current_window_dimensions; // The dimensions of the window
extern struct GfxDimensions
    gfx_current_dimensions; // The dimensions of the draw area the game draws to, before scaling (if applicable)
extern struct XYWidthHeight
    gfx_current_game_window_viewport; // The area of the window the game is drawn to, (0, 0) is top-left corner
extern uint32_t gfx_msaa_level;
#ifdef __cplusplus
}
#endif


void gfx_init(struct GfxWindowManagerAPI* wapi, struct GfxRenderingAPI* rapi, const char* game_name,
              bool start_in_fullscreen, uint32_t width, uint32_t height);
struct GfxRenderingAPI* gfx_get_current_rendering_api(void);
void gfx_start_frame(void);
//void gfx_run(Gfx* commands, const std::unordered_map<Mtx*, MtxF>& mtx_replacements);
void gfx_run(Gfx* commands);
void gfx_end_frame(void);
#ifndef LEGACY_GFX_WIDOW_API
void gfx_set_target_fps(int);
void gfx_set_maximum_frame_latency(int latency);
float gfx_get_detected_hz(void);
#endif
void gfx_texture_cache_clear();
#ifdef __cplusplus
extern "C" int gfx_create_framebuffer(uint32_t width, uint32_t height);
#else
int gfx_create_framebuffer(uint32_t width, uint32_t height);
#endif
void gfx_get_pixel_depth_prepare(float x, float y);
uint16_t gfx_get_pixel_depth(float x, float y);

#endif
