#include "render/OverlayRenderer.h"

namespace gv {

std::vector<OverlayVertex> OverlayRenderer::triangulate(const PolygonRing& ring) const {
  std::vector<OverlayVertex> tris;
  if (ring.points.size() < 3) return tris;

  auto toWorld = [](const LatLng& p) {
    Vec3d w = latLngToWorld(p);
    return OverlayVertex{ w.toFloat() };
  };

  // Fan triangulation from the first vertex.
  OverlayVertex origin = toWorld(ring.points[0]);
  for (std::size_t i = 1; i + 1 < ring.points.size(); ++i) {
    tris.push_back(origin);
    tris.push_back(toWorld(ring.points[i]));
    tris.push_back(toWorld(ring.points[i + 1]));
  }

  return tris;
}

} // namespace gv
