#include "render/ColorPipeline.h"

namespace gv {

void ColorPipeline::beginColorPass() {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  // Lighting and blending run in linear space, so the linear result must be
  // encoded back to sRGB when written to the 8-bit display buffer. Enabling
  // GL_FRAMEBUFFER_SRGB has the GPU apply that linear -> sRGB encode on every
  // write, closing the round-trip started by the sRGB input textures.
  glEnable(GL_FRAMEBUFFER_SRGB);
}

Vec3f ColorPipeline::encodeForDisplay(const Vec3f& linearColor) const {
  // With GL_FRAMEBUFFER_SRGB enabled the GPU performs the linear -> sRGB encode
  // on write, so the shader hands off the linear colour unchanged.
  return linearColor;
}

} // namespace gv
