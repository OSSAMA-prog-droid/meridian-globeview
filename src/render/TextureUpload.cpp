#include "render/TextureUpload.h"

namespace gv {

GLuint uploadTileTexture(const DecodedImage& img) {
  GLuint tex = 0;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Imagery is colour data, so it's stored in an sRGB internal format and
  // linearised automatically on sample.
  glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8,
               img.width, img.height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, img.pixels.data());

  glBindTexture(GL_TEXTURE_2D, 0);
  return tex;
}

} // namespace gv
