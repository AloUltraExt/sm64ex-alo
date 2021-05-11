#include "model.inc.h"
Vtx VB_Shrink_Platform_MOP_0x3021130[] = {
{{{ 113, 0, 113 }, 0, { 1015, -1015 }, { 0, 127, 0, 255}}},
{{{ -113, 0, -113 }, 0, { -1015, 1015 }, { 0, 127, 0, 255}}},
{{{ -113, 0, 113 }, 0, { -1015, -1015 }, { 0, 127, 0, 255}}},
{{{ -113, 0, -113 }, 0, { -1015, 1015 }, { 0, 127, 0, 255}}},
{{{ 113, 0, 113 }, 0, { 1015, -1015 }, { 0, 127, 0, 255}}},
{{{ 113, 0, -113 }, 0, { 1015, 1015 }, { 0, 127, 0, 255}}},
};

const Light_t Light_Shrink_Platform_MOP_0x3020920 = {
{ 255, 255, 255}, 0, { 255, 255, 255}, 0, { 127, 127, 127}, 0
};

const Ambient_t Light_Shrink_Platform_MOP_0x3020928 = {
{127, 127, 127}, 0, {127, 127, 127}, 0
};

const Gfx DL_Shrink_Platform_MOP_0x3021220[] = {
gsDPPipeSync(),
gsSPGeometryMode(0, 0),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
gsSPTexture(65535, 65535, 0, 0, 1),
gsDPTileSync(),
gsDPLoadSync(),
gsSPLight(&Light_Shrink_Platform_MOP_0x3020920.col, 1),
gsSPLight(&Light_Shrink_Platform_MOP_0x3020928.col, 2),
gsDPSetTextureImage(0, 2, 1, Shrink_Platform_MOP__texture_03020930),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_Shrink_Platform_MOP_0x3021130, 6, 0),
gsSP1Triangle(0, 1, 2, 0),
gsSPVertex(VB_Shrink_Platform_MOP_0x3021130, 6, 0),
gsSP1Triangle(3, 4, 5, 0),
gsSPTexture(65535, 65535, 0, 0, 0),
gsSPEndDisplayList(),
};

