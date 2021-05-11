#include <PR/ultratypes.h>

#include "sm64.h"
#include "behavior_data.h"
#include "level_table.h"
#include "model_ids.h"
#include "object_fields.h"
#include "seq_ids.h"

#include "extras/misc_functions.h"

#include "actors/common0.h"

#include "audio/data.h"
#include "audio/external.h"

#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/level_script.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"

#include "game/area.h"
#include "game/behavior_actions.h"
#include "game/camera.h"
#include "game/debug.h"
#include "game/game_init.h"
#include "game/interaction.h"
#include "game/level_update.h"
#include "game/main.h"
#include "game/mario.h"
#include "game/mario_actions_airborne.h"
#include "game/mario_actions_automatic.h"
#include "game/mario_actions_cutscene.h"
#include "game/mario_actions_moving.h"
#include "game/mario_actions_object.h"
#include "game/mario_actions_stationary.h"
#include "game/mario_actions_submerged.h"
#include "game/mario_misc.h"
#include "game/mario_step.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/object_list_processor.h"
#include "game/print.h"
#include "game/rendering_graph_node.h"
#include "game/rumble_init.h"
#include "game/save_file.h"
#include "game/sound_init.h"

#include "pc/configfile.h"

#include "options_menu.h"
#include "cheats.h"

#ifndef TARGET_N64
#include "pc/cliopts.h"
#endif

// Ifdef hell but it does the job
u8 should_intro_be_skipped(void) {
#if SKIP_PEACH_CUTSCENE
    return TRUE;
#else
    return save_file_exists(gCurrSaveFileNum - 1)
#ifndef TARGET_N64
#ifdef COMMAND_LINE_OPTIONS
    || gCLIOpts.SkipIntro == TRUE
#endif
    || configSkipIntro == TRUE
#endif
    ;
#endif
}
