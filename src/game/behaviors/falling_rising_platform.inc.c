// falling_rising_platform.inc.c

void bhv_squishable_platform_loop(void) {
    o->header.gfx.scale[1] = (sins(o->oBitFSPlatformTimer) + 1.0) * 0.3 + 0.4;
    o->oBitFSPlatformTimer += 0x80;
}

void bhv_bitfs_sinking_platform_loop(void) {
    // ex-alo change
    // Adds missing "f" symbol to "0.58"
    o->oPosY -= sins(o->oBitFSPlatformTimer) * 0.58f;
    o->oBitFSPlatformTimer += 0x100;
}

// TODO: Named incorrectly. fix
void bhv_ddd_moving_pole_loop(void) {
    obj_copy_pos_and_angle(o, o->parentObj);
}

void bhv_bitfs_sinking_cage_platform_loop(void) {
    if (o->oBhvParams2ndByte != 0) {
        if (o->oTimer == 0) {
            o->oPosY -= 300.0f;
        }
        o->oPosY += sins(o->oBitFSPlatformTimer) * 7.0f;
    } else {
        o->oPosY -= sins(o->oBitFSPlatformTimer) * 3.0f;
    }

    o->oBitFSPlatformTimer += 0x100;
}
