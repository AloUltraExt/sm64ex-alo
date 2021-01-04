#ifdef RAPI_GL

#include <stdint.h>
#include <stdbool.h>

#ifndef _LANGUAGE_C
# define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#ifdef __MINGW32__
# define FOR_WINDOWS 1
#else
# define FOR_WINDOWS 0
#endif

#if FOR_WINDOWS || defined(OSX_BUILD)
# define GLEW_STATIC
# include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1

#ifdef WAPI_SDL2
# include <SDL2/SDL.h>
# ifdef USE_GLES
#  include <SDL2/SDL_opengles2.h>
# else
#  include <SDL2/SDL_opengl.h>
# endif
#elif defined(WAPI_SDL1)
# include <SDL/SDL.h>
# ifndef GLEW_STATIC
#  include <SDL/SDL_opengl.h>
# endif
#endif

#include "../platform.h"
#include "../configfile.h"
#include "gfx_cc.h"
#include "gfx_rendering_api.h"
#include "gfx_screen_config.h"
#include "gfx_pc.h"

#define TEX_CACHE_STEP 512

struct ShaderProgram {
    uint32_t shader_id;
    GLuint opengl_program_id;
    uint8_t num_inputs;
    bool used_textures[2];
    uint8_t num_floats;
    GLint attrib_locations[7];
    GLint uniform_locations[5];
    uint8_t attrib_sizes[7];
    uint8_t num_attribs;
    bool used_noise;
};

struct GLTexture {
    GLuint gltex;
    GLfloat size[2];
    bool filter;
};

struct RenderTarget {
    GLuint framebuffer_id;
    GLuint color_texture_id;
    GLuint depth_renderbuffer_id;

    uint32_t width;
    uint32_t height;
};

static struct {
    int32_t viewport_x, viewport_y, viewport_width, viewport_height;
    int32_t scissor_x, scissor_y, scissor_width, scissor_height;
    int8_t depth_test, depth_mask;
    int8_t zmode_decal;

    uint8_t active_texture;
} gl_state = {0};

static struct RenderTarget main_rt;
static struct RenderTarget framebuffer_rt;

static struct ShaderProgram shader_program_pool[64];
static uint8_t shader_program_pool_size;

static struct ShaderProgram rt_shader_program;

static GLuint opengl_vbo;

static int tex_cache_size = 0;
static int num_textures = 0;
static struct GLTexture *tex_cache = NULL;

static struct ShaderProgram *opengl_prg = NULL;
static struct GLTexture *opengl_tex[2];
static int opengl_curtex = 0;

// Current values

static uint32_t current_width;
static uint32_t current_height;

static int8_t current_depth_test, current_depth_mask;
static int8_t current_zmode_decal;

static int32_t current_viewport_x, current_viewport_y, current_viewport_width, current_viewport_height;
static int32_t current_scissor_x, current_scissor_y, current_scissor_width, current_scissor_height;

static uint32_t frame_count;

static const char *rt_vertex_shader =
#ifdef USE_GLES
    "#version 100\n"
#else
    "#version 120\n"
#endif
    "attribute vec2 a_position;\n"
    "attribute vec2 a_uv;\n"
    "varying vec2 v_uv;\n"
    "void main() {\n"
    "    gl_Position = vec4(a_position.x, a_position.y, 0.0, 1.0);\n"
    "    v_uv = a_uv;\n"
    "}\n";

static const char *rt_fragment_shader =
#ifdef USE_GLES
    "#version 100\n"
    "precision mediump float;\n"
#else
    "#version 120\n"
#endif
    "varying vec2 v_uv;\n"
    "uniform sampler2D u_texture;"
    "void main() {\n"
    "    gl_FragColor = texture2D(u_texture, v_uv);\n"
    "}\n";

static void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height) {
    if (gl_state.viewport_x == x && gl_state.viewport_y == y && gl_state.viewport_width == width && gl_state.viewport_height == height) {
        return;
    }

    gl_state.viewport_x = x;
    gl_state.viewport_y = y;
    gl_state.viewport_width = width;
    gl_state.viewport_height = height;

    glViewport(x, y, width, height);
}

static void set_scissor(int32_t x, int32_t y, int32_t width, int32_t height) {
    if (gl_state.scissor_x == x && gl_state.scissor_y == y && gl_state.scissor_width == width && gl_state.scissor_height == height) {
        return;
    }

    gl_state.scissor_x = x;
    gl_state.scissor_y = y;
    gl_state.scissor_width = width;
    gl_state.scissor_height = height;

    glScissor(x, y, width, height);
}

static void set_depth_test(bool depth_test) {
    if (gl_state.depth_test == depth_test) {
        return;
    }

    gl_state.depth_test = depth_test;

    if (depth_test) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

static void set_depth_mask(bool depth_mask) {
    if (gl_state.depth_mask == depth_mask) {
        return;
    }

    gl_state.depth_mask = depth_mask;

    glDepthMask(depth_mask ? GL_TRUE : GL_FALSE);
}

static void set_zmode_decal(bool zmode_decal) {
    if (gl_state.zmode_decal == zmode_decal) {
        return;
    }

    gl_state.zmode_decal = zmode_decal;

    if (zmode_decal) {
        glPolygonOffset(-2, -2);
        glEnable(GL_POLYGON_OFFSET_FILL);
    } else {
        glPolygonOffset(0, 0);
        glDisable(GL_POLYGON_OFFSET_FILL);
    }
}

static void set_active_texture(uint8_t active_texture) {
    if (gl_state.active_texture == active_texture) {
        return;
    }

    gl_state.active_texture = active_texture;

    glActiveTexture(GL_TEXTURE0 + active_texture);
}

static void set_vertex_buffer(float buffer[], size_t buffer_length) {
    glBufferSubData(GL_ARRAY_BUFFER, 0, buffer_length, buffer);
}

static GLuint compile_shader(const char *vertex_shader, const char *fragment_shader) {
    GLint success;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint max_length = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &max_length);
        char error_log[1024];
        fprintf(stderr, "Vertex shader compilation failed\n");
        glGetShaderInfoLog(vs, max_length, &max_length, &error_log[0]);
        fprintf(stderr, "%s\n", &error_log[0]);
        sys_fatal("vertex shader compilation failed (see terminal)");
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint max_length = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &max_length);
        char error_log[1024];
        fprintf(stderr, "Fragment shader compilation failed\n");
        glGetShaderInfoLog(fs, max_length, &max_length, &error_log[0]);
        fprintf(stderr, "%s\n", &error_log[0]);
        sys_fatal("fragment shader compilation failed (see terminal)");
    }

    GLuint shader_program_id = glCreateProgram();
    glAttachShader(shader_program_id, vs);
    glAttachShader(shader_program_id, fs);
    glLinkProgram(shader_program_id);

    glDetachShader(shader_program_id, vs);
    glDetachShader(shader_program_id, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return shader_program_id;
}

static void gfx_opengl_vertex_array_set_attribs(struct ShaderProgram *prg) {
    size_t num_floats = prg->num_floats;
    size_t pos = 0;

    for (int i = 0; i < prg->num_attribs; i++) {
        glEnableVertexAttribArray(prg->attrib_locations[i]);
        glVertexAttribPointer(prg->attrib_locations[i], prg->attrib_sizes[i], GL_FLOAT, GL_FALSE, num_floats * sizeof(float), (void *) (pos * sizeof(float)));
        pos += prg->attrib_sizes[i];
    }
}

static inline void gfx_opengl_set_shader_uniforms(struct ShaderProgram *prg) {
    if (prg->used_noise)
        glUniform1f(prg->uniform_locations[4], (float)frame_count);
}

static inline void gfx_opengl_set_texture_uniforms(struct ShaderProgram *prg, const int tile) {
    if (prg->used_textures[tile] && opengl_tex[tile]) {
        glUniform2f(prg->uniform_locations[tile*2 + 0], opengl_tex[tile]->size[0], opengl_tex[tile]->size[1]);
        glUniform1i(prg->uniform_locations[tile*2 + 1], opengl_tex[tile]->filter);
    }
}

static void gfx_opengl_load_shader(struct ShaderProgram *new_prg) {
    opengl_prg = new_prg;
    glUseProgram(new_prg->opengl_program_id);
    gfx_opengl_vertex_array_set_attribs(new_prg);
    gfx_opengl_set_shader_uniforms(new_prg);
    gfx_opengl_set_texture_uniforms(new_prg, 0);
    gfx_opengl_set_texture_uniforms(new_prg, 1);
}

static void gfx_opengl_unload_shader(struct ShaderProgram *old_prg) {
    if (old_prg != NULL) {
        for (int i = 0; i < old_prg->num_attribs; i++)
            glDisableVertexAttribArray(old_prg->attrib_locations[i]);
        if (old_prg == opengl_prg)
            opengl_prg = NULL;
    } else {
        opengl_prg = NULL;
    }
}

static void create_render_target(uint32_t width, uint32_t height, bool is_resizing, bool has_depth_buffer, struct RenderTarget *render_target) {
    // Create color texture and buffers

    if (!is_resizing) {
        glGenTextures(1, &render_target->color_texture_id);
        if (has_depth_buffer) {
            glGenRenderbuffers(1, &render_target->depth_renderbuffer_id);
        }
        glGenFramebuffers(1, &render_target->framebuffer_id);
    }

    // Configure color texture

    glBindTexture(GL_TEXTURE_2D, render_target->color_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Configure the depth buffer

    if (has_depth_buffer) {
        glBindRenderbuffer(GL_RENDERBUFFER, render_target->depth_renderbuffer_id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    }

    // Bind color and depth to the framebuffer

    if (!is_resizing) {
        glBindFramebuffer(GL_FRAMEBUFFER, render_target->framebuffer_id);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_target->color_texture_id, 0);
        if (has_depth_buffer) {
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_target->depth_renderbuffer_id);
        }
    }

    render_target->width = width;
    render_target->height = height;
}

static void draw_render_target(const struct RenderTarget *dst_render_target, const struct RenderTarget *src_render_target, bool clear_before_drawing) {
    // Set render target

    uint32_t width, height;

    if (dst_render_target == NULL) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        width = current_width;
        height = current_height;
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, dst_render_target->framebuffer_id);
        width = dst_render_target->width;
        height = dst_render_target->height;
    }

    // Set some states and clear after that

    set_depth_test(false);
    set_depth_mask(false);
    set_zmode_decal(false);
    set_viewport(0, 0, width, height);
    set_scissor(0, 0, width, height);

    if (clear_before_drawing) {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Set color texture

    set_active_texture(0);
    glBindTexture(GL_TEXTURE_2D, src_render_target->color_texture_id);

    // Set vertex buffer data

    float rt_aspect = (float) width / (float) height;
    float current_aspect = (float) current_width / (float) current_height;
    float w = current_aspect / rt_aspect;

    float buf_vbo[] = {
        -w, +1.0, 0.0, 1.0,
        -w, -1.0, 0.0, 0.0,
        +w, +1.0, 1.0, 1.0,
        +w, -1.0, 1.0, 0.0
    };

    uint32_t stride = 2 * 2 * sizeof(float);
    set_vertex_buffer(buf_vbo, 4 * stride);

    // Draw the quad

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

static void create_render_target_views(bool is_resize) {
    if (!is_resize) {
        // Initialize the framebuffer only the first time
        create_render_target(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, false, false, &framebuffer_rt);
    }

    // Create the main render target where contents will be rendered

    create_render_target(current_width, current_height, is_resize, true, &main_rt);
}

static bool gfx_opengl_z_is_from_0_to_1(void) {
    return false;
}

static void append_str(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
}

static void append_line(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
    buf[(*len)++] = '\n';
}

static const char *shader_item_to_str(uint32_t item, bool with_alpha, bool only_alpha, bool inputs_have_alpha, bool hint_single_element) {
    if (!only_alpha) {
        switch (item) {
            case SHADER_0:
                return with_alpha ? "vec4(0.0, 0.0, 0.0, 0.0)" : "vec3(0.0, 0.0, 0.0)";
            case SHADER_INPUT_1:
                return with_alpha || !inputs_have_alpha ? "vInput1" : "vInput1.rgb";
            case SHADER_INPUT_2:
                return with_alpha || !inputs_have_alpha ? "vInput2" : "vInput2.rgb";
            case SHADER_INPUT_3:
                return with_alpha || !inputs_have_alpha ? "vInput3" : "vInput3.rgb";
            case SHADER_INPUT_4:
                return with_alpha || !inputs_have_alpha ? "vInput4" : "vInput4.rgb";
            case SHADER_TEXEL0:
                return with_alpha ? "texVal0" : "texVal0.rgb";
            case SHADER_TEXEL0A:
                return hint_single_element ? "texVal0.a" :
                    (with_alpha ? "vec4(texelVal0.a, texelVal0.a, texelVal0.a, texelVal0.a)" : "vec3(texelVal0.a, texelVal0.a, texelVal0.a)");
            case SHADER_TEXEL1:
                return with_alpha ? "texVal1" : "texVal1.rgb";
        }
    } else {
        switch (item) {
            case SHADER_0:
                return "0.0";
            case SHADER_INPUT_1:
                return "vInput1.a";
            case SHADER_INPUT_2:
                return "vInput2.a";
            case SHADER_INPUT_3:
                return "vInput3.a";
            case SHADER_INPUT_4:
                return "vInput4.a";
            case SHADER_TEXEL0:
                return "texVal0.a";
            case SHADER_TEXEL0A:
                return "texVal0.a";
            case SHADER_TEXEL1:
                return "texVal1.a";
        }
    }
}

static void append_formula(char *buf, size_t *len, uint8_t c[2][4], bool do_single, bool do_multiply, bool do_mix, bool with_alpha, bool only_alpha, bool opt_alpha) {
    if (do_single) {
        append_str(buf, len, shader_item_to_str(c[only_alpha][3], with_alpha, only_alpha, opt_alpha, false));
    } else if (do_multiply) {
        append_str(buf, len, shader_item_to_str(c[only_alpha][0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " * ");
        append_str(buf, len, shader_item_to_str(c[only_alpha][2], with_alpha, only_alpha, opt_alpha, true));
    } else if (do_mix) {
        append_str(buf, len, "mix(");
        append_str(buf, len, shader_item_to_str(c[only_alpha][1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(c[only_alpha][0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(c[only_alpha][2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, ")");
    } else {
        append_str(buf, len, "(");
        append_str(buf, len, shader_item_to_str(c[only_alpha][0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " - ");
        append_str(buf, len, shader_item_to_str(c[only_alpha][1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ") * ");
        append_str(buf, len, shader_item_to_str(c[only_alpha][2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, " + ");
        append_str(buf, len, shader_item_to_str(c[only_alpha][3], with_alpha, only_alpha, opt_alpha, false));
    }
}

static struct ShaderProgram *gfx_opengl_create_and_load_new_shader(uint32_t shader_id) {
    uint8_t c[2][4];
    for (int i = 0; i < 4; i++) {
        c[0][i] = (shader_id >> (i * 3)) & 7;
        c[1][i] = (shader_id >> (12 + i * 3)) & 7;
    }
    bool opt_alpha = (shader_id & SHADER_OPT_ALPHA) != 0;
    bool opt_fog = (shader_id & SHADER_OPT_FOG) != 0;
    bool opt_texture_edge = (shader_id & SHADER_OPT_TEXTURE_EDGE) != 0;
#ifdef USE_GLES
    bool opt_noise = false;
#else
    bool opt_noise = (shader_id & SHADER_OPT_NOISE) != 0;
#endif

    bool used_textures[2] = { 0, 0 };
    int num_inputs = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (c[i][j] >= SHADER_INPUT_1 && c[i][j] <= SHADER_INPUT_4) {
                if (c[i][j] > num_inputs) {
                    num_inputs = c[i][j];
                }
            }
            if (c[i][j] == SHADER_TEXEL0 || c[i][j] == SHADER_TEXEL0A) {
                used_textures[0] = true;
            }
            if (c[i][j] == SHADER_TEXEL1) {
                used_textures[1] = true;
            }
        }
    }
    bool do_single[2] = { c[0][2] == 0, c[1][2] == 0 };
    bool do_multiply[2] = { c[0][1] == 0 && c[0][3] == 0, c[1][1] == 0 && c[1][3] == 0 };
    bool do_mix[2] = { c[0][1] == c[0][3], c[1][1] == c[1][3] };
    bool color_alpha_same = (shader_id & 0xfff) == ((shader_id >> 12) & 0xfff);

    char vs_buf[1024];
    char fs_buf[2048];
    size_t vs_len = 0;
    size_t fs_len = 0;
    size_t num_floats = 4;

    // Vertex shader
#ifdef USE_GLES
    append_line(vs_buf, &vs_len, "#version 100");
#else
    append_line(vs_buf, &vs_len, "#version 120");
#endif
    append_line(vs_buf, &vs_len, "attribute vec4 aVtxPos;");
    if (used_textures[0] || used_textures[1]) {
        append_line(vs_buf, &vs_len, "attribute vec2 aTexCoord;");
        append_line(vs_buf, &vs_len, "varying vec2 vTexCoord;");
        num_floats += 2;
    }
    if (opt_fog) {
        append_line(vs_buf, &vs_len, "attribute vec4 aFog;");
        append_line(vs_buf, &vs_len, "varying vec4 vFog;");
        num_floats += 4;
    }
    for (int i = 0; i < num_inputs; i++) {
        vs_len += sprintf(vs_buf + vs_len, "attribute vec%d aInput%d;\n", opt_alpha ? 4 : 3, i + 1);
        vs_len += sprintf(vs_buf + vs_len, "varying vec%d vInput%d;\n", opt_alpha ? 4 : 3, i + 1);
        num_floats += opt_alpha ? 4 : 3;
    }
    append_line(vs_buf, &vs_len, "void main() {");
    if (used_textures[0] || used_textures[1]) {
        append_line(vs_buf, &vs_len, "vTexCoord = aTexCoord;");
    }
    if (opt_fog) {
        append_line(vs_buf, &vs_len, "vFog = aFog;");
    }
    for (int i = 0; i < num_inputs; i++) {
        vs_len += sprintf(vs_buf + vs_len, "vInput%d = aInput%d;\n", i + 1, i + 1);
    }
    append_line(vs_buf, &vs_len, "gl_Position = aVtxPos;");
    append_line(vs_buf, &vs_len, "}");

    // Fragment shader
#ifdef USE_GLES
    append_line(fs_buf, &fs_len, "#version 100");
    append_line(fs_buf, &fs_len, "precision mediump float;");
#else
    append_line(fs_buf, &fs_len, "#version 120");
#endif

    if (used_textures[0] || used_textures[1]) {
        append_line(fs_buf, &fs_len, "varying vec2 vTexCoord;");
    }
    if (opt_fog) {
        append_line(fs_buf, &fs_len, "varying vec4 vFog;");
    }
    for (int i = 0; i < num_inputs; i++) {
        fs_len += sprintf(fs_buf + fs_len, "varying vec%d vInput%d;\n", opt_alpha ? 4 : 3, i + 1);
    }
    if (used_textures[0]) {
        append_line(fs_buf, &fs_len, "uniform sampler2D uTex0;");
        append_line(fs_buf, &fs_len, "uniform vec2 uTex0Size;");
        append_line(fs_buf, &fs_len, "uniform bool uTex0Filter;");
    }
    if (used_textures[1]) {
        append_line(fs_buf, &fs_len, "uniform sampler2D uTex1;");
        append_line(fs_buf, &fs_len, "uniform vec2 uTex1Size;");
        append_line(fs_buf, &fs_len, "uniform bool uTex1Filter;");
    }

    // 3 point texture filtering
    // Original author: ArthurCarvalho
    // Slightly modified GLSL implementation by twinaphex, mupen64plus-libretro project.

    if (used_textures[0] || used_textures[1]) {
        if (configFiltering == 2) {
            append_line(fs_buf, &fs_len, "#define TEX_OFFSET(off) texture2D(tex, texCoord - (off)/texSize)");
            append_line(fs_buf, &fs_len, "vec4 filter3point(in sampler2D tex, in vec2 texCoord, in vec2 texSize) {");
            append_line(fs_buf, &fs_len, "  vec2 offset = fract(texCoord*texSize - vec2(0.5));");
            append_line(fs_buf, &fs_len, "  offset -= step(1.0, offset.x + offset.y);");
            append_line(fs_buf, &fs_len, "  vec4 c0 = TEX_OFFSET(offset);");
            append_line(fs_buf, &fs_len, "  vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));");
            append_line(fs_buf, &fs_len, "  vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));");
            append_line(fs_buf, &fs_len, "  return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);");
            append_line(fs_buf, &fs_len, "}");
            append_line(fs_buf, &fs_len, "vec4 sampleTex(in sampler2D tex, in vec2 uv, in vec2 texSize, in bool dofilter) {");
            append_line(fs_buf, &fs_len, "if (dofilter)");
            append_line(fs_buf, &fs_len, "return filter3point(tex, uv, texSize);");
            append_line(fs_buf, &fs_len, "else");
            append_line(fs_buf, &fs_len, "return texture2D(tex, uv);");
            append_line(fs_buf, &fs_len, "}");
        } else {
            append_line(fs_buf, &fs_len, "vec4 sampleTex(in sampler2D tex, in vec2 uv, in vec2 texSize, in bool dofilter) {");
            append_line(fs_buf, &fs_len, "return texture2D(tex, uv);");
            append_line(fs_buf, &fs_len, "}");
        }
    }

    if (opt_alpha && opt_noise) {
        append_line(fs_buf, &fs_len, "uniform float frame_count;");

        append_line(fs_buf, &fs_len, "float random(in vec3 value) {");
        append_line(fs_buf, &fs_len, "    float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));");
        append_line(fs_buf, &fs_len, "    return fract(sin(random) * 143758.5453);");
        append_line(fs_buf, &fs_len, "}");
    }

    append_line(fs_buf, &fs_len, "void main() {");

    if (used_textures[0]) {
        append_line(fs_buf, &fs_len, "vec4 texVal0 = sampleTex(uTex0, vTexCoord, uTex0Size, uTex0Filter);");
    }
    if (used_textures[1]) {
        append_line(fs_buf, &fs_len, "vec4 texVal1 = sampleTex(uTex1, vTexCoord, uTex1Size, uTex1Filter);");
    }

    append_str(fs_buf, &fs_len, opt_alpha ? "vec4 texel = " : "vec3 texel = ");
    if (!color_alpha_same && opt_alpha) {
        append_str(fs_buf, &fs_len, "vec4(");
        append_formula(fs_buf, &fs_len, c, do_single[0], do_multiply[0], do_mix[0], false, false, true);
        append_str(fs_buf, &fs_len, ", ");
        append_formula(fs_buf, &fs_len, c, do_single[1], do_multiply[1], do_mix[1], true, true, true);
        append_str(fs_buf, &fs_len, ")");
    } else {
        append_formula(fs_buf, &fs_len, c, do_single[0], do_multiply[0], do_mix[0], opt_alpha, false, opt_alpha);
    }
    append_line(fs_buf, &fs_len, ";");

    if (opt_texture_edge && opt_alpha) {
        append_line(fs_buf, &fs_len, "if (texel.a > 0.3) texel.a = 1.0; else discard;");
    }
    // TODO discard if alpha is 0?
    if (opt_fog) {
        if (opt_alpha) {
            append_line(fs_buf, &fs_len, "texel = vec4(mix(texel.rgb, vFog.rgb, vFog.a), texel.a);");
        } else {
            append_line(fs_buf, &fs_len, "texel = mix(texel, vFog.rgb, vFog.a);");
        }
    }

    if (opt_alpha && opt_noise) 
        append_line(fs_buf, &fs_len, "texel.a *= floor(clamp(random(floor(vec3(gl_FragCoord.xy, frame_count))) + texel.a, 0.0, 1.0));");

    if (opt_alpha) {
        append_line(fs_buf, &fs_len, "gl_FragColor = texel;");
    } else {
        append_line(fs_buf, &fs_len, "gl_FragColor = vec4(texel, 1.0);");
    }
    append_line(fs_buf, &fs_len, "}");

    vs_buf[vs_len] = '\0';
    fs_buf[fs_len] = '\0';

    /*puts("Vertex shader:");
    puts(vs_buf);
    puts("Fragment shader:");
    puts(fs_buf);
    puts("End");*/

    GLuint shader_program = compile_shader(vs_buf, fs_buf);
    
    struct ShaderProgram *prg = &shader_program_pool[shader_program_pool_size++];
    prg->opengl_program_id = shader_program;

    size_t cnt = 0;

    prg->attrib_locations[cnt] = glGetAttribLocation(shader_program, "aVtxPos");
    prg->attrib_sizes[cnt] = 4;
    ++cnt;

    if (used_textures[0] || used_textures[1]) {
        prg->attrib_locations[cnt] = glGetAttribLocation(shader_program, "aTexCoord");
        prg->attrib_sizes[cnt] = 2;
        ++cnt;
    }

    if (opt_fog) {
        prg->attrib_locations[cnt] = glGetAttribLocation(shader_program, "aFog");
        prg->attrib_sizes[cnt] = 4;
        ++cnt;
    }

    for (int i = 0; i < num_inputs; i++) {
        char name[16];
        sprintf(name, "aInput%d", i + 1);
        prg->attrib_locations[cnt] = glGetAttribLocation(shader_program, name);
        prg->attrib_sizes[cnt] = opt_alpha ? 4 : 3;
        ++cnt;
    }

    prg->shader_id = shader_id;
    prg->opengl_program_id = shader_program;
    prg->num_inputs = num_inputs;
    prg->used_textures[0] = used_textures[0];
    prg->used_textures[1] = used_textures[1];
    prg->num_floats = num_floats;
    prg->num_attribs = cnt;

    gfx_opengl_load_shader(prg);

    if (used_textures[0]) {
        GLint sampler_location = glGetUniformLocation(shader_program, "uTex0");
        prg->uniform_locations[0] = glGetUniformLocation(shader_program, "uTex0Size");
        prg->uniform_locations[1] = glGetUniformLocation(shader_program, "uTex0Filter");
        glUniform1i(sampler_location, 0);
    }
    if (used_textures[1]) {
        GLint sampler_location = glGetUniformLocation(shader_program, "uTex1");
        prg->uniform_locations[2] = glGetUniformLocation(shader_program, "uTex1Size");
        prg->uniform_locations[3] = glGetUniformLocation(shader_program, "uTex1Filter");
        glUniform1i(sampler_location, 1);
    }

    if (opt_alpha && opt_noise) {
        prg->uniform_locations[4] = glGetUniformLocation(shader_program, "frame_count");
        prg->used_noise = true;
    } else {
        prg->used_noise = false;
    }

    return prg;
}

static struct ShaderProgram *gfx_opengl_lookup_shader(uint32_t shader_id) {
    for (size_t i = 0; i < shader_program_pool_size; i++) {
        if (shader_program_pool[i].shader_id == shader_id) {
            return &shader_program_pool[i];
        }
    }
    return NULL;
}

static void gfx_opengl_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    *num_inputs = prg->num_inputs;
    used_textures[0] = prg->used_textures[0];
    used_textures[1] = prg->used_textures[1];
}

static GLuint gfx_opengl_new_texture(void) {
    if (num_textures >= tex_cache_size) {
        tex_cache_size += TEX_CACHE_STEP;
        tex_cache = realloc(tex_cache, sizeof(struct GLTexture) * tex_cache_size);
        if (!tex_cache) sys_fatal("out of memory allocating texture cache");
        // invalidate these because they might be pointing to garbage now
        opengl_tex[0] = NULL;
        opengl_tex[1] = NULL;
    }
    glGenTextures(1, &tex_cache[num_textures].gltex);
    return num_textures++;
}

static void gfx_opengl_select_texture(int tile, GLuint texture_id) {
     opengl_tex[tile] = tex_cache + texture_id;
     opengl_curtex = tile;
     set_active_texture(tile);
     glBindTexture(GL_TEXTURE_2D, opengl_tex[tile]->gltex);
     gfx_opengl_set_texture_uniforms(opengl_prg, tile);
}

static void gfx_opengl_upload_texture(const uint8_t *rgba32_buf, int width, int height) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba32_buf);
    opengl_tex[opengl_curtex]->size[0] = width;
    opengl_tex[opengl_curtex]->size[1] = height;
}

static uint32_t gfx_cm_to_opengl(uint32_t val) {
    if (val & G_TX_CLAMP) {
        return GL_CLAMP_TO_EDGE;
    }
    return (val & G_TX_MIRROR) ? GL_MIRRORED_REPEAT : GL_REPEAT;
}

static void gfx_opengl_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt) {
    const GLenum filter = linear_filter ? GL_LINEAR : GL_NEAREST;
    set_active_texture(tile);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gfx_cm_to_opengl(cms));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gfx_cm_to_opengl(cmt));
    opengl_curtex = tile;
    if (opengl_tex[tile]) {
        opengl_tex[tile]->filter = linear_filter;
        gfx_opengl_set_texture_uniforms(opengl_prg, tile);
    }
}

static void gfx_opengl_set_depth_test(bool depth_test) {
    current_depth_test = depth_test;
}

static void gfx_opengl_set_depth_mask(bool z_upd) {
    current_depth_mask = z_upd;
}

static void gfx_opengl_set_zmode_decal(bool zmode_decal) {
    current_zmode_decal = zmode_decal;
}

static void gfx_opengl_set_viewport(int x, int y, int width, int height) {
    current_viewport_x = x;
    current_viewport_y = y;
    current_viewport_width = width;
    current_viewport_height = height;
}

static void gfx_opengl_set_scissor(int x, int y, int width, int height) {
    current_scissor_x = x;
    current_scissor_y = y;
    current_scissor_width = width;
    current_scissor_height = height;
}

static void gfx_opengl_set_use_alpha(bool use_alpha) {
    if (use_alpha) {
        glEnable(GL_BLEND);
    } else {
        glDisable(GL_BLEND);
    }
}

static void gfx_opengl_draw_triangles(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {
    // Depth

    set_depth_test(current_depth_test);
    set_depth_mask(current_depth_mask);
    set_zmode_decal(current_zmode_decal);

    // Viewport and Scissor

    set_viewport(current_viewport_x, current_viewport_y, current_viewport_width, current_viewport_height);
    set_scissor(current_scissor_x, current_scissor_y, current_scissor_width, current_scissor_height);

    // Draw vertex buffer

    set_vertex_buffer(buf_vbo, buf_vbo_len * sizeof(float));

    glDrawArrays(GL_TRIANGLES, 0, 3 * buf_vbo_num_tris);
}

static inline bool gl_get_version(int *major, int *minor, bool *is_es) {
    const char *vstr = (const char *)glGetString(GL_VERSION);
    if (!vstr || !vstr[0]) return false;

    if (!strncmp(vstr, "OpenGL ES ", 10)) {
        vstr += 10;
        *is_es = true;
    } else if (!strncmp(vstr, "OpenGL ES-CM ", 13)) {
        vstr += 13;
        *is_es = true;
    }

    return (sscanf(vstr, "%d.%d", major, minor) == 2);
}

static void gfx_opengl_get_framebuffer(uint16_t *buffer) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_rt.framebuffer_id);
    glReadBuffer(GL_COLOR_ATTACHMENT0);

    uint8_t pixels[FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT * 3];
    glReadPixels(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    uint32_t bi = 0;
    for (int32_t y = FRAMEBUFFER_HEIGHT - 1; y >= 0; y--) {
        for (int32_t x = 0; x < FRAMEBUFFER_WIDTH; x++) {
            uint32_t fb_pixel = (y * FRAMEBUFFER_WIDTH + x) * 3;

            uint8_t r = pixels[fb_pixel + 0] >> 3;
            uint8_t g = pixels[fb_pixel + 1] >> 3;
            uint8_t b = pixels[fb_pixel + 2] >> 3;
            uint8_t a = 1; //pixels[fb_pixel + 3] / 255;

            buffer[bi] = (r << 11) | (g << 6) | (b << 1) | a;
            bi++;
        }
    }
}

static void gfx_opengl_init(void) {
#if FOR_WINDOWS || defined(OSX_BUILD)
    GLenum err;
    if ((err = glewInit()) != GLEW_OK)
        sys_fatal("could not init GLEW:\n%s", glewGetErrorString(err));
#endif

    tex_cache_size = TEX_CACHE_STEP;
    tex_cache = calloc(tex_cache_size, sizeof(struct GLTexture));
    if (!tex_cache) sys_fatal("out of memory allocating texture cache");

    // check GL version
    int vmajor, vminor;
    bool is_es = false;
    gl_get_version(&vmajor, &vminor, &is_es);
    if (vmajor < 2 && vminor < 1 && !is_es)
        sys_fatal("OpenGL 2.1+ is required.\nReported version: %s%d.%d", is_es ? "ES" : "", vmajor, vminor);

    // Initialize render targets

    current_width = gfx_current_dimensions.width;
    current_height = gfx_current_dimensions.height;

    create_render_target_views(false);

    // Create the render target shader, used to draw into fullscreen quads

    rt_shader_program.opengl_program_id = compile_shader(rt_vertex_shader, rt_fragment_shader);
    rt_shader_program.attrib_locations[0] = glGetAttribLocation(rt_shader_program.opengl_program_id, "a_position");
    rt_shader_program.attrib_sizes[0] = 2;
    rt_shader_program.attrib_locations[1] = glGetAttribLocation(rt_shader_program.opengl_program_id, "a_uv");
    rt_shader_program.attrib_sizes[1] = 2;
    rt_shader_program.num_attribs = 2;
    rt_shader_program.num_floats = 4;
    rt_shader_program.used_textures[0] = true;
    rt_shader_program.used_textures[1] = false;
    rt_shader_program.num_inputs = 0;     // Unused in this case
    rt_shader_program.shader_id = 0;      // Unused in this case
    rt_shader_program.used_noise = false; // Unused in this case

    glUseProgram(rt_shader_program.opengl_program_id);
    GLint sampler_location = glGetUniformLocation(rt_shader_program.opengl_program_id, "u_texture");
    glUniform1i(sampler_location, 0);

    // Initialize vertex buffer

    glGenBuffers(1, &opengl_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, opengl_vbo);
    glBufferData(GL_ARRAY_BUFFER, VERTEX_BUFFER_SIZE * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    // Initialize misc states

    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

static void gfx_opengl_on_resize(void) {
}

static void gfx_opengl_start_frame(void) {
    frame_count++;

    if (current_width != gfx_current_dimensions.width || current_height != gfx_current_dimensions.height) {
        current_width = gfx_current_dimensions.width;
        current_height = gfx_current_dimensions.height;
        create_render_target_views(true);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, main_rt.framebuffer_id);

    glDisable(GL_SCISSOR_TEST);
    set_depth_mask(true); // Must be set to clear Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);
}

static void gfx_opengl_end_frame(void) {
    // Set the shader and vertex attribs for quad rendering

    glUseProgram(rt_shader_program.opengl_program_id);
    gfx_opengl_vertex_array_set_attribs(&rt_shader_program);

    // Draw quad with main render target into the other render targets

    draw_render_target(NULL, &main_rt, false);
    draw_render_target(&framebuffer_rt, &main_rt, true);

    // Set again the last shader used before drawing render targets.
    // Not doing so can lead to rendering issues on the first drawcalls
    // of the next frame, if they use the same shader as the ones before.

    gfx_opengl_load_shader(opengl_prg);
}

static void gfx_opengl_finish_render(void) {
}

static void gfx_opengl_shutdown(void) {
}

struct GfxRenderingAPI gfx_opengl_api = {
    gfx_opengl_z_is_from_0_to_1,
    gfx_opengl_unload_shader,
    gfx_opengl_load_shader,
    gfx_opengl_create_and_load_new_shader,
    gfx_opengl_lookup_shader,
    gfx_opengl_shader_get_info,
    gfx_opengl_new_texture,
    gfx_opengl_select_texture,
    gfx_opengl_upload_texture,
    gfx_opengl_set_sampler_parameters,
    gfx_opengl_set_depth_test,
    gfx_opengl_set_depth_mask,
    gfx_opengl_set_zmode_decal,
    gfx_opengl_set_viewport,
    gfx_opengl_set_scissor,
    gfx_opengl_set_use_alpha,
    gfx_opengl_draw_triangles,
    gfx_opengl_get_framebuffer,
    gfx_opengl_init,
    gfx_opengl_on_resize,
    gfx_opengl_start_frame,
    gfx_opengl_end_frame,
    gfx_opengl_finish_render,
    gfx_opengl_shutdown
};

#endif // RAPI_GL
