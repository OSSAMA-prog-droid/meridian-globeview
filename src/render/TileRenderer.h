#pragma once
// Builds geometry for Web Mercator map tiles.

#include <vector>
#include "globeview/Math.h"
#include "globeview/Geo.h"

namespace gv {

struct TileVertex {
  Vec3f position;  // world-space metres
  Vec2f uv;        // texture coordinates
};

class TileRenderer {
public:
  // Four corners (TL, TR, BR, BL) for one map tile, in world space.
  std::vector<TileVertex> buildTileQuad(const TileKey& key) const;
};

} // namespace gv
