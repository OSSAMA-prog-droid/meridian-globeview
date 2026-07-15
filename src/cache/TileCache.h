#pragma once
// Caches uploaded tile textures so a tile isn't re-fetched every time it scrolls
// back into view.

#include <cstddef>
#include <unordered_map>
#include "globeview/Gl.h"
#include "globeview/Geo.h"

namespace gv {

struct TileKeyHash {
  std::size_t operator()(const TileKey& k) const {
    std::size_t h = static_cast<std::size_t>(k.z);
    h = h * 1000003u + static_cast<std::size_t>(k.x);
    h = h * 1000003u + static_cast<std::size_t>(k.y);
    return h;
  }
};

class TileCache {
public:
  // Return the texture for a tile, creating and uploading it on first use.
  GLuint getOrLoad(const TileKey& key);

  std::size_t size() const { return textures_.size(); }

private:
  GLuint loadTexture(const TileKey& key);

  std::unordered_map<TileKey, GLuint, TileKeyHash> textures_;
};

} // namespace gv
