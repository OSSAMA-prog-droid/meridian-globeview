#pragma once
// Submits the frame's overlay draws to the GPU.

#include <vector>
#include "globeview/Gl.h"
#include "globeview/Math.h"

namespace gv {

struct OverlayDraw {
  GLuint             program = 0;
  std::vector<float> vertexData;   // supplied each frame
  int                vertexCount = 0;
  Mat4f              transform;
};

class FrameGraph {
public:
  void renderOverlays(const std::vector<OverlayDraw>& overlays);

private:
  void ensureBuffer();
  GLuint scratchVbo_ = 0;
};

} // namespace gv
