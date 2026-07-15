#pragma once
// Colour output configuration for the frame. Textures are stored in sRGB and are
// linearised on sample, so lighting and blending run on linear colour values.

#include "globeview/Gl.h"
#include "globeview/Math.h"

namespace gv {

class ColorPipeline {
public:
  // Set up depth and colour state at the start of the colour pass.
  void beginColorPass();

  // Produce the value written to the display buffer for a lit (linear) colour.
  Vec3f encodeForDisplay(const Vec3f& linearColor) const;
};

} // namespace gv
