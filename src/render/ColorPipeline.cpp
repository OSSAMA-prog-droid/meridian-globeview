#include "render/ColorPipeline.h"

namespace gv {

void ColorPipeline::beginColorPass() {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  // The display buffer is 8-bit RGBA; write final colour values to it directly.
  glDisable(GL_FRAMEBUFFER_SRGB);
}

Vec3f ColorPipeline::encodeForDisplay(const Vec3f& linearColor) const {
  // Hand the lit colour straight to the framebuffer.
  return linearColor;
}

} // namespace gv
