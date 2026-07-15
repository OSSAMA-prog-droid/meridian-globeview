#include "render/Camera.h"
#include "render/DepthConfig.h"

#include <cmath>

namespace gv {

void Camera::setViewport(int width, int height) {
  width_ = width;
  height_ = height;
}

void Camera::setTarget(const LatLng& target, double distanceMeters) {
  target_ = target;
  distance_ = distanceMeters;
  recomputeEye();
}

void Camera::applyDragRotation(double deltaXDeg, double deltaYDeg) {
  yawDeg_   += deltaXDeg;
  pitchDeg_ += deltaYDeg;
  if (pitchDeg_ > 89.0) pitchDeg_ = 89.0;
  if (pitchDeg_ <  5.0) pitchDeg_ =  5.0;
  recomputeEye();
}

void Camera::recomputeEye() {
  centerWorld_ = latLngToWorld(target_);

  // Place the eye on an orbit around the target using the current yaw and pitch.
  double cy = std::cos(yawDeg_);
  double sy = std::sin(yawDeg_);
  double cp = std::cos(pitchDeg_);
  double sp = std::sin(pitchDeg_);

  Vec3d dir{ cp * sy, sp, cp * cy };
  eye_ = { centerWorld_.x + dir.x * distance_,
           centerWorld_.y + dir.y * distance_,
           centerWorld_.z + dir.z * distance_ };
}

Mat4f Camera::viewMatrix() const {
  // View transform for the current eye, in world space.
  Vec3f eye    = eye_.toFloat();
  Vec3f center = centerWorld_.toFloat();
  Vec3f up{ 0.0f, 1.0f, 0.0f };
  return lookAt(eye, center, up);
}

Mat4f Camera::projectionMatrix() const {
  float aspect = height_ > 0 ? static_cast<float>(width_) / static_cast<float>(height_) : 1.0f;
  return perspective(radiansf(60.0f), aspect, kNearPlane, kFarPlane);
}

} // namespace gv
