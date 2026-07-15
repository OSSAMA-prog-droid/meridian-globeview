#pragma once
// Geographic types and Web Mercator helpers. World coordinates are in metres;
// the Mercator world spans roughly ±20,037,508 m on each axis.

#include <cstdint>
#include <vector>
#include "globeview/Math.h"

namespace gv {

// Circumference of the Earth at the equator (Web Mercator world width, metres).
constexpr double kEarthCircumference = 40075016.68557849;
constexpr double kMercatorMax = kEarthCircumference / 2.0; // 20037508.34...
// Web Mercator can only represent latitudes within this bound.
constexpr double kMercatorLatLimit = 85.05112877980659;

struct LatLng { double lat = 0, lng = 0; };

struct TileKey {
  int z = 0, x = 0, y = 0;
  bool operator==(const TileKey& o) const { return z == o.z && x == o.x && y == o.y; }
};

struct BBox { double minLng = 0, minLat = 0, maxLng = 0, maxLat = 0; };

// A single ring of a polygon overlay, in lon/lat degrees.
struct PolygonRing { std::vector<LatLng> points; };

struct Marker { std::uint32_t id = 0; double lat = 0, lng = 0; };

// Longitude (deg) -> Mercator X (metres).
inline double lngToWorldX(double lng) {
  return lng / 360.0 * kEarthCircumference;
}

// Latitude (deg) -> Mercator Y (metres). Clamped to the Mercator latitude limit.
inline double latToWorldY(double lat) {
  if (lat >  kMercatorLatLimit) lat =  kMercatorLatLimit;
  if (lat < -kMercatorLatLimit) lat = -kMercatorLatLimit;
  double s = std::sin(radians(lat));
  return kEarthCircumference / (4.0 * kPi) * std::log((1.0 + s) / (1.0 - s));
}

inline Vec3d latLngToWorld(const LatLng& c, double elevation = 0.0) {
  return { lngToWorldX(c.lng), latToWorldY(c.lat), elevation };
}

} // namespace gv
