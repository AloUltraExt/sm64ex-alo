#include "src/game/envfx_snow.h"

const GeoLayout marios_winged_metal_cap_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(0, 180, 75),
		GEO_OPEN_NODE(),
			GEO_SCALE(LAYER_FORCE, 16384),
			GEO_OPEN_NODE(),
				GEO_ASM(10, geo_update_layer_transparency),
				GEO_NODE_START(),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, mario_winged_metal_cap_Winged_Metal_Cap_mesh_layer_1),
					GEO_DISPLAY_LIST(LAYER_ALPHA, mario_winged_metal_cap_Winged_Metal_Cap_mesh_layer_4),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
