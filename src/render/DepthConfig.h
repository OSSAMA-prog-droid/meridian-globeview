#pragma once
// Depth range and projection for the globe view. The scene is drawn from just in
// front of the vehicle all the way out to the horizon, so the depth range is wide.

#include "globeview/Math.h"

namespace gv {

// Visible range, in metres: from right in front of the camera to the horizon.
constexpr float kNearPlane = 0.1f;
constexpr float kFarPlane  = 2000000.0f;

// Standard perspective projection into the default GL clip space (depth -1..1).
inline Mat4f perspective(float fovYRadians, float aspect, float nearZ, float farZ) {
  float f = 1.0f / std::tan(fovYRadians * 0.5f);
  Mat4f p;
  for (int i = 0; i < 16; ++i) p.m[i] = 0.0f;
  p.m[0]  = f / aspect;
  p.m[5]  = f;
  p.m[10] = (farZ + nearZ) / (nearZ - farZ);
  p.m[11] = -1.0f;
  p.m[14] = (2.0f * farZ * nearZ) / (nearZ - farZ);
  return p;
}

} // namespace gv
