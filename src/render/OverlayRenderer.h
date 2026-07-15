#pragma once
// Triangulates country / zone boundary polygons into world-space geometry.

#include <vector>
#include "globeview/Math.h"
#include "globeview/Geo.h"

namespace gv {

struct OverlayVertex { Vec3f position; };

class OverlayRenderer {
public:
  // Triangulate one polygon ring (lon/lat degrees) into world-space triangles.
  std::vector<OverlayVertex> triangulate(const PolygonRing& ring) const;
};

} // namespace gv
