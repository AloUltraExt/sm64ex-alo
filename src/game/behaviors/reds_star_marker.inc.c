// reds_star_marker.inc.c
// Filename is abbreviated to prevent compiler seg fault

void bhv_red_coin_star_marker_init(void) {
    o->header.gfx.scale[2] = 0.75f;
}

#if BETTER_REDS_STAR_MARKER
void bhv_red_coin_star_marker_loop(void) {
    struct Surface *floor;
    f32 curHeight;
    f32 waterHeight = find_water_level(o->oHomeX, o->oHomeZ);
    f32 floorHeight = find_floor(o->oHomeX, o->oHomeY, o->oHomeZ, &floor);

    if (waterHeight > floorHeight) {
        curHeight = waterHeight;
    } else {
        curHeight = floorHeight;
    }

    o->oPosY = curHeight + 60.0f;
}
#endif
