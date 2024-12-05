#pragma once

#define LEGACY_GFX_WIDOW_API

//#define LEGACY_GFX_RENDER_API

/* Essential, do not edit unless you know what are you doing */

// SoH uses ImGui to set window dimensions, which are separate to render dimensions
// so options like resolution scale and msaa can work properly
// For now we set these the same if framebuffers are enabled to simply render on screen independently
#define ENABLE_FRAMEBUFFER 1
