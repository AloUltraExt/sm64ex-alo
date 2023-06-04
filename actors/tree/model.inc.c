// Tree

// 0x0302DE10
static const Lights1 tree_seg3_lights = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0302DE28
ALIGNED8 static const Texture tree_seg3_texture_bubbly_left_side[] = {
#include "actors/tree/tree_left_side.rgba16.inc.c"
};

// 0x0302EE28
ALIGNED8 static const Texture tree_seg3_texture_bubbly_right_side[] = {
#include "actors/tree/tree_right_side.rgba16.inc.c"
};

// 0x0302FE28
static const Vtx tree_seg3_vertex_bubbly_left_side[] = {
    {{{  -356,     -9,      0}, 0, {  -796,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     -9,      0}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    800,      0}, 0, {   990,   -712}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0302FE58
static const Vtx tree_seg3_vertex_bubbly_right_side[] = {
    {{{     0,     -9,      0}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   358,     -9,      0}, 0, {  1756,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    800,      0}, 0, {     0,   -712}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0302FE88 - 0x0302FEB8
const Gfx tree_seg3_sub_dl_bubbly_left_side[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_bubbly_left_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(tree_seg3_vertex_bubbly_left_side, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0302FEB8 - 0x0302FEE8
const Gfx tree_seg3_sub_dl_bubbly_right_side[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_bubbly_right_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(tree_seg3_vertex_bubbly_right_side, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

#if !OBJ_OPACITY_BY_CAM_DIST
#define tree_seg3_sub_dl_bubbly tree_seg3_dl_bubbly
#endif
// 0x0302FEE8 - 0x0302FF60
const Gfx tree_seg3_sub_dl_bubbly[] = {
#if !OBJ_OPACITY_BY_CAM_DIST
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
#endif
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(tree_seg3_sub_dl_bubbly_left_side),
    gsSPDisplayList(tree_seg3_sub_dl_bubbly_right_side),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

#if OBJ_OPACITY_BY_CAM_DIST
const Gfx tree_seg3_dl_bubbly[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPBranchList(tree_seg3_sub_dl_bubbly),
};

const Gfx tree_seg3_dl_bubbly_transparent[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsSPBranchList(tree_seg3_sub_dl_bubbly),
};
#endif
    
// 0x0302FF60
ALIGNED8 static const Texture tree_seg3_texture_pine[] = {
#include "actors/tree/pine_tree.rgba16.inc.c"
};

// 0x03030F60
static const Vtx tree_seg3_vertex_spiky[] = {
    {{{   128,    512,      0}, 0, {   990,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -127,    512,      0}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -127,      0,      0}, 0, {     0,   2012}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,      0,      0}, 0, {   990,   2012}, {0x00, 0x00, 0x7f, 0xff}}},
};

#if !OBJ_OPACITY_BY_CAM_DIST
#define tree_seg3_sub_dl_spiky tree_seg3_dl_spiky
#endif
// 0x03030FA0 - 0x03031048
const Gfx tree_seg3_sub_dl_spiky[] = {
#if !OBJ_OPACITY_BY_CAM_DIST
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
#endif
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_pine),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&tree_seg3_lights.l, 1),
    gsSPLight(&tree_seg3_lights.a, 2),
    gsSPVertex(tree_seg3_vertex_spiky, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

#if OBJ_OPACITY_BY_CAM_DIST
const Gfx tree_seg3_dl_spiky[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPBranchList(tree_seg3_sub_dl_spiky),
};

const Gfx tree_seg3_dl_spiky_transparent[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsSPBranchList(tree_seg3_sub_dl_spiky),
};
#endif

// 0x03031048
ALIGNED8 static const Texture tree_seg3_texture_snowy_pine[] = {
#include "actors/tree/snowy_pine_tree.rgba16.inc.c"
};

// 0x03032048
static const Vtx tree_seg3_vertex_snowy_pine[] = {
    {{{   128,    512,      0}, 0, {   990,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -127,    512,      0}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -127,      0,      0}, 0, {     0,   2012}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,      0,      0}, 0, {   990,   2012}, {0x00, 0x00, 0x7f, 0xff}}},
};

#if !OBJ_OPACITY_BY_CAM_DIST
#define tree_seg3_sub_dl_snowy_pine tree_seg3_dl_snowy_pine
#endif
// 0x03032088 - 0x03032130
const Gfx tree_seg3_sub_dl_snowy_pine[] = {
#if !OBJ_OPACITY_BY_CAM_DIST
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
#endif
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_snowy_pine),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&tree_seg3_lights.l, 1),
    gsSPLight(&tree_seg3_lights.a, 2),
    gsSPVertex(tree_seg3_vertex_snowy_pine, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

#if OBJ_OPACITY_BY_CAM_DIST
const Gfx tree_seg3_dl_snowy_pine[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPBranchList(tree_seg3_sub_dl_snowy_pine),
};

const Gfx tree_seg3_dl_snowy_pine_transparent[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsSPBranchList(tree_seg3_sub_dl_snowy_pine),
};
#endif

// 0x03032218
ALIGNED8 static const Texture tree_seg3_texture_palm[] = {
#include "actors/tree/palm_tree.rgba16.inc.c"
};

// 0x03033218
static const Vtx tree_seg3_vertex_palm[] = {
    {{{   170,    512,      0}, 0, {   990,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -169,    512,      0}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -169,      0,      0}, 0, {     0,   2012}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   170,      0,      0}, 0, {   990,   2012}, {0x00, 0x00, 0x7f, 0xff}}},
};

#if !OBJ_OPACITY_BY_CAM_DIST
#define tree_seg3_sub_dl_palm tree_seg3_dl_palm
#endif
// 0x03033258 - 0x03033300
const Gfx tree_seg3_sub_dl_palm[] = {
#if !OBJ_OPACITY_BY_CAM_DIST
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
#endif
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_palm),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&tree_seg3_lights.l, 1),
    gsSPLight(&tree_seg3_lights.a, 2),
    gsSPVertex(tree_seg3_vertex_palm, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

#if OBJ_OPACITY_BY_CAM_DIST
const Gfx tree_seg3_dl_palm[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPBranchList(tree_seg3_sub_dl_palm),
};

const Gfx tree_seg3_dl_palm_transparent[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsSPBranchList(tree_seg3_sub_dl_palm),
};
#endif
