// breakable_box.inc.c

void bhv_breakable_box_loop(void) {
    obj_set_hitbox(o, &sBreakableBoxHitbox);

    if (o->oTimer == 0) {
        breakable_box_init();
    }

    if (cur_obj_was_attacked_or_ground_pounded()) {
        obj_explode_and_spawn_coins(46.0f, 1);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
    }
}
