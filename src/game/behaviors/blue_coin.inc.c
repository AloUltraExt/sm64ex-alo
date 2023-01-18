
/**
 * Behavior for bhvHiddenBlueCoin and bhvBlueCoinSwitch.
 * bhvHiddenBlueCoin are the stationary blue coins that appear when
 * you press a blue coin switch (a.k.a. bhvBlueCoinSwitch).
 */

/**
 * Update function for bhvHiddenBlueCoin.
 */
void bhv_hidden_blue_coin_loop(void) {
    struct Object *blueCoinSwitch;

    switch (o->oAction) {
        case HIDDEN_BLUE_COIN_ACT_INACTIVE:
            // Become invisible and intangible
            cur_obj_disable_rendering();
            cur_obj_become_intangible();

            // Set action to HIDDEN_BLUE_COIN_ACT_WAITING after the blue coin switch is found.
            o->oHiddenBlueCoinSwitch = cur_obj_nearest_object_with_behavior(bhvBlueCoinSwitch);

            if (o->oHiddenBlueCoinSwitch != NULL) {
                o->oAction++;
            }

            break;

        case HIDDEN_BLUE_COIN_ACT_WAITING:
            // Wait until the blue coin switch starts ticking to activate.
            blueCoinSwitch = o->oHiddenBlueCoinSwitch;

            if (blueCoinSwitch->oAction == BLUE_COIN_SWITCH_ACT_TICKING) {
                o->oAction++; // Set to HIDDEN_BLUE_COIN_ACT_ACTIVE
            }

            break;

        case HIDDEN_BLUE_COIN_ACT_ACTIVE:
            // Become tangible
            cur_obj_enable_rendering();
            cur_obj_become_tangible();

#if RESPAWN_BLUE_COIN_SWITCH
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
#endif

            // Delete the coin once collected
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                spawn_object(o, MODEL_SPARKLES, bhvGoldenCoinSparkles);
                obj_mark_for_deletion(o);
            }

            // After 200 frames of waiting and 20 2-frame blinks (for 240 frames total),
            // delete the object.
            if (cur_obj_wait_then_blink(200, 20)) {
#if RESPAWN_BLUE_COIN_SWITCH
                o->oAction = HIDDEN_BLUE_COIN_ACT_INACTIVE;
#else
                obj_mark_for_deletion(o);
#endif
            }

            break;
    }

    o->oInteractStatus = 0;
}

#if RESPAWN_BLUE_COIN_SWITCH
#define VEL_Y_MOVE 16.0f
#define TIMER_INIT 3
#else
#define VEL_Y_DOWN 20.0f
#define TIMER_INIT 5
#endif

/**
 * Update function for bhvBlueCoinSwitch.
 */
void bhv_blue_coin_switch_loop(void) {
    // The switch's model is 1/3 size.
    cur_obj_scale(3.0f);

    switch (o->oAction) {
        case BLUE_COIN_SWITCH_ACT_IDLE:
            // If Mario is on the switch and has ground-pounded,
            // recede and get ready to start ticking.
            if (gMarioObject->platform == o) {
                if (gMarioStates[0].action == ACT_GROUND_POUND_LAND) {
                    // Set to BLUE_COIN_SWITCH_ACT_RECEDING
                    o->oAction++;
                    // Recede at a rate of VEL_Y_MOVE units/frame.
                    o->oVelY = -VEL_Y_MOVE;
                    // Set gravity to 0 so it doesn't accelerate when receding.
                    o->oGravity = 0.0f;

                    cur_obj_play_sound_2(SOUND_GENERAL_SWITCH_DOOR_OPEN);
                }
            }

            // Have collision
            load_object_collision_model();

            break;

        case BLUE_COIN_SWITCH_ACT_RECEDING:
            // Recede for 6 frames before going invisible and ticking.
            // This is probably an off-by-one error, since the switch is 100 units tall
            // and recedes at 20 units/frame, which means it will fully recede after 5 frames.
            if (o->oTimer > TIMER_INIT) {
                #if !RESPAWN_BLUE_COIN_SWITCH
                cur_obj_hide();
                #endif
                // Set to BLUE_COIN_SWITCH_ACT_TICKING
                o->oAction++;
                
                // ???
#if RESPAWN_BLUE_COIN_SWITCH
                o->oVelY = 0.0f;
                o->oGravity = 0.0f;
#else
                o->oPosY = gMarioObject->oPosY - (VEL_Y_MOVE * 2);
#endif

                // Spawn particles.
                spawn_mist_particles();
            } else {
                // Have collision while receding
                load_object_collision_model();
                // Recede
                cur_obj_move_using_fvel_and_gravity();
            }

            break;

        case BLUE_COIN_SWITCH_ACT_TICKING:
            // Tick faster when the blue coins start blinking
            if (o->oTimer < 200) {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
            } else {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            }

#if RESPAWN_BLUE_COIN_SWITCH
            if (cur_obj_nearest_object_with_behavior(bhvHiddenBlueCoin) == NULL) {
                spawn_mist_particles_variable(0, 0, 46.0f);
                obj_mark_for_deletion(o);
            // Set to BLUE_COIN_SWITCH_ACT_EXTENDING after the coins unload after the 240-frame timer expires.
            } else if (o->oTimer > 240) {
                o->oAction++;
                o->oVelY    = VEL_Y_MOVE;
                o->oGravity =  0.0f;
            }
            load_object_collision_model();
            break;

        case BLUE_COIN_SWITCH_ACT_EXTENDING:
            if (o->oTimer > 3) {
                // Set to BLUE_COIN_SWITCH_ACT_IDLE
                o->oAction = BLUE_COIN_SWITCH_ACT_IDLE;
            } else {
                // Have collision while extending
                load_object_collision_model();
                // Extend
                cur_obj_move_using_fvel_and_gravity();
            }
#else
            // Delete the switch (which stops the sound) after the last coin is collected,
            // or after the coins unload after the 240-frame timer expires.
            if (cur_obj_nearest_object_with_behavior(bhvHiddenBlueCoin) == NULL || o->oTimer > 240) {
                obj_mark_for_deletion(o);
            }
#endif

            break;
    }
}

#undef VEL_Y
#undef TIMER
