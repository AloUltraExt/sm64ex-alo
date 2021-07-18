#ifdef RAPI_WHB

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
#include <gx2/mem.h>
#include <gx2/registers.h>
#include <gx2/state.h>
#include <gx2/swap.h>

#include <whb/log.h>
#include <whb/gfx.h>

#include "shaders_wiiu/shaders_wiiu.h"
#include "gfx_cc.h"
#include "gfx_rendering_api.h"
#include "gfx_whb.h"

struct ShaderProgram {
    uint32_t shader_id;
    WHBGfxShaderGroup group;
    uint8_t num_inputs;
    bool used_textures[2];
    uint8_t num_floats;
    bool used_noise;
    //uint32_t frame_count_offset;
    //uint32_t window_height_offset;
    uint32_t samplers_location[2];
};

typedef struct _Texture
{
     GX2Texture texture;
     GX2Sampler sampler;
     bool textureUploaded;
     bool samplerSet;
} Texture;

static struct ShaderProgram shader_program_pool[64];
static uint8_t shader_program_pool_size = 0;

static struct ShaderProgram *current_shader_program = NULL;
static std::vector<float*> vbo_array;

static std::vector<Texture> whb_textures;
static uint8_t current_tile = 0;
static uint32_t current_texture_ids[2];

static uint32_t frame_count = 0;
static uint32_t current_height = 0;

static BOOL current_depth_test = FALSE;
static BOOL current_depth_write = FALSE;
static GX2CompareFunction current_depth_compare = GX2_COMPARE_FUNC_LEQUAL;

GX2SamplerVar *GX2GetPixelSamplerVar(const GX2PixelShader *shader, const char *name)
{
    for (uint32_t i = 0; i < shader->samplerVarCount; i++)
    {
       if (strcmp(shader->samplerVars[i].name, name) == 0)
           return &(shader->samplerVars[i]);
    }

    return NULL;
}

s32 GX2GetPixelSamplerVarLocation(const GX2PixelShader *shader, const char *name)
{
    GX2SamplerVar *sampler = GX2GetPixelSamplerVar(shader, name);
    if (!sampler)
        return -1;

    return sampler->location;
}

/*
s32 GX2GetPixelUniformVarOffset(const GX2PixelShader *shader, const char *name)
{
    GX2UniformVar *uniform = GX2GetPixelUniformVar(shader, name);
    if (!uniform)
        return -1;

    return uniform->offset;
}
*/

static bool gfx_whb_z_is_from_0_to_1(void) {
    return false;
}

static void gfx_whb_unload_shader(struct ShaderProgram *old_prg) {
    if (current_shader_program == old_prg) {
        current_shader_program = NULL;
    } else {
        // ??????????
    }
}

static void gfx_whb_set_uniforms(struct ShaderProgram *prg) {
    /*
    if (prg->used_noise) {
        uint32_t frame_count_array[4] = { frame_count, 0, 0, 0 };
        uint32_t window_height_array[4] = { current_height, 0, 0, 0 };

        GX2SetPixelUniformReg(prg->frame_count_offset, 4, frame_count_array);
        GX2SetPixelUniformReg(prg->window_height_offset, 4, window_height_array);
    }
    */
}

static void gfx_whb_load_shader(struct ShaderProgram *new_prg) {
    current_shader_program = new_prg;
    if (new_prg == NULL)
        return;

    GX2SetFetchShader(&new_prg->group.fetchShader);
    GX2SetVertexShader(new_prg->group.vertexShader);
    GX2SetPixelShader(new_prg->group.pixelShader);

    gfx_whb_set_uniforms(new_prg);
}

static struct ShaderProgram *gfx_whb_create_and_load_new_shader(uint32_t shader_id) {
    struct CCFeatures cc_features;
    gfx_cc_get_features(shader_id, &cc_features);

    struct ShaderProgram *prg = &shader_program_pool[shader_program_pool_size++];

    const uint8_t *shader_wiiu;

    switch (shader_id) {
        case 0x01200200:
            shader_wiiu = shader_wiiu_01200200;
            break;
        case 0x00000045:
            shader_wiiu = shader_wiiu_00000045;
            break;
        case 0x00000200:
            shader_wiiu = shader_wiiu_00000200;
            break;
        case 0x01200a00:
            shader_wiiu = shader_wiiu_01200a00;
            break;
        case 0x00000a00:
            shader_wiiu = shader_wiiu_00000a00;
            break;
        case 0x01a00045:
            shader_wiiu = shader_wiiu_01a00045;
            break;
        case 0x00000551:
            shader_wiiu = shader_wiiu_00000551;
            break;
        case 0x01045045:
            shader_wiiu = shader_wiiu_01045045;
            break;
        case 0x05a00a00:
            shader_wiiu = shader_wiiu_05a00a00;
            break;
        case 0x01200045:
            shader_wiiu = shader_wiiu_01200045;
            break;
        case 0x05045045:
            shader_wiiu = shader_wiiu_05045045;
            break;
        case 0x01045a00:
            shader_wiiu = shader_wiiu_01045a00;
            break;
        case 0x01a00a00:
            shader_wiiu = shader_wiiu_01a00a00;
            break;
        case 0x0000038d:
            shader_wiiu = shader_wiiu_0000038d;
            break;
        case 0x01081081:
            shader_wiiu = shader_wiiu_01081081;
            break;
        case 0x0120038d:
            shader_wiiu = shader_wiiu_0120038d;
            break;
        case 0x03200045:
            shader_wiiu = shader_wiiu_03200045;
            break;
        case 0x03200a00:
            shader_wiiu = shader_wiiu_03200a00;
            break;
        case 0x01a00a6f:
            shader_wiiu = shader_wiiu_01a00a6f;
            break;
        case 0x01141045:
            shader_wiiu = shader_wiiu_01141045;
            break;
        case 0x07a00a00:
            shader_wiiu = shader_wiiu_07a00a00;
            break;
        case 0x05200200:
            shader_wiiu = shader_wiiu_05200200;
            break;
        case 0x03200200:
            shader_wiiu = shader_wiiu_03200200;
            break;
        case 0x09200200:
            shader_wiiu = shader_wiiu_09200200;
            break;
        case 0x0920038d:
            shader_wiiu = shader_wiiu_0920038d;
            break;
        case 0x09200045:
            shader_wiiu = shader_wiiu_09200045;
            break;
        case 0x09200a00:
            shader_wiiu = shader_wiiu_09200a00;
            break;
        default:
error:
            WHBLogPrintf("Shader create failed! shader_id: 0x%x", shader_id);
            shader_program_pool_size--;
            current_shader_program = NULL;
            return NULL;
    }

    if (!WHBGfxLoadGFDShaderGroup(&prg->group, 0, shader_wiiu)) {
        goto error;
    }

    WHBLogPrint("Loaded GFD.");

    uint32_t pos = 0;
    prg->num_floats = 0;

    if (!WHBGfxInitShaderAttribute(&prg->group, "aVtxPos", 0, pos, GX2_ATTRIB_FORMAT_FLOAT_32_32_32_32)) {
        goto error;
    }

    pos += 4 * sizeof(float);
    prg->num_floats += 4;

    if (cc_features.used_textures[0] || cc_features.used_textures[1]) {
        if (!WHBGfxInitShaderAttribute(&prg->group, "aTexCoord", 0, pos, GX2_ATTRIB_FORMAT_FLOAT_32_32)) {
            goto error;
        }

        pos += (2+2) * sizeof(float); // 2 floats for the texcoord + 2 floats (8 bytes) as padding, for faster GPU reading
        prg->num_floats += (2+2);
    }

    if (cc_features.opt_fog) {
        if (!WHBGfxInitShaderAttribute(&prg->group, "aFog", 0, pos, GX2_ATTRIB_FORMAT_FLOAT_32_32_32_32)) {
            goto error;
        }

        pos += 4 * sizeof(float);
        prg->num_floats += 4;
    }

    for (int i = 0; i < cc_features.num_inputs; i++) {
        char name[16];
        sprintf(name, "aInput%d", i + 1);
        if (!WHBGfxInitShaderAttribute(&prg->group, name, 0, pos, GX2_ATTRIB_FORMAT_FLOAT_32_32_32_32)) {
            goto error;
        }

        pos += 4 * sizeof(float);
        prg->num_floats += 4;
    }

    if (!WHBGfxInitFetchShader(&prg->group)) {
        goto error;
    }

    WHBLogPrint("Initiated Fetch Shader.");

    prg->shader_id = shader_id;
    prg->num_inputs = cc_features.num_inputs;
    prg->used_textures[0] = cc_features.used_textures[0];
    prg->used_textures[1] = cc_features.used_textures[1];

    gfx_whb_load_shader(prg);

    WHBLogPrintf("Shader mode: %u", (uint32_t)prg->group.pixelShader->mode);

    prg->samplers_location[0] = GX2GetPixelSamplerVarLocation(prg->group.pixelShader, "uTex0");
    prg->samplers_location[1] = GX2GetPixelSamplerVarLocation(prg->group.pixelShader, "uTex1");

    /*
    prg->frame_count_offset = GX2GetPixelUniformVarOffset(prg->group.pixelShader, "frame_count");
    prg->window_height_offset = GX2GetPixelUniformVarOffset(prg->group.pixelShader, "window_height");
    */

    if (cc_features.opt_alpha && cc_features.opt_noise) {
        prg->used_noise = true;
    } else {
        prg->used_noise = false;
    }

    WHBLogPrint("Initiated Tex/Frame/Height uniforms.");
    WHBLogPrint("Initiated Shader.");

    return prg;
}

static struct ShaderProgram *gfx_whb_lookup_shader(uint32_t shader_id) {
    for (size_t i = 0; i < shader_program_pool_size; i++) {
        if (shader_program_pool[i].shader_id == shader_id) {
            return &shader_program_pool[i];
        }
    }
    return NULL;
}

static void gfx_whb_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    if (prg != NULL) {
        *num_inputs = prg->num_inputs;
        used_textures[0] = prg->used_textures[0];
        used_textures[1] = prg->used_textures[1];
    } else {
        *num_inputs = 0;
        used_textures[0] = false;
        used_textures[1] = false;
    }
}

static uint32_t gfx_whb_new_texture(void) {
    whb_textures.resize(whb_textures.size() + 1);
    uint32_t texture_id = (uint32_t)(whb_textures.size() - 1);

    Texture& texture = whb_textures[texture_id];
    texture.textureUploaded = false;
    texture.samplerSet = false;

    return texture_id;
}

static void gfx_whb_select_texture(int tile, uint32_t texture_id) {
    current_tile = tile;
    current_texture_ids[tile] = texture_id;

    if (current_shader_program != NULL) {
        Texture& texture = whb_textures[texture_id];
        if (texture.textureUploaded) {
            GX2SetPixelTexture(&texture.texture, current_shader_program->samplers_location[tile]);
        }
        if (texture.samplerSet) {
            GX2SetPixelSampler(&texture.sampler, current_shader_program->samplers_location[tile]);
        }
    }
}

static void gfx_whb_upload_texture(const uint8_t *rgba32_buf, int width, int height) {
    int tile = current_tile;
    GX2Texture& texture = whb_textures[current_texture_ids[tile]].texture;

    texture.surface.use =         GX2_SURFACE_USE_TEXTURE;
    texture.surface.dim =         GX2_SURFACE_DIM_TEXTURE_2D;
    texture.surface.width =       width;
    texture.surface.height =      height;
    texture.surface.depth =       1;
    texture.surface.mipLevels =   1;
    texture.surface.format =      GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
    texture.surface.aa =          GX2_AA_MODE1X;
    texture.surface.tileMode =    GX2_TILE_MODE_LINEAR_ALIGNED;
    texture.viewFirstMip =        0;
    texture.viewNumMips =         1;
    texture.viewFirstSlice =      0;
    texture.viewNumSlices =       1;
    texture.surface.swizzle =     0;
    texture.surface.alignment =   0;
    texture.surface.pitch =       0;

    uint32_t i;
    for(i = 0; i < 13; i++) {
        texture.surface.mipLevelOffset[i] = 0;
    }
    texture.viewFirstMip = 0;
    texture.viewNumMips = 1;
    texture.viewFirstSlice = 0;
    texture.viewNumSlices = 1;
    texture.compMap = 0x00010203;
    for(i = 0; i < 5; i++){
        texture.regs[i] = 0;
    }

    GX2CalcSurfaceSizeAndAlignment(&texture.surface);
    GX2InitTextureRegs(&texture);

    texture.surface.image = memalign(texture.surface.alignment, texture.surface.imageSize);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, texture.surface.image, texture.surface.imageSize);

    GX2Surface surf;
    surf = texture.surface;
    surf.tileMode = GX2_TILE_MODE_LINEAR_SPECIAL;
    surf.image = (void *)rgba32_buf;
    GX2CalcSurfaceSizeAndAlignment(&surf);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, (void *)rgba32_buf, surf.imageSize);
    GX2CopySurface(&surf, 0, 0, &texture.surface, 0, 0);

    if (current_shader_program != NULL) {
        GX2SetPixelTexture(&texture, current_shader_program->samplers_location[tile]);
    }
    whb_textures[current_texture_ids[tile]].textureUploaded = true;

    //WHBLogPrint("Texture set.");
}

static GX2TexClampMode gfx_cm_to_gx2(uint32_t val) {
    if (val & G_TX_CLAMP) {
        return GX2_TEX_CLAMP_MODE_CLAMP;
    }
    return (val & G_TX_MIRROR) ? GX2_TEX_CLAMP_MODE_MIRROR : GX2_TEX_CLAMP_MODE_WRAP;
}

static void gfx_whb_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt) {
    current_tile = tile;

    GX2Sampler *sampler = &whb_textures[current_texture_ids[tile]].sampler;
    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, linear_filter ? GX2_TEX_XY_FILTER_MODE_LINEAR : GX2_TEX_XY_FILTER_MODE_POINT);
    GX2InitSamplerClamping(sampler, gfx_cm_to_gx2(cms), gfx_cm_to_gx2(cmt), GX2_TEX_CLAMP_MODE_WRAP);

    if (current_shader_program != NULL) {
        GX2SetPixelSampler(sampler, current_shader_program->samplers_location[tile]);
    }
    whb_textures[current_texture_ids[tile]].samplerSet = true;
}

static void gfx_whb_set_depth_test(bool depth_test) {
    current_depth_test = depth_test;
    GX2SetDepthOnlyControl(current_depth_test, current_depth_write, current_depth_compare);
}

static void gfx_whb_set_depth_mask(bool z_upd) {
    current_depth_write = z_upd;
    GX2SetDepthOnlyControl(current_depth_test, current_depth_write, current_depth_compare);
}

static void gfx_whb_set_zmode_decal(bool zmode_decal) {
    if (zmode_decal) {
        GX2SetPolygonControl(GX2_FRONT_FACE_CCW, FALSE, FALSE, TRUE,
                             GX2_POLYGON_MODE_TRIANGLE, GX2_POLYGON_MODE_TRIANGLE,
                             TRUE, TRUE, FALSE);
        GX2SetPolygonOffset(-2.0f, -2.0f, -2.0f, -2.0f, 0.0f );
    } else {
        GX2SetPolygonControl(GX2_FRONT_FACE_CCW, FALSE, FALSE, FALSE,
                             GX2_POLYGON_MODE_TRIANGLE, GX2_POLYGON_MODE_TRIANGLE,
                             FALSE, FALSE, FALSE);
        GX2SetPolygonOffset( 0.0f,  0.0f,  0.0f,  0.0f, 0.0f );
    }
}

static void gfx_whb_set_viewport(int x, int y, int width, int height) {
    GX2SetViewport(x, window_height - y - height, width, height, 0.0f, 1.0f);
    current_height = height;
}

static void gfx_whb_set_scissor(int x, int y, int width, int height) {
    GX2SetScissor(x, window_height - y - height, width, height);
}

static void gfx_whb_set_use_alpha(bool use_alpha) {
    if (use_alpha) {
        GX2SetBlendControl(GX2_RENDER_TARGET_0,
                           GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA,
                           GX2_BLEND_COMBINE_MODE_ADD, FALSE,
                           GX2_BLEND_MODE_ZERO, GX2_BLEND_MODE_ZERO,
                           GX2_BLEND_COMBINE_MODE_ADD);
        GX2SetColorControl(GX2_LOGIC_OP_COPY, 1, FALSE, TRUE);
    } else {
        GX2SetBlendControl(GX2_RENDER_TARGET_0,
                           GX2_BLEND_MODE_ONE, GX2_BLEND_MODE_ZERO,
                           GX2_BLEND_COMBINE_MODE_ADD, FALSE,
                           GX2_BLEND_MODE_ZERO, GX2_BLEND_MODE_ZERO,
                           GX2_BLEND_COMBINE_MODE_ADD);
        GX2SetColorControl(GX2_LOGIC_OP_COPY, 0, FALSE, TRUE);
    }
}

static void gfx_whb_draw_triangles(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {
    if (current_shader_program == NULL)
        return;

    uint32_t idx = vbo_array.size();
    vbo_array.resize(idx + 1);

    size_t vbo_len = sizeof(float) * buf_vbo_len;
    vbo_array[idx] = static_cast<float*>(memalign(0x40, vbo_len));

    float* new_vbo = vbo_array[idx];
    memcpy(new_vbo, buf_vbo, vbo_len);

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_ATTRIBUTE_BUFFER, new_vbo, vbo_len);

    GX2SetAttribBuffer(0, vbo_len, sizeof(float) * current_shader_program->num_floats, new_vbo);
    GX2DrawEx(GX2_PRIMITIVE_MODE_TRIANGLES, 3 * buf_vbo_num_tris, 0, 1);
}

static void gfx_whb_get_framebuffer(uint16_t *buffer) {
}

static void gfx_whb_init(void) {
}

static void gfx_whb_on_resize(void) {
}

static void gfx_whb_start_frame(void) {
    frame_count++;

    WHBGfxBeginRenderTV();
    WHBGfxClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

static void gfx_whb_end_frame(void) {
    GX2Flush();
    GX2DrawDone();
    WHBGfxFinishRenderTV();
    GX2CopyColorBufferToScanBuffer(WHBGfxGetTVColourBuffer(), GX2_SCAN_TARGET_DRC);
}

static void gfx_whb_finish_render(void) {
}

static void gfx_whb_shutdown(void) {
    WHBGfxShutdown();
}

extern "C" void whb_free_vbo(void) {
    for (uint32_t i = 0; i < vbo_array.size(); i++) {
        free(vbo_array[i]);
    }

    vbo_array.clear();
}

extern "C" void whb_free(void) {
    // Free our textures and shaders
    for (uint32_t i = 0; i < whb_textures.size(); i++) {
        Texture& texture = whb_textures[i];
        if (texture.textureUploaded) {
            free(texture.texture.surface.image);
        }
    }

    for (uint32_t i = 0; i < shader_program_pool_size; i++) {
        WHBGfxFreeShaderGroup(&shader_program_pool[i].group);
    }

    whb_textures.clear();
    shader_program_pool_size = 0;
}

struct GfxRenderingAPI gfx_whb_api = {
    gfx_whb_z_is_from_0_to_1,
    gfx_whb_unload_shader,
    gfx_whb_load_shader,
    gfx_whb_create_and_load_new_shader,
    gfx_whb_lookup_shader,
    gfx_whb_shader_get_info,
    gfx_whb_new_texture,
    gfx_whb_select_texture,
    gfx_whb_upload_texture,
    gfx_whb_set_sampler_parameters,
    gfx_whb_set_depth_test,
    gfx_whb_set_depth_mask,
    gfx_whb_set_zmode_decal,
    gfx_whb_set_viewport,
    gfx_whb_set_scissor,
    gfx_whb_set_use_alpha,
    gfx_whb_draw_triangles,
    gfx_whb_get_framebuffer,
    gfx_whb_init,
    gfx_whb_on_resize,
    gfx_whb_start_frame,
    gfx_whb_end_frame,
    gfx_whb_finish_render,
    gfx_whb_shutdown
};

#endif
