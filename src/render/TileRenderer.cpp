#include "render/TileRenderer.h"

namespace gv {

// World-space extent (metres) covered by one tile at the given zoom level.
static double tileSpanMeters(int z) {
  return kEarthCircumference / static_cast<double>(1 << z);
}

std::vector<TileVertex> TileRenderer::buildTileQuad(const TileKey& key) const {
  const double span = tileSpanMeters(key.z);

  // Tile (0,0) is the top-left of the world; x grows east, y grows south.
  const double left   = -kMercatorMax + key.x * span;
  const double right  = left + span;
  const double top    =  kMercatorMax - key.y * span;
  const double bottom = top - span;

  auto vert = [](double wx, double wy, float u, float v) {
    return TileVertex{
      Vec3f{ static_cast<float>(wx), static_cast<float>(wy), 0.0f },
      Vec2f{ u, v }
    };
  };

  // Corners with their texture coordinates, walking the tile top-left to
  // bottom-left the same way the tile image is laid out.
  return {
    vert(left,  top,    0.0f, 0.0f),
    vert(right, top,    1.0f, 0.0f),
    vert(right, bottom, 1.0f, 1.0f),
    vert(left,  bottom, 0.0f, 1.0f),
  };
}

} // namespace gv
