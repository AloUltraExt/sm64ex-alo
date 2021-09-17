Gfx *geo_emitter_coloring(s32 callContext, struct GraphNode *node, UNUSED s32 context) {
    Gfx *gfxHead = NULL;
    Gfx *gfx;

    if (callContext == GEO_CONTEXT_RENDER) {
        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        struct GraphNodeGenerated *graphNode = (struct GraphNodeGenerated *) node;
        
        // Sparkles are transparent
        graphNode->fnNode.node.flags = (graphNode->fnNode.node.flags & 0xFF) | (LAYER_TRANSPARENT << 8);

        gfx = gfxHead = alloc_display_list(2 * sizeof(Gfx));

        u8 bp1half2 = (obj->parentObj->oBehParams >> 24) & 0x0F; // Red
        u8 bp2half1 =  obj->parentObj->oBehParams2ndByte >> 4; // Green
        u8 bp2half2 =  obj->parentObj->oBehParams2ndByte & 0x0F; // Blue

        // Color sparkles
        gDPSetEnvColor(gfx++, (bp1half2 << 4), (bp2half1 << 4), (bp2half2 << 4), 255);
        
        gSPEndDisplayList(gfx);
    }

    return gfxHead;
}

void bhv_emitter_loop(void) {
    s16 i;
    struct Object *sparkle;
    u8 bp1half1 = (o->oBehParams >> 24) >> 4; // Scale
    f32 scalePos = (f32) ((bp1half1 << 1));

    for (i = 0; i < 4; i++) {
        sparkle = try_to_spawn_object(0, 1.0f, o, MODEL_MOP_EMITTER_SPARKLES, bhvSparkle);

        if (sparkle != NULL) {
            sparkle->parentObj = o;
            sparkle->oPosX += random_float() * scalePos;
            sparkle->oPosZ += random_float() * scalePos;

            obj_translate_xyz_random(sparkle, 90.0f);
            obj_scale_random(sparkle, 1.0, 0.0f);
            
            if (sparkle->oAnimState > 8) {
                obj_mark_for_deletion(sparkle);
            }
        }
    }
}
