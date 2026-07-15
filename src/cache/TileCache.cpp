#include "cache/TileCache.h"

namespace gv {

GLuint TileCache::loadTexture(const TileKey& /*key*/) {
  GLuint tex = 0;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  // (the tile image would be fetched and uploaded into `tex` here)
  glBindTexture(GL_TEXTURE_2D, 0);
  return tex;
}

GLuint TileCache::getOrLoad(const TileKey& key) {
  auto it = textures_.find(key);
  if (it != textures_.end()) return it->second;

  GLuint tex = loadTexture(key);
  textures_[key] = tex;
  return tex;
}

} // namespace gv
