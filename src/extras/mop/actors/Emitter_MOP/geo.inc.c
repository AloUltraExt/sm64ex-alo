extern const Gfx sparkles_animation_seg4_dl_04035288_mop_colors[];
extern const Gfx sparkles_animation_seg4_dl_04035300_mop_colors[];
extern const Gfx sparkles_animation_seg4_dl_04035318_mop_colors[];
extern const Gfx sparkles_animation_seg4_dl_04035330_mop_colors[];
extern const Gfx sparkles_animation_seg4_dl_04035348_mop_colors[];
extern const Gfx sparkles_animation_seg4_dl_04035360_mop_colors[];

extern Gfx *geo_emitter_coloring(s32 callContext, struct GraphNode *node, UNUSED s32 context);

const GeoLayout Sparkles_Emitter_MOP[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
     GEO_ASM(0, geo_emitter_coloring),
     GEO_SWITCH_CASE(9, geo_switch_anim_state),
     GEO_OPEN_NODE(),
        GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sparkles_animation_seg4_dl_04035300_mop_colors),
        GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sparkles_animation_seg4_dl_04035318_mop_colors),
        GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sparkles_animation_seg4_dl_04035330_mop_colors),
        GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sparkles_animation_seg4_dl_04035348_mop_colors),
        GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sparkles_animation_seg4_dl_04035360_mop_colors),
        GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sparkles_animation_seg4_dl_04035348_mop_colors),
        GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sparkles_animation_seg4_dl_04035330_mop_colors),
        GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sparkles_animation_seg4_dl_04035318_mop_colors),
        GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sparkles_animation_seg4_dl_04035300_mop_colors),
     GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
