#include "src/game/envfx_snow.h"

const GeoLayout exclamation_box_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_CULLING_RADIUS(300),
		GEO_OPEN_NODE(),
			GEO_SHADOW(SHADOW_SQUARE_PERMANENT, 0xB4, 70),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, exclamation_box_displaylist_mesh_layer_1),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, exclamation_box_displaylist_mesh_layer_2),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, exclamation_box_displaylist_mesh_layer_3),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, exclamation_box_displaylist_mesh_layer_4),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
