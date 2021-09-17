static const Vtx sparkles_animation_seg4_vertex_04032A48_mop_colors[] = {
    {{{   -32,      0,      0}, 0, {     0,    992}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    32,      0,      0}, 0, {   992,    992}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    32,     64,      0}, 0, {   992,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -32,     64,      0}, 0, {     0,      0}, {0xff, 0xff, 0x64, 0xff}}},
};

const Gfx sparkles_animation_seg4_dl_04035288_mop_colors[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(sparkles_animation_seg4_vertex_04032A48_mop_colors, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

const Gfx sparkles_animation_seg4_dl_04035300_mop_colors[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04032A88),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288_mop_colors),
};

const Gfx sparkles_animation_seg4_dl_04035318_mop_colors[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04033288),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288_mop_colors),
};

const Gfx sparkles_animation_seg4_dl_04035330_mop_colors[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04033A88),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288_mop_colors),
};

const Gfx sparkles_animation_seg4_dl_04035348_mop_colors[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04034288),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288_mop_colors),
};

const Gfx sparkles_animation_seg4_dl_04035360_mop_colors[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04034A88),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288_mop_colors),
};