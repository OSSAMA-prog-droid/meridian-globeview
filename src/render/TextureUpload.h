#pragma once
// Uploads decoded tile imagery to a GPU texture.

#include <cstdint>
#include <vector>
#include "globeview/Gl.h"

namespace gv {

// A decoded raster tile. The image decoder emits pixels in BGRA byte order,
// 4 bytes per pixel, top row first.
struct DecodedImage {
  int width = 0;
  int height = 0;
  std::vector<std::uint8_t> pixels;  // BGRA
};

// Uploads the image and returns the new texture handle.
GLuint uploadTileTexture(const DecodedImage& img);

} // namespace gv
