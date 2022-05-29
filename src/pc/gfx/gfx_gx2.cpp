#ifdef RAPI_GX2

#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include <vector>

#ifndef _LANGUAGE_C
#define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#include <gx2/event.h>
#include <gx2/draw.h>
#include <gx2/event.h>
#include <gx2/mem.h>
#include <gx2/registers.h>
#include <gx2/shaders.h>
#include <gx2/state.h>
#include <gx2/texture.h>

#include <whb/log.h>
#include <whb/gfx.h>

#include "gx2_shader_gen.h"
#include "gfx_gx2.h"

#include "gfx_cc.h"
#include "gfx_rendering_api.h"

struct ShaderProgram 
{
    uint32_t shader_id;
    struct ShaderGroup group;
    uint8_t num_inputs;
    bool used_textures[2];
    uint8_t num_floats;
    bool used_noise;
    uint32_t window_params_offset;
    uint32_t samplers_location[2];
};

typedef struct _Texture
{
    GX2Texture texture;
    GX2Sampler sampler;
    bool texture_uploaded;
    bool sampler_set;
}
Texture;

static struct ShaderProgram shader_program_pool[64];
static uint8_t shader_program_pool_size = 0;

static struct ShaderProgram* current_shader_program = nullptr;
static std::vector<float*> vbo_array;

static std::vector<Texture> gx2_textures;
static uint8_t current_tile = 0;
static uint32_t current_texture_ids[2];

static uint32_t frame_count = 0;
static uint32_t current_height = 0;

static BOOL current_depth_test = FALSE;
static BOOL current_depth_write = FALSE;
static GX2CompareFunction current_depth_compare = GX2_COMPARE_FUNC_LEQUAL;

GX2SamplerVar* GX2GetPixelSamplerVar(const GX2PixelShader* shader, const char* name)
{
    for (uint32_t i = 0; i < shader->samplerVarCount; i++)
    {
       if (strcmp(shader->samplerVars[i].name, name) == 0)
           return &(shader->samplerVars[i]);
    }

    return nullptr;
}

s32 GX2GetPixelSamplerVarLocation(const GX2PixelShader* shader, const char* name)
{
    GX2SamplerVar* sampler = GX2GetPixelSamplerVar(shader, name);
    if (!sampler)
        return -1;

    return sampler->location;
}

s32 GX2GetPixelUniformVarOffset(const GX2PixelShader* shader, const char* name)
{
    GX2UniformVar* uniform = GX2GetPixelUniformVar(shader, name);
    if (!uniform)
        return -1;

    return uniform->offset;
}

static bool gfx_gx2_z_is_from_0_to_1(void)
{
    return false;
}

static void gfx_gx2_unload_shader(struct ShaderProgram* old_prg)
{
    if (current_shader_program == old_prg)
        current_shader_program = nullptr;

    else
    {
        // ??????????
    }
}

static void gfx_gx2_set_uniforms(struct ShaderProgram* prg)
{
    if (prg->used_noise)
    {
        float window_params_array[4] = { (float)current_height, (float)frame_count };
        GX2SetPixelUniformReg(prg->window_params_offset, 4, window_params_array);
    }
}

static void gfx_gx2_load_shader(struct ShaderProgram* new_prg)
{
    current_shader_program = new_prg;
    if (!new_prg)
        return;

    GX2SetFetchShader(&new_prg->group.fetchShader);
    GX2SetVertexShader(&new_prg->group.vertexShader);
    GX2SetPixelShader(&new_prg->group.pixelShader);

    gfx_gx2_set_uniforms(new_prg);
}

static struct ShaderProgram* gfx_gx2_create_and_load_new_shader(uint32_t shader_id)
{
    struct CCFeatures cc_features;
    gfx_cc_get_features(shader_id, &cc_features);

    struct ShaderProgram* prg = &shader_program_pool[shader_program_pool_size++];

    const uint8_t *shader_wiiu;

    if (gx2GenerateShaderGroup(&prg->group, &cc_features) != 0)
    {
        WHBLogPrintf("Failed to generate shader");
        return (current_shader_program = nullptr);
    }

    WHBLogPrint("Generated shader");

    // In our case, each attribute has 4 floats
    prg->num_floats = prg->group.numAttributes * 4;

    prg->shader_id = shader_id;
    prg->num_inputs = cc_features.num_inputs;
    prg->used_textures[0] = cc_features.used_textures[0];
    prg->used_textures[1] = cc_features.used_textures[1];

    gfx_gx2_load_shader(prg);

    WHBLogPrintf("Loaded shader");

    prg->window_params_offset = GX2GetPixelUniformVarOffset(&prg->group.pixelShader, "window_params");
    prg->samplers_location[0] = GX2GetPixelSamplerVarLocation(&prg->group.pixelShader, "uTex0");
    prg->samplers_location[1] = GX2GetPixelSamplerVarLocation(&prg->group.pixelShader, "uTex1");
    
    prg->used_noise = cc_features.opt_alpha && cc_features.opt_noise;

    WHBLogPrint("Initiated Shader.");

    return prg;
}

static struct ShaderProgram* gfx_gx2_lookup_shader(uint32_t shader_id)
{
    for (size_t i = 0; i < shader_program_pool_size; i++)
        if (shader_program_pool[i].shader_id == shader_id)
            return &shader_program_pool[i];

    return nullptr;
}

static void gfx_gx2_shader_get_info(struct ShaderProgram* prg, uint8_t* num_inputs, bool used_textures[2])
{
    if (prg)
    {
        *num_inputs = prg->num_inputs;
        used_textures[0] = prg->used_textures[0];
        used_textures[1] = prg->used_textures[1];
    }
    else
    {
        *num_inputs = 0;
        used_textures[0] = false;
        used_textures[1] = false;
    }
}

static uint32_t gfx_gx2_new_texture(void)
{
    size_t texture_id = gx2_textures.size();
    gx2_textures.resize(texture_id + 1);

    Texture& texture = gx2_textures[texture_id];
    texture.texture_uploaded = false;
    texture.sampler_set = false;

    return texture_id;
}

static void gfx_gx2_select_texture(int tile, uint32_t texture_id)
{
    current_tile = tile;
    current_texture_ids[tile] = texture_id;

    if (current_shader_program)
    {
        Texture& texture = gx2_textures[texture_id];
        if (texture.texture_uploaded)
            GX2SetPixelTexture(&texture.texture, current_shader_program->samplers_location[tile]);
        if (texture.sampler_set)
            GX2SetPixelSampler(&texture.sampler, current_shader_program->samplers_location[tile]);
    }
}

static void gfx_gx2_upload_texture(const uint8_t* rgba32_buf, int width, int height)
{
    int tile = current_tile;
    GX2Texture& texture = gx2_textures[current_texture_ids[tile]].texture;

    texture.surface.use       = GX2_SURFACE_USE_TEXTURE;
    texture.surface.dim       = GX2_SURFACE_DIM_TEXTURE_2D;
    texture.surface.width     = width;
    texture.surface.height    = height;
    texture.surface.depth     = 1;
    texture.surface.mipLevels = 1;
    texture.surface.format    = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
    texture.surface.aa        = GX2_AA_MODE1X;
    texture.surface.tileMode  = GX2_TILE_MODE_LINEAR_ALIGNED;
    texture.viewFirstMip      = 0;
    texture.viewNumMips       = 1;
    texture.viewFirstSlice    = 0;
    texture.viewNumSlices     = 1;
    texture.surface.swizzle   = 0;
    texture.surface.alignment = 0;
    texture.surface.pitch     = 0;

    for (uint32_t i = 0; i < 13; i++)
        texture.surface.mipLevelOffset[i] = 0;

    texture.viewFirstMip   = 0;
    texture.viewNumMips    = 1;
    texture.viewFirstSlice = 0;
    texture.viewNumSlices  = 1;
    texture.compMap        = 0x00010203;

    for (uint32_t i = 0; i < 5; i++)
        texture.regs[i] = 0;

    GX2CalcSurfaceSizeAndAlignment(&texture.surface);
    GX2InitTextureRegs(&texture);

    texture.surface.image = memalign(texture.surface.alignment, texture.surface.imageSize);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, texture.surface.image, texture.surface.imageSize);

    GX2Surface surf;
    surf = texture.surface;
    surf.tileMode = GX2_TILE_MODE_LINEAR_SPECIAL;
    surf.image = (void*)rgba32_buf;
    GX2CalcSurfaceSizeAndAlignment(&surf);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, (void*)rgba32_buf, surf.imageSize);
    GX2CopySurface(&surf, 0, 0, &texture.surface, 0, 0);

    if (current_shader_program)
        GX2SetPixelTexture(&texture, current_shader_program->samplers_location[tile]);

    gx2_textures[current_texture_ids[tile]].texture_uploaded = true;

    //WHBLogPrint("Texture set.");
}

static GX2TexClampMode gfx_cm_to_gx2(uint32_t val)
{
    if (val & G_TX_CLAMP)
        return GX2_TEX_CLAMP_MODE_CLAMP;
    else if (val & G_TX_MIRROR)
        return GX2_TEX_CLAMP_MODE_MIRROR;
    else
        return GX2_TEX_CLAMP_MODE_WRAP;
}

static void gfx_gx2_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt)
{
    current_tile = tile;

    GX2Sampler* sampler = &gx2_textures[current_texture_ids[tile]].sampler;
    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, linear_filter ? GX2_TEX_XY_FILTER_MODE_LINEAR : GX2_TEX_XY_FILTER_MODE_POINT);
    GX2InitSamplerClamping(sampler, gfx_cm_to_gx2(cms), gfx_cm_to_gx2(cmt), GX2_TEX_CLAMP_MODE_WRAP);

    if (current_shader_program)
        GX2SetPixelSampler(sampler, current_shader_program->samplers_location[tile]);

    gx2_textures[current_texture_ids[tile]].sampler_set = true;
}

static void gfx_gx2_set_depth_test(bool depth_test)
{
    current_depth_test = depth_test;
    GX2SetDepthOnlyControl(current_depth_test, current_depth_write, current_depth_compare);
}

static void gfx_gx2_set_depth_mask(bool z_upd)
{
    current_depth_write = z_upd;
    GX2SetDepthOnlyControl(current_depth_test, current_depth_write, current_depth_compare);
}

static void gfx_gx2_set_zmode_decal(bool zmode_decal)
{
    if (zmode_decal)
    {
        GX2SetPolygonControl(GX2_FRONT_FACE_CCW, FALSE, FALSE, TRUE,
                             GX2_POLYGON_MODE_TRIANGLE, GX2_POLYGON_MODE_TRIANGLE,
                             TRUE, TRUE, FALSE);

        GX2SetPolygonOffset(-2.0f, -2.0f, -2.0f, -2.0f, 0.0f );
    }
    else
    {
        GX2SetPolygonControl(GX2_FRONT_FACE_CCW, FALSE, FALSE, FALSE,
                             GX2_POLYGON_MODE_TRIANGLE, GX2_POLYGON_MODE_TRIANGLE,
                             FALSE, FALSE, FALSE);

        GX2SetPolygonOffset( 0.0f,  0.0f,  0.0f,  0.0f, 0.0f );
    }
}

static void gfx_gx2_set_viewport(int x, int y, int width, int height)
{
    GX2SetViewport(x, g_window_height - y - height, width, height, 0.0f, 1.0f);
    current_height = height;
}

static void gfx_gx2_set_scissor(int x, int y, int width, int height)
{
    GX2SetScissor(x, g_window_height - y - height, width, height);
}

static void gfx_gx2_set_use_alpha(bool use_alpha)
{
    if (use_alpha)
    {
        GX2SetBlendControl(GX2_RENDER_TARGET_0,
                           GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA,
                           GX2_BLEND_COMBINE_MODE_ADD, FALSE,
                           GX2_BLEND_MODE_ZERO, GX2_BLEND_MODE_ZERO,
                           GX2_BLEND_COMBINE_MODE_ADD);

        GX2SetColorControl(GX2_LOGIC_OP_COPY, 1, FALSE, TRUE);
    }
    else
    {
        GX2SetBlendControl(GX2_RENDER_TARGET_0,
                           GX2_BLEND_MODE_ONE, GX2_BLEND_MODE_ZERO,
                           GX2_BLEND_COMBINE_MODE_ADD, FALSE,
                           GX2_BLEND_MODE_ZERO, GX2_BLEND_MODE_ZERO,
                           GX2_BLEND_COMBINE_MODE_ADD);

        GX2SetColorControl(GX2_LOGIC_OP_COPY, 0, FALSE, TRUE);
    }
}

static void gfx_gx2_draw_triangles(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris)
{
    if (!current_shader_program)
        return;

    size_t idx = vbo_array.size();
    vbo_array.resize(idx + 1);

    size_t vbo_len = sizeof(float) * buf_vbo_len;
    vbo_array[idx] = static_cast<float*>(memalign(0x40, vbo_len));

    float* new_vbo = vbo_array[idx];
    memcpy(new_vbo, buf_vbo, vbo_len);

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_ATTRIBUTE_BUFFER, new_vbo, vbo_len);

    GX2SetAttribBuffer(0, vbo_len, sizeof(float) * current_shader_program->num_floats, new_vbo);
    GX2DrawEx(GX2_PRIMITIVE_MODE_TRIANGLES, 3 * buf_vbo_num_tris, 0, 1);
}

static void gfx_gx2_get_framebuffer(uint16_t *buffer) {
}

static void gfx_gx2_init(void) 
{
}

static void gfx_gx2_on_resize(void) 
{
}

static void gfx_gx2_start_frame(void) 
{
    frame_count++;
}

static void gfx_gx2_end_frame(void) 
{
}

static void gfx_gx2_finish_render(void) 
{
    // Wait until drawing is done
    GX2DrawDone();
    // Free resources
    gfx_gx2_free_vbo();
}

static void gfx_gx2_shutdown(void) 
{
}

extern "C" void gfx_gx2_free_vbo(void)
{
    for (uint32_t i = 0; i < vbo_array.size(); i++)
        free(vbo_array[i]);

    vbo_array.clear();
}

extern "C" void gfx_gx2_free(void)
{
    // Free our textures and shaders
    for (uint32_t i = 0; i < gx2_textures.size(); i++)
    {
        Texture& texture = gx2_textures[i];
        if (texture.texture_uploaded)
            free(texture.texture.surface.image);
    }

    for (uint32_t i = 0; i < shader_program_pool_size; i++)
        gx2FreeShaderGroup(&shader_program_pool[i].group);

    gx2_textures.clear();
    shader_program_pool_size = 0;
}

struct GfxRenderingAPI gfx_gx2_api = {
    gfx_gx2_z_is_from_0_to_1,
    gfx_gx2_unload_shader,
    gfx_gx2_load_shader,
    gfx_gx2_create_and_load_new_shader,
    gfx_gx2_lookup_shader,
    gfx_gx2_shader_get_info,
    gfx_gx2_new_texture,
    gfx_gx2_select_texture,
    gfx_gx2_upload_texture,
    gfx_gx2_set_sampler_parameters,
    gfx_gx2_set_depth_test,
    gfx_gx2_set_depth_mask,
    gfx_gx2_set_zmode_decal,
    gfx_gx2_set_viewport,
    gfx_gx2_set_scissor,
    gfx_gx2_set_use_alpha,
    gfx_gx2_draw_triangles,
    gfx_gx2_get_framebuffer,
    gfx_gx2_init,
    gfx_gx2_on_resize,
    gfx_gx2_start_frame,
    gfx_gx2_end_frame,
    gfx_gx2_finish_render,
    gfx_gx2_shutdown
};

#endif
