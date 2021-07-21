#ifdef RAPI_D3D11

#include <cstdio>
#include <vector>
#include <cmath>

#include <windows.h>
#include <versionhelpers.h>
#include <wrl/client.h>

#include <dxgi1_3.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#ifndef _LANGUAGE_C
#define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#include "gfx_cc.h"
#include "gfx_window_manager_api.h"
#include "gfx_rendering_api.h"
#include "gfx_direct3d_common.h"

#define DECLARE_GFX_DXGI_FUNCTIONS
#include "gfx_dxgi.h"

#include "gfx_screen_config.h"
#include "gfx_pc.h"

#define DEBUG_D3D 0

using namespace Microsoft::WRL; // For ComPtr

namespace {

struct PerFrameCB {
    uint32_t noise_frame;
    float noise_scale_x;
    float noise_scale_y;
    uint32_t padding;
};

struct PerDrawCB {
    struct Texture {
        uint32_t width;
        uint32_t height;
        uint32_t linear_filtering;
        uint32_t padding;
    } textures[2];
};

struct TextureData {
    ComPtr<ID3D11ShaderResourceView> resource_view;
    ComPtr<ID3D11SamplerState> sampler_state;
    uint32_t width;
    uint32_t height;
    bool linear_filtering;
};

struct ShaderProgramD3D11 {
    ComPtr<ID3D11VertexShader> vertex_shader;
    ComPtr<ID3D11PixelShader> pixel_shader;
    ComPtr<ID3D11InputLayout> input_layout;
    ComPtr<ID3D11BlendState> blend_state;

    uint32_t shader_id;
    uint8_t num_inputs;
    uint8_t num_floats;
    bool used_textures[2];
};

struct RenderTarget {
    ComPtr<ID3D11Texture2D> texture;
    ComPtr<ID3D11RenderTargetView> render_target_view;
    ComPtr<ID3D11DepthStencilView> depth_stencil_view;
    TextureData texture_data;
    ComPtr<ID3D11Texture2D> cpu_readable_texture_copy;
};

struct PipelineState {
    int32_t viewport_x, viewport_y, viewport_width, viewport_height;
    int32_t scissor_x, scissor_y, scissor_width, scissor_height;
    int8_t depth_test, depth_mask;
    int8_t zmode_decal;

    D3D_PRIMITIVE_TOPOLOGY primitive_topology;

    struct ShaderProgramD3D11 *shader_program;
    ComPtr<ID3D11BlendState> blend_state;

    ComPtr<ID3D11ShaderResourceView> resource_views[2];
    ComPtr<ID3D11SamplerState> sampler_states[2];

    uint32_t vertex_buffer_stride = 0;
};

static struct {
    HMODULE d3d11_module;
    PFN_D3D11_CREATE_DEVICE D3D11CreateDevice;
    
    HMODULE d3dcompiler_module;
    pD3DCompile D3DCompile;
    
    D3D_FEATURE_LEVEL feature_level;
    
    ComPtr<ID3D11Device> device;
    ComPtr<IDXGISwapChain1> swap_chain;
    ComPtr<ID3D11DeviceContext> context;
    ComPtr<ID3D11RasterizerState> rasterizer_state;
    ComPtr<ID3D11DepthStencilState> depth_stencil_state;
    ComPtr<ID3D11Buffer> vertex_buffer;
    ComPtr<ID3D11Buffer> per_frame_cb;
    ComPtr<ID3D11Buffer> per_draw_cb;

    RenderTarget backbuffer_rt;
    RenderTarget main_rt;
    RenderTarget framebuffer_rt;

    struct ShaderProgramD3D11 rt_shader_program;

#if DEBUG_D3D
    ComPtr<ID3D11Debug> debug;
#endif

    DXGI_SAMPLE_DESC sample_description;

    PerFrameCB per_frame_cb_data;
    PerDrawCB per_draw_cb_data;

    struct ShaderProgramD3D11 shader_program_pool[64];
    uint8_t shader_program_pool_size;

    std::vector<struct TextureData> textures;

    bool framebuffer_requested;
    uint16_t *framebuffer_data;

    // Current values

    int current_tile;
    uint32_t current_texture_ids[2];

    struct ShaderProgramD3D11 *current_shader_program;

    uint32_t current_width, current_height;

    int8_t current_depth_test, current_depth_mask;
    int8_t current_zmode_decal;

    int32_t current_viewport_x, current_viewport_y, current_viewport_width, current_viewport_height;
    int32_t current_scissor_x, current_scissor_y, current_scissor_width, current_scissor_height;

    // State of the D3D pipeline (to prevent setting states needlessly)

    struct PipelineState state;

} d3d;

static const char rt_shader[1024] =
    "struct PSInput {\n"
    "    float4 position : SV_POSITION;\n"
    "    float2 uv : TEXCOORD;\n"
    "};\n"
    "Texture2D texture0 : register(t0);\n"
    "SamplerState sampler0 : register(s0);\n"
    "PSInput VSMain(float2 position : POSITION, float2 uv : TEXCOORD) {\n"
    "    PSInput result;\n"
    "    result.position = float4(position, 0, 1);\n"
    "    result.uv = uv;\n"
    "    return result;\n"
    "}\n"
    "float4 PSMain(PSInput input) : SV_TARGET {\n"
    "    return float4(texture0.Sample(sampler0, input.uv).rgb, 1);\n"
    "}\n";

static LARGE_INTEGER last_time, accumulated_time, frequency;

static ComPtr<ID3DBlob> compile_shader(const char *vertex_shader, size_t vertex_shader_length, const char *fragment_shader, size_t fragment_shader_length, ShaderProgramD3D11 *shader_program) {
    ComPtr<ID3DBlob> vs, ps, error_blob;

#if DEBUG_D3D
    UINT compile_flags = D3DCOMPILE_DEBUG;
#else
    UINT compile_flags = D3DCOMPILE_OPTIMIZATION_LEVEL2;
#endif

    HRESULT hr = d3d.D3DCompile(vertex_shader, vertex_shader_length, nullptr, nullptr, nullptr, "VSMain", "vs_4_0_level_9_1", compile_flags, 0, vs.GetAddressOf(), error_blob.GetAddressOf());

    if (FAILED(hr)) {
        char *message = (char *) error_blob->GetBufferPointer();
        MessageBox(gfx_dxgi_get_h_wnd(), message, "Error", MB_OK | MB_ICONERROR);
        throw hr;
    }

    hr = d3d.D3DCompile(fragment_shader, fragment_shader_length, nullptr, nullptr, nullptr, "PSMain", "ps_4_0_level_9_1", compile_flags, 0, ps.GetAddressOf(), error_blob.GetAddressOf());

    if (FAILED(hr)) {
        char *message = (char *) error_blob->GetBufferPointer();
        MessageBox(gfx_dxgi_get_h_wnd(), message, "Error", MB_OK | MB_ICONERROR);
        throw hr;
    }

    ThrowIfFailed(d3d.device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, shader_program->vertex_shader.GetAddressOf()));
    ThrowIfFailed(d3d.device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, shader_program->pixel_shader.GetAddressOf()));

    return vs;
}

static void set_vertex_buffer(float buffer[], size_t buffer_length, uint32_t stride) {
    D3D11_MAPPED_SUBRESOURCE ms;
    ZeroMemory(&ms, sizeof(D3D11_MAPPED_SUBRESOURCE));

    d3d.context->Map(d3d.vertex_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    memcpy(ms.pData, buffer, buffer_length);
    d3d.context->Unmap(d3d.vertex_buffer.Get(), 0);

    if (d3d.state.vertex_buffer_stride == stride) {
        return;
    }

    d3d.state.vertex_buffer_stride = stride;

    uint32_t offset = 0;
    d3d.context->IASetVertexBuffers(0, 1, d3d.vertex_buffer.GetAddressOf(), &stride, &offset);
}

static void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height) {
    if (d3d.state.viewport_x == x && d3d.state.viewport_y == y && d3d.state.viewport_width == width && d3d.state.viewport_height == height) {
        return;
    }

    d3d.state.viewport_x = x;
    d3d.state.viewport_y = y;
    d3d.state.viewport_width = width;
    d3d.state.viewport_height = height;

    D3D11_VIEWPORT viewport;
    viewport.TopLeftX = x;
    viewport.TopLeftY = y;
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    d3d.context->RSSetViewports(1, &viewport);
}

static void set_scissor(int32_t x, int32_t y, int32_t width, int32_t height) {
    if (d3d.state.scissor_x == x && d3d.state.scissor_y == y && d3d.state.scissor_width == width && d3d.state.scissor_height == height) {
        return;
    }

    d3d.state.scissor_x = x;
    d3d.state.scissor_y = y;
    d3d.state.scissor_width = width;
    d3d.state.scissor_height = height;

    D3D11_RECT rect;
    rect.left = x;
    rect.top = y;
    rect.right = width;
    rect.bottom = height;

    d3d.context->RSSetScissorRects(1, &rect);
}

static void set_depth_stencil_state(int8_t depth_test, int8_t depth_mask) {
    if (d3d.state.depth_test == depth_test && d3d.state.depth_mask == depth_mask) {
        return;
    }

    d3d.state.depth_test = depth_test;
    d3d.state.depth_mask = depth_mask;

    d3d.depth_stencil_state.Reset();

    D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
    ZeroMemory(&depth_stencil_desc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depth_stencil_desc.DepthEnable = depth_test;
    depth_stencil_desc.DepthWriteMask = depth_mask ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
    depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    depth_stencil_desc.StencilEnable = false;

    ThrowIfFailed(d3d.device->CreateDepthStencilState(&depth_stencil_desc, d3d.depth_stencil_state.GetAddressOf()),
                  gfx_dxgi_get_h_wnd(), "Failed to create depth stencil state.");

    d3d.context->OMSetDepthStencilState(d3d.depth_stencil_state.Get(), 0);
}

static void set_rasterizer_state(int8_t zmode_decal) {
    if (d3d.state.zmode_decal == zmode_decal) {
        return;
    }

    d3d.state.zmode_decal = zmode_decal;

    d3d.rasterizer_state.Reset();

    D3D11_RASTERIZER_DESC rasterizer_desc;
    ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

    rasterizer_desc.FillMode = D3D11_FILL_SOLID;
    rasterizer_desc.CullMode = D3D11_CULL_NONE;
    rasterizer_desc.FrontCounterClockwise = true;
    rasterizer_desc.DepthBias = 0;
    rasterizer_desc.SlopeScaledDepthBias = zmode_decal ? -2.0f : 0.0f;
    rasterizer_desc.DepthBiasClamp = 0.0f;
    rasterizer_desc.DepthClipEnable = true;
    rasterizer_desc.ScissorEnable = true;
    rasterizer_desc.MultisampleEnable = false;
    rasterizer_desc.AntialiasedLineEnable = false;

    ThrowIfFailed(d3d.device->CreateRasterizerState(&rasterizer_desc, d3d.rasterizer_state.GetAddressOf()),
                  gfx_dxgi_get_h_wnd(), "Failed to create rasterizer state.");

    d3d.context->RSSetState(d3d.rasterizer_state.Get());
}

static void set_shader(ShaderProgramD3D11 *shader_program) {
    if (d3d.state.shader_program == shader_program) {
        return;
    }

    d3d.state.shader_program = shader_program;

    d3d.context->IASetInputLayout(shader_program->input_layout.Get());
    d3d.context->VSSetShader(shader_program->vertex_shader.Get(), 0, 0);
    d3d.context->PSSetShader(shader_program->pixel_shader.Get(), 0, 0);

    if (d3d.state.blend_state.Get() != shader_program->blend_state.Get()) {
        d3d.state.blend_state = shader_program->blend_state.Get();
        d3d.context->OMSetBlendState(shader_program->blend_state.Get(), 0, 0xFFFFFFFF);
    }
}

static void set_primitive_topology(D3D_PRIMITIVE_TOPOLOGY primitive_topology) {
    if (d3d.state.primitive_topology == primitive_topology) {
        return;
    }

    d3d.state.primitive_topology = primitive_topology;

    d3d.context->IASetPrimitiveTopology(primitive_topology);
}

static void set_shader_resources(uint8_t slot, const TextureData *texture) {
    if (texture == nullptr) {
        d3d.state.resource_views[slot] = nullptr;
        ID3D11ShaderResourceView *null_srv[1] = { nullptr };
        d3d.context->PSSetShaderResources(slot, 1, null_srv);
        return;
    }

    if (d3d.state.resource_views[slot].Get() == texture->resource_view.Get()) {
        return;
    }

    d3d.state.resource_views[slot] = texture->resource_view.Get();

    d3d.context->PSSetShaderResources(slot, 1, texture->resource_view.GetAddressOf());

#ifdef THREE_POINT_FILTERING
    d3d.per_draw_cb_data.textures[slot].width = texture->width;
    d3d.per_draw_cb_data.textures[slot].height = texture->height;
    d3d.per_draw_cb_data.textures[slot].linear_filtering = texture->linear_filtering;
#endif

    if (d3d.state.sampler_states[slot].Get() != texture->sampler_state.Get()) {
        d3d.state.sampler_states[slot] = texture->sampler_state.Get();
        d3d.context->PSSetSamplers(slot, 1, texture->sampler_state.GetAddressOf());
    }
}

static void create_render_target(uint32_t width, uint32_t height, bool has_depth_buffer, bool is_shader_resource, bool create_cpu_readable_copy, RenderTarget *render_target) {
    uint32_t bind_flags = D3D11_BIND_RENDER_TARGET;
    if (is_shader_resource)
        bind_flags |= D3D11_BIND_SHADER_RESOURCE;

    // Create the texture

    D3D11_TEXTURE2D_DESC texture_desc;
    ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));

    texture_desc.Width = width;
    texture_desc.Height = height;
    texture_desc.MipLevels = 1;
    texture_desc.ArraySize = 1;
    texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texture_desc.SampleDesc = d3d.sample_description;
    texture_desc.Usage = D3D11_USAGE_DEFAULT;
    texture_desc.BindFlags = bind_flags;
    texture_desc.CPUAccessFlags = 0;
    texture_desc.MiscFlags = 0;

    ThrowIfFailed(d3d.device->CreateTexture2D(&texture_desc, nullptr, render_target->texture.GetAddressOf()));

    render_target->texture_data.width = width;
    render_target->texture_data.height = height;
    render_target->texture_data.linear_filtering = true;

    // Create the render target

    D3D11_RENDER_TARGET_VIEW_DESC rtv_desc;
    ZeroMemory(&rtv_desc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));

    rtv_desc.Format = texture_desc.Format;
    rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    rtv_desc.Texture2D.MipSlice = 0;

    ThrowIfFailed(d3d.device->CreateRenderTargetView(render_target->texture.Get(), &rtv_desc, render_target->render_target_view.GetAddressOf()));

    // Create the shader resource view and sampler from the texture

    if (is_shader_resource) {
        D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
        ZeroMemory(&srv_desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

        srv_desc.Format = texture_desc.Format;
        srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srv_desc.Texture2D.MostDetailedMip = 0;
        srv_desc.Texture2D.MipLevels = 1;

        ThrowIfFailed(d3d.device->CreateShaderResourceView(render_target->texture.Get(), &srv_desc, render_target->texture_data.resource_view.GetAddressOf()));

        D3D11_SAMPLER_DESC sampler_desc;
        ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));

        sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler_desc.MinLOD = 0;
        sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

        ThrowIfFailed(d3d.device->CreateSamplerState(&sampler_desc, render_target->texture_data.sampler_state.GetAddressOf()));
    } else {
        render_target->texture_data.resource_view = nullptr;
        render_target->texture_data.sampler_state = nullptr;
    }

    // Create depth buffer

    if (has_depth_buffer) {
        D3D11_TEXTURE2D_DESC depth_stencil_texture_desc;
        ZeroMemory(&depth_stencil_texture_desc, sizeof(D3D11_TEXTURE2D_DESC));

        depth_stencil_texture_desc.Width = width;
        depth_stencil_texture_desc.Height = height;
        depth_stencil_texture_desc.MipLevels = 1;
        depth_stencil_texture_desc.ArraySize = 1;
        depth_stencil_texture_desc.Format = d3d.feature_level >= D3D_FEATURE_LEVEL_10_0 ? DXGI_FORMAT_D32_FLOAT : DXGI_FORMAT_D24_UNORM_S8_UINT;
        depth_stencil_texture_desc.SampleDesc = d3d.sample_description;
        depth_stencil_texture_desc.Usage = D3D11_USAGE_DEFAULT;
        depth_stencil_texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depth_stencil_texture_desc.CPUAccessFlags = 0;
        depth_stencil_texture_desc.MiscFlags = 0;

        ComPtr<ID3D11Texture2D> depth_stencil_texture;
        ThrowIfFailed(d3d.device->CreateTexture2D(&depth_stencil_texture_desc, nullptr, depth_stencil_texture.GetAddressOf()));
        ThrowIfFailed(d3d.device->CreateDepthStencilView(depth_stencil_texture.Get(), nullptr, render_target->depth_stencil_view.GetAddressOf()));
    } else {
        render_target->depth_stencil_view = nullptr;
    }

    // Create a copy of the framebuffer to be able to read it from CPU

    if (create_cpu_readable_copy) {
        texture_desc.Usage = D3D11_USAGE_STAGING;
        texture_desc.BindFlags = 0;
        texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

        ThrowIfFailed(d3d.device->CreateTexture2D(&texture_desc, nullptr, render_target->cpu_readable_texture_copy.GetAddressOf()));
    } else {
        render_target->cpu_readable_texture_copy = nullptr;
    }
}

static void draw_render_target(const RenderTarget *dst_render_target, const RenderTarget *src_render_target, bool clear_before_drawing) {
    // Set render target

    d3d.context->OMSetRenderTargets(1, dst_render_target->render_target_view.GetAddressOf(), NULL);

    if (clear_before_drawing) {
        const float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        d3d.context->ClearRenderTargetView(dst_render_target->render_target_view.Get(), clearColor);
    }

    // Disable depth buffer

    set_depth_stencil_state(false, false);
    set_rasterizer_state(false);

    // Viewport and Scissor

    set_viewport(0, 0, dst_render_target->texture_data.width, dst_render_target->texture_data.height);
    set_scissor(0, 0, dst_render_target->texture_data.width, dst_render_target->texture_data.height);

    // Set vertex buffer data

    float rt_aspect = (float) dst_render_target->texture_data.width / (float) dst_render_target->texture_data.height;
    float current_aspect = (float) d3d.current_width / (float) d3d.current_height;
    float w = current_aspect / rt_aspect;

    float buf_vbo[] = {
        -w, +1.0, 0.0, 0.0,
        -w, -1.0, 0.0, 1.0,
        +w, +1.0, 1.0, 0.0,
        +w, -1.0, 1.0, 1.0
    };

    uint32_t stride = 2 * 2 * sizeof(float);
    set_vertex_buffer(buf_vbo, 4 * stride, stride);

    // Set shader stuff

    set_shader(&d3d.rt_shader_program);
    set_shader_resources(0, &src_render_target->texture_data);
    set_primitive_topology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    d3d.context->Draw(4, 0);

    set_shader_resources(0, nullptr);
}

static void initialize_framebuffer() {
    create_render_target(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, false, false, true, &d3d.framebuffer_rt);

    // Compile the shader used to draw the fullscreen quad with the render target

    struct ShaderProgramD3D11 *prg = &d3d.rt_shader_program;
    size_t shader_length = strlen(rt_shader);
    ComPtr<ID3DBlob> vs = compile_shader(rt_shader, shader_length, rt_shader, shader_length, prg);

    // Create input layout

    D3D11_INPUT_ELEMENT_DESC ied[2];
    ied[0] = { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
    ied[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };

    ThrowIfFailed(d3d.device->CreateInputLayout(ied, 2, vs->GetBufferPointer(), vs->GetBufferSize(), prg->input_layout.GetAddressOf()));

    // Blend state

    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));

    blend_desc.RenderTarget[0].BlendEnable = false;
    blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    ThrowIfFailed(d3d.device->CreateBlendState(&blend_desc, prg->blend_state.GetAddressOf()));
}

static void create_render_target_views(bool is_resize) {
    DXGI_SWAP_CHAIN_DESC1 desc1;

    if (is_resize) {
        // Release previous stuff (if any)

        d3d.backbuffer_rt.texture.Reset();
        d3d.backbuffer_rt.render_target_view.Reset();

        d3d.main_rt.texture.Reset();
        d3d.main_rt.render_target_view.Reset();
        d3d.main_rt.depth_stencil_view.Reset();
        d3d.main_rt.texture_data.resource_view.Reset();
        d3d.main_rt.texture_data.sampler_state.Reset();

        // Resize swap chain buffers

        ThrowIfFailed(d3d.swap_chain->GetDesc1(&desc1));
        ThrowIfFailed(d3d.swap_chain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, desc1.Flags),
                      gfx_dxgi_get_h_wnd(), "Failed to resize IDXGISwapChain buffers.");
    } else {
        // Only initialize the framebuffer the first time
        initialize_framebuffer();
    }

    // Get new size

    ThrowIfFailed(d3d.swap_chain->GetDesc1(&desc1));

    // Create back buffer

    ThrowIfFailed(d3d.swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *) d3d.backbuffer_rt.texture.GetAddressOf()),
                  gfx_dxgi_get_h_wnd(), "Failed to get backbuffer from IDXGISwapChain.");

    ThrowIfFailed(d3d.device->CreateRenderTargetView(d3d.backbuffer_rt.texture.Get(), nullptr, d3d.backbuffer_rt.render_target_view.GetAddressOf()),
                  gfx_dxgi_get_h_wnd(), "Failed to create render target view.");

    d3d.backbuffer_rt.texture_data.width = desc1.Width;
    d3d.backbuffer_rt.texture_data.height = desc1.Height;

    // Create the main render target where contents will be rendered

    create_render_target(desc1.Width, desc1.Height, true, true, false, &d3d.main_rt);

    // Save resolution

    d3d.current_width = desc1.Width;
    d3d.current_height = desc1.Height;
}

static void gfx_d3d11_init(void) {
    // Load d3d11.dll
    d3d.d3d11_module = LoadLibraryW(L"d3d11.dll");
    if (d3d.d3d11_module == nullptr) {
        ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()), gfx_dxgi_get_h_wnd(), "d3d11.dll could not be loaded");
    }
    d3d.D3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)GetProcAddress(d3d.d3d11_module, "D3D11CreateDevice");

    // Load D3DCompiler_47.dll or D3DCompiler_43.dll
    d3d.d3dcompiler_module = LoadLibraryW(L"D3DCompiler_47.dll");
    if (d3d.d3dcompiler_module == nullptr) {
        d3d.d3dcompiler_module = LoadLibraryW(L"D3DCompiler_43.dll");
        if (d3d.d3dcompiler_module == nullptr) {
            ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()), gfx_dxgi_get_h_wnd(), "D3DCompiler_47.dll or D3DCompiler_43.dll could not be loaded");
        }
    }
    d3d.D3DCompile = (pD3DCompile)GetProcAddress(d3d.d3dcompiler_module, "D3DCompile");

    // Create D3D11 device

    gfx_dxgi_create_factory_and_device(DEBUG_D3D, 11, [](IDXGIAdapter1 *adapter, bool test_only) {
#if DEBUG_D3D
        UINT device_creation_flags = D3D11_CREATE_DEVICE_DEBUG;
#else
        UINT device_creation_flags = 0;
#endif
        D3D_FEATURE_LEVEL FeatureLevels[] = {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1
        };

        HRESULT res = d3d.D3D11CreateDevice(
            adapter,
            D3D_DRIVER_TYPE_UNKNOWN, // since we use a specific adapter
            nullptr,
            device_creation_flags,
            FeatureLevels,
            ARRAYSIZE(FeatureLevels),
            D3D11_SDK_VERSION,
            test_only ? nullptr : d3d.device.GetAddressOf(),
            &d3d.feature_level,
            test_only ? nullptr : d3d.context.GetAddressOf());

        if (test_only) {
            return SUCCEEDED(res);
        } else {
            ThrowIfFailed(res, gfx_dxgi_get_h_wnd(), "Failed to create D3D11 device.");
            return true;
        }
    });

    // Sample description to be used in several textures

    d3d.sample_description.Count = 1;
    d3d.sample_description.Quality = 0;

    // Create the swap chain
    d3d.swap_chain = gfx_dxgi_create_swap_chain(d3d.device.Get());

    // Create D3D Debug device if in debug mode

#if DEBUG_D3D
    ThrowIfFailed(d3d.device->QueryInterface(__uuidof(ID3D11Debug), (void **) d3d.debug.GetAddressOf()),
                  gfx_dxgi_get_h_wnd(), "Failed to get ID3D11Debug device.");
#endif

    // Create views

    create_render_target_views(false);

    // Create main vertex buffer

    D3D11_BUFFER_DESC vertex_buffer_desc;
    ZeroMemory(&vertex_buffer_desc, sizeof(D3D11_BUFFER_DESC));

    vertex_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    vertex_buffer_desc.ByteWidth = VERTEX_BUFFER_SIZE * sizeof(float);
    vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertex_buffer_desc.MiscFlags = 0;

    ThrowIfFailed(d3d.device->CreateBuffer(&vertex_buffer_desc, nullptr, d3d.vertex_buffer.GetAddressOf()),
                  gfx_dxgi_get_h_wnd(), "Failed to create vertex buffer.");

    // Create per-frame constant buffer

    D3D11_BUFFER_DESC constant_buffer_desc;
    ZeroMemory(&constant_buffer_desc, sizeof(D3D11_BUFFER_DESC));

    constant_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    constant_buffer_desc.ByteWidth = sizeof(PerFrameCB);
    constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constant_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    constant_buffer_desc.MiscFlags = 0;

    ThrowIfFailed(d3d.device->CreateBuffer(&constant_buffer_desc, nullptr, d3d.per_frame_cb.GetAddressOf()),
                  gfx_dxgi_get_h_wnd(), "Failed to create per-frame constant buffer.");

    d3d.context->PSSetConstantBuffers(0, 1, d3d.per_frame_cb.GetAddressOf());

    // Create per-draw constant buffer

    constant_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    constant_buffer_desc.ByteWidth = sizeof(PerDrawCB);
    constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constant_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    constant_buffer_desc.MiscFlags = 0;

    ThrowIfFailed(d3d.device->CreateBuffer(&constant_buffer_desc, nullptr, d3d.per_draw_cb.GetAddressOf()),
                  gfx_dxgi_get_h_wnd(), "Failed to create per-draw constant buffer.");

    d3d.context->PSSetConstantBuffers(1, 1, d3d.per_draw_cb.GetAddressOf());

    // Initialize pipeline state

    ZeroMemory(&d3d.state, sizeof(PipelineState));
    d3d.state.depth_test = -1;
    d3d.state.depth_mask = -1;
    d3d.state.zmode_decal = -1;
}

static bool gfx_d3d11_z_is_from_0_to_1(void) {
    return true;
}

static void gfx_d3d11_unload_shader(struct ShaderProgram *old_prg) {
}

static void gfx_d3d11_load_shader(struct ShaderProgram *new_prg) {
    d3d.current_shader_program = (struct ShaderProgramD3D11 *)new_prg;
}

static struct ShaderProgram *gfx_d3d11_create_and_load_new_shader(uint32_t shader_id) {
    CCFeatures cc_features;
    gfx_cc_get_features(shader_id, &cc_features);

    char buf[4096];
    size_t len, num_floats;

#ifdef THREE_POINT_FILTERING
    bool three_point_filtering = true;
#else
    bool three_point_filtering = false;
#endif

    gfx_direct3d_common_build_shader(buf, len, num_floats, cc_features, false, three_point_filtering);

    struct ShaderProgramD3D11 *prg = &d3d.shader_program_pool[d3d.shader_program_pool_size++];
    ComPtr<ID3DBlob> vs = compile_shader(buf, len, buf, len, prg);

    // Input Layout

    D3D11_INPUT_ELEMENT_DESC ied[7];
    uint8_t ied_index = 0;
    ied[ied_index++] = { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
    if (cc_features.used_textures[0] || cc_features.used_textures[1]) {
        ied[ied_index++] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
    }
    if (cc_features.opt_fog) {
        ied[ied_index++] = { "FOG", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
    }
    for (unsigned int i = 0; i < cc_features.num_inputs; i++) {
        DXGI_FORMAT format = cc_features.opt_alpha ? DXGI_FORMAT_R32G32B32A32_FLOAT : DXGI_FORMAT_R32G32B32_FLOAT;
        ied[ied_index++] = { "INPUT", i, format, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
    }

    ThrowIfFailed(d3d.device->CreateInputLayout(ied, ied_index, vs->GetBufferPointer(), vs->GetBufferSize(), prg->input_layout.GetAddressOf()));

    // Blend state

    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));

    if (cc_features.opt_alpha) {
        blend_desc.RenderTarget[0].BlendEnable = true;
        blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    } else {
        blend_desc.RenderTarget[0].BlendEnable = false;
        blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    }

    ThrowIfFailed(d3d.device->CreateBlendState(&blend_desc, prg->blend_state.GetAddressOf()));

    // Save some values

    prg->shader_id = shader_id;
    prg->num_inputs = cc_features.num_inputs;
    prg->num_floats = num_floats;
    prg->used_textures[0] = cc_features.used_textures[0];
    prg->used_textures[1] = cc_features.used_textures[1];

    return (struct ShaderProgram *)(d3d.current_shader_program = prg);
}

static struct ShaderProgram *gfx_d3d11_lookup_shader(uint32_t shader_id) {
    for (size_t i = 0; i < d3d.shader_program_pool_size; i++) {
        if (d3d.shader_program_pool[i].shader_id == shader_id) {
            return (struct ShaderProgram *)&d3d.shader_program_pool[i];
        }
    }
    return nullptr;
}

static void gfx_d3d11_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    struct ShaderProgramD3D11 *p = (struct ShaderProgramD3D11 *)prg;

    *num_inputs = p->num_inputs;
    used_textures[0] = p->used_textures[0];
    used_textures[1] = p->used_textures[1];
}

static uint32_t gfx_d3d11_new_texture(void) {
    d3d.textures.resize(d3d.textures.size() + 1);
    return (uint32_t)(d3d.textures.size() - 1);
}

static void gfx_d3d11_select_texture(int tile, uint32_t texture_id) {
    d3d.current_tile = tile;
    d3d.current_texture_ids[tile] = texture_id;
}

static D3D11_TEXTURE_ADDRESS_MODE gfx_cm_to_d3d11(uint32_t val) {
    if (val & G_TX_CLAMP) {
        return D3D11_TEXTURE_ADDRESS_CLAMP;
    }
    return (val & G_TX_MIRROR) ? D3D11_TEXTURE_ADDRESS_MIRROR : D3D11_TEXTURE_ADDRESS_WRAP;
}

static void gfx_d3d11_upload_texture(const uint8_t *rgba32_buf, int width, int height) {
    // Create texture

    D3D11_TEXTURE2D_DESC texture_desc;
    ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));

    texture_desc.Width = width;
    texture_desc.Height = height;
    texture_desc.Usage = D3D11_USAGE_IMMUTABLE;
    texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texture_desc.CPUAccessFlags = 0;
    texture_desc.MiscFlags = 0; // D3D11_RESOURCE_MISC_GENERATE_MIPS ?
    texture_desc.ArraySize = 1;
    texture_desc.MipLevels = 1;
    texture_desc.SampleDesc.Count = 1;
    texture_desc.SampleDesc.Quality = 0;

    D3D11_SUBRESOURCE_DATA resource_data;
    resource_data.pSysMem = rgba32_buf;
    resource_data.SysMemPitch = width * 4;
    resource_data.SysMemSlicePitch = resource_data.SysMemPitch * height;

    ComPtr<ID3D11Texture2D> texture;
    ThrowIfFailed(d3d.device->CreateTexture2D(&texture_desc, &resource_data, texture.GetAddressOf()));

    // Create shader resource view from texture

    D3D11_SHADER_RESOURCE_VIEW_DESC resource_view_desc;
    ZeroMemory(&resource_view_desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

    resource_view_desc.Format = texture_desc.Format;
    resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    resource_view_desc.Texture2D.MostDetailedMip = 0;
    resource_view_desc.Texture2D.MipLevels = -1;

    TextureData *texture_data = &d3d.textures[d3d.current_texture_ids[d3d.current_tile]];
    texture_data->width = width;
    texture_data->height = height;

    if (texture_data->resource_view.Get() != nullptr) {
        // Free the previous texture in this slot
        texture_data->resource_view.Reset();
    }

    ThrowIfFailed(d3d.device->CreateShaderResourceView(texture.Get(), &resource_view_desc, texture_data->resource_view.GetAddressOf()));
}

static void gfx_d3d11_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt) {
    D3D11_SAMPLER_DESC sampler_desc;
    ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));

#ifdef THREE_POINT_FILTERING
    sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
#else
    sampler_desc.Filter = linear_filter ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_POINT;
#endif
    sampler_desc.AddressU = gfx_cm_to_d3d11(cms);
    sampler_desc.AddressV = gfx_cm_to_d3d11(cmt);
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.MinLOD = 0;
    sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

    TextureData *texture_data = &d3d.textures[d3d.current_texture_ids[tile]];
    texture_data->linear_filtering = linear_filter;

    // This function is called twice per texture, the first one only to set default values.
    // Maybe that could be skipped? Anyway, make sure to release the first default sampler
    // state before setting the actual one.
    texture_data->sampler_state.Reset();

    ThrowIfFailed(d3d.device->CreateSamplerState(&sampler_desc, texture_data->sampler_state.GetAddressOf()));
}

static void gfx_d3d11_set_depth_test(bool depth_test) {
    d3d.current_depth_test = depth_test;
}

static void gfx_d3d11_set_depth_mask(bool depth_mask) {
    d3d.current_depth_mask = depth_mask;
}

static void gfx_d3d11_set_zmode_decal(bool zmode_decal) {
    d3d.current_zmode_decal = zmode_decal;
}

static void gfx_d3d11_set_viewport(int x, int y, int width, int height) {
    d3d.current_viewport_x = x;
    d3d.current_viewport_y = d3d.current_height - y - height;
    d3d.current_viewport_width = width;
    d3d.current_viewport_height = height;
}

static void gfx_d3d11_set_scissor(int x, int y, int width, int height) {
    d3d.current_scissor_x = x;
    d3d.current_scissor_y = d3d.current_height - y - height;
    d3d.current_scissor_width = x + width;
    d3d.current_scissor_height = d3d.current_height - y;
}

static void gfx_d3d11_set_use_alpha(bool use_alpha) {
    // Already part of the pipeline state from shader info
}

static void gfx_d3d11_draw_triangles(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {

    set_depth_stencil_state(d3d.current_depth_test, d3d.current_depth_mask);
    set_rasterizer_state(d3d.current_zmode_decal);

    // Viewport and Scissor

    set_viewport(d3d.current_viewport_x, d3d.current_viewport_y, d3d.current_viewport_width, d3d.current_viewport_height);
    set_scissor(d3d.current_scissor_x, d3d.current_scissor_y, d3d.current_scissor_width, d3d.current_scissor_height);

    // Textures

    for (uint8_t i = 0; i < 2; i++) {
        if (d3d.current_shader_program->used_textures[i]) {
            set_shader_resources(i, &d3d.textures[d3d.current_texture_ids[i]]);
        }
    }

    // Set per-draw constant buffer

#ifdef THREE_POINT_FILTERING
    D3D11_MAPPED_SUBRESOURCE ms;
    ZeroMemory(&ms, sizeof(D3D11_MAPPED_SUBRESOURCE));
    d3d.context->Map(d3d.per_draw_cb.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    memcpy(ms.pData, &d3d.per_draw_cb_data, sizeof(PerDrawCB));
    d3d.context->Unmap(d3d.per_draw_cb.Get(), 0);
#endif

    // Set vertex buffer data

    size_t buffer_length = buf_vbo_len * sizeof(float);
    uint32_t stride = d3d.current_shader_program->num_floats * sizeof(float);
    set_vertex_buffer(buf_vbo, buffer_length, stride);

    set_shader(d3d.current_shader_program);

    set_primitive_topology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    d3d.context->Draw(buf_vbo_num_tris * 3, 0);
}

static void gfx_d3d11_get_framebuffer(uint16_t *buffer) {
    d3d.context->CopyResource(d3d.framebuffer_rt.cpu_readable_texture_copy.Get(), d3d.framebuffer_rt.texture.Get());
    d3d.framebuffer_requested = true;
    d3d.framebuffer_data = buffer;
}

static void gfx_d3d11_on_resize(void) {
    create_render_target_views(true);
}

static void gfx_d3d11_start_frame(void) {
    // Set render targets

    d3d.context->OMSetRenderTargets(1, d3d.main_rt.render_target_view.GetAddressOf(), d3d.main_rt.depth_stencil_view.Get());

    // Clear render targets

    const float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    d3d.context->ClearRenderTargetView(d3d.main_rt.render_target_view.Get(), clearColor);
    d3d.context->ClearDepthStencilView(d3d.main_rt.depth_stencil_view.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    // Set per-frame constant buffer

    d3d.per_frame_cb_data.noise_frame++;
    if (d3d.per_frame_cb_data.noise_frame > 150) {
        // No high values, as noise starts to look ugly
        d3d.per_frame_cb_data.noise_frame = 0;
    }

    float aspect_ratio = (float) d3d.current_width / (float) d3d.current_height;
    d3d.per_frame_cb_data.noise_scale_x = 120 * aspect_ratio; // 120 = N64 height resolution (240) / 2
    d3d.per_frame_cb_data.noise_scale_y = 120;

    D3D11_MAPPED_SUBRESOURCE ms;
    ZeroMemory(&ms, sizeof(D3D11_MAPPED_SUBRESOURCE));
    d3d.context->Map(d3d.per_frame_cb.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    memcpy(ms.pData, &d3d.per_frame_cb_data, sizeof(PerFrameCB));
    d3d.context->Unmap(d3d.per_frame_cb.Get(), 0);
}

static void gfx_d3d11_end_frame(void) {
    draw_render_target(&d3d.backbuffer_rt, &d3d.main_rt, false);
    draw_render_target(&d3d.framebuffer_rt, &d3d.main_rt, true);

    if (d3d.framebuffer_requested) {
        D3D11_MAPPED_SUBRESOURCE ms;
        ZeroMemory(&ms, sizeof(D3D11_MAPPED_SUBRESOURCE));
        UINT subresource = D3D11CalcSubresource(0, 0, 0);
        d3d.context->Map(d3d.framebuffer_rt.cpu_readable_texture_copy.Get(), subresource, D3D11_MAP_READ, 0, &ms);
        uint8_t *pixels = (uint8_t *) ms.pData;

        uint32_t bi = 0;
        for (uint32_t y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
            for (uint32_t x = 0; x < FRAMEBUFFER_WIDTH; x++) {
                uint32_t fb_pixel = (y * FRAMEBUFFER_WIDTH + x) * 4;

                uint8_t r = pixels[fb_pixel + 0] >> 3;
                uint8_t g = pixels[fb_pixel + 1] >> 3;
                uint8_t b = pixels[fb_pixel + 2] >> 3;
                uint8_t a = 1; //pixels[fb_pixel + 3] / 255;

                d3d.framebuffer_data[bi] = (r << 11) | (g << 6) | (b << 1) | a;
                bi++;
            }
        }

        d3d.context->Unmap(d3d.framebuffer_rt.cpu_readable_texture_copy.Get(), subresource);
        d3d.framebuffer_requested = false;
    }
}

static void gfx_d3d11_finish_render(void) {
}

static void gfx_d3d11_shutdown() {
#if DEBUG_D3D

    // Check if there are any leaking resources.
    // Normally the will be relased automatically thanks to ComPtr,
    // but let's release them manually here to see what ReportLiveDeviceObjects() reports.
    // ID3D11Device should appear with Refcount: 4,
    // IDXGISwapChain should have Refcount: 1 (there's still a reference in gfx_dxgi.cpp that is released later)
    // And all the rest should have RefCount: 0.

    d3d.state.blend_state = nullptr;
    d3d.state.resource_views[0] = nullptr;
    d3d.state.resource_views[1] = nullptr;
    d3d.state.sampler_states[0] = nullptr;
    d3d.state.sampler_states[1] = nullptr;

    for (int t = 0; t < d3d.textures.size(); t++) {
        d3d.textures[t].resource_view.Reset();
        d3d.textures[t].sampler_state.Reset();
    }

    for (int s = 0; s < d3d.shader_program_pool_size; s++) {
        d3d.shader_program_pool[s].vertex_shader.Reset();
        d3d.shader_program_pool[s].pixel_shader.Reset();
        d3d.shader_program_pool[s].blend_state.Reset();
        d3d.shader_program_pool[s].input_layout.Reset();
    }

    d3d.rt_shader_program.vertex_shader.Reset();
    d3d.rt_shader_program.pixel_shader.Reset();
    d3d.rt_shader_program.blend_state.Reset();
    d3d.rt_shader_program.input_layout.Reset();

    d3d.backbuffer_rt.texture.Reset();
    d3d.backbuffer_rt.render_target_view.Reset();
    d3d.backbuffer_rt.depth_stencil_view.Reset();
    d3d.backbuffer_rt.cpu_readable_texture_copy.Reset();
    d3d.backbuffer_rt.texture_data.resource_view.Reset();
    d3d.backbuffer_rt.texture_data.sampler_state.Reset();

    d3d.main_rt.texture.Reset();
    d3d.main_rt.render_target_view.Reset();
    d3d.main_rt.depth_stencil_view.Reset();
    d3d.main_rt.cpu_readable_texture_copy.Reset();
    d3d.main_rt.texture_data.resource_view.Reset();
    d3d.main_rt.texture_data.sampler_state.Reset();

    d3d.framebuffer_rt.texture.Reset();
    d3d.framebuffer_rt.render_target_view.Reset();
    d3d.framebuffer_rt.depth_stencil_view.Reset();
    d3d.framebuffer_rt.cpu_readable_texture_copy.Reset();
    d3d.framebuffer_rt.texture_data.resource_view.Reset();
    d3d.framebuffer_rt.texture_data.sampler_state.Reset();

    d3d.vertex_buffer.Reset();
    d3d.per_frame_cb.Reset();
    d3d.per_draw_cb.Reset();

    d3d.depth_stencil_state.Reset();
    d3d.rasterizer_state.Reset();
    d3d.swap_chain.Reset();
    d3d.context.Reset();

    d3d.debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
#endif
}

} // namespace

struct GfxRenderingAPI gfx_direct3d11_api = {
    gfx_d3d11_z_is_from_0_to_1,
    gfx_d3d11_unload_shader,
    gfx_d3d11_load_shader,
    gfx_d3d11_create_and_load_new_shader,
    gfx_d3d11_lookup_shader,
    gfx_d3d11_shader_get_info,
    gfx_d3d11_new_texture,
    gfx_d3d11_select_texture,
    gfx_d3d11_upload_texture,
    gfx_d3d11_set_sampler_parameters,
    gfx_d3d11_set_depth_test,
    gfx_d3d11_set_depth_mask,
    gfx_d3d11_set_zmode_decal,
    gfx_d3d11_set_viewport,
    gfx_d3d11_set_scissor,
    gfx_d3d11_set_use_alpha,
    gfx_d3d11_draw_triangles,
    gfx_d3d11_get_framebuffer,
    gfx_d3d11_init,
    gfx_d3d11_on_resize,
    gfx_d3d11_start_frame,
    gfx_d3d11_end_frame,
    gfx_d3d11_finish_render,
    gfx_d3d11_shutdown,
};

#endif
