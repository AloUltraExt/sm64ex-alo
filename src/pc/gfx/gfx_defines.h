#pragma once

#define LEGACY_GFX_WIDOW_API

//#define LEGACY_GFX_RENDER_API

/* Essential, do not edit unless you know what are you doing */

// SoH uses ImGui to render using framebuffers
#define ENABLE_FRAMEBUFFER 1
// Without the requisite above nothing renders, so make extra changes to render directly to the screen
#define RENDER_TO_SCREEN 1
