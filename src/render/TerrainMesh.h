#pragma once
// Builds a triangle mesh for a terrain tile from a height sampler. Finer tiles
// (closer to the camera) are built at a higher grid resolution.

#include <cstdint>
#include <functional>
#include <vector>
#include "globeview/Math.h"
#include "globeview/Geo.h"

namespace gv {

struct TerrainVertex { Vec3f position; };

struct TerrainMeshData {
  std::vector<TerrainVertex>   vertices;
  std::vector<std::uint32_t>   indices;
};

class TerrainMesh {
public:
  using HeightFn = std::function<double(const LatLng&)>;

  // gridResolution = number of cells per edge, chosen from the tile's LOD.
  TerrainMeshData buildMesh(const BBox& area, int gridResolution, const HeightFn& height) const;
};

} // namespace gv
