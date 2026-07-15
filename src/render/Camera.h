#pragma once
// Orbit camera over the globe. It looks at a geographic target from a given
// distance, and can be rotated by mouse drags.

#include "globeview/Math.h"
#include "globeview/Geo.h"

namespace gv {

class Camera {
public:
  void setViewport(int width, int height);
  void setTarget(const LatLng& target, double distanceMeters);

  // Rotate the view around the target. deltaX / deltaY come from a mouse drag,
  // expressed in degrees.
  void applyDragRotation(double deltaXDeg, double deltaYDeg);

  Mat4f viewMatrix() const;
  Mat4f projectionMatrix() const;

  Vec3d eyeWorld() const { return eye_; }

private:
  void recomputeEye();

  LatLng target_{};
  double distance_  = 1000.0;
  double yawDeg_    = 0.0;
  double pitchDeg_  = 45.0;
  int    width_     = 1280;
  int    height_    = 720;
  Vec3d  eye_{};          // camera position, world metres
  Vec3d  centerWorld_{};  // look-at target, world metres
};

} // namespace gv
