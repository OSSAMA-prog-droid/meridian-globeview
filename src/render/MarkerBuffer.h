#pragma once
// GPU buffer holding live vehicle marker positions. Positions arrive on a
// background tracking thread; the renderer draws them on the main thread.

#include <cstddef>
#include <vector>
#include "globeview/Gl.h"
#include "globeview/Geo.h"

namespace gv {

class MarkerBuffer {
public:
  ~MarkerBuffer();

  void init(std::size_t capacity);

  // Called from the tracking thread when fresh positions arrive.
  void updatePositions(const std::vector<Marker>& markers);

  // Called from the render thread once per frame.
  void draw();

private:
  GLuint      vbo_      = 0;
  std::size_t capacity_ = 0;
  int         count_    = 0;
};

} // namespace gv
