#include "render/TerrainMesh.h"

namespace gv {

TerrainMeshData TerrainMesh::buildMesh(const BBox& area, int gridResolution,
                                       const HeightFn& height) const {
  TerrainMeshData mesh;
  const int n = gridResolution < 1 ? 1 : gridResolution;

  const double lngStep = (area.maxLng - area.minLng) / n;
  const double latStep = (area.maxLat - area.minLat) / n;

  // Regular (n+1) x (n+1) grid of vertices, sampling the height field.
  mesh.vertices.reserve((n + 1) * (n + 1));
  for (int row = 0; row <= n; ++row) {
    for (int col = 0; col <= n; ++col) {
      LatLng c{ area.minLat + latStep * row, area.minLng + lngStep * col };
      double elev = height(c);
      Vec3d w = latLngToWorld(c, elev);
      mesh.vertices.push_back(TerrainVertex{ w.toFloat() });
    }
  }

  // Two triangles per cell.
  auto index = [n](int row, int col) { return static_cast<std::uint32_t>(row * (n + 1) + col); };
  mesh.indices.reserve(n * n * 6);
  for (int row = 0; row < n; ++row) {
    for (int col = 0; col < n; ++col) {
      std::uint32_t a = index(row,     col);
      std::uint32_t b = index(row,     col + 1);
      std::uint32_t c = index(row + 1, col);
      std::uint32_t d = index(row + 1, col + 1);
      mesh.indices.insert(mesh.indices.end(), { a, c, b, b, c, d });
    }
  }

  return mesh;
}

} // namespace gv
