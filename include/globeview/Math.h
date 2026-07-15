#pragma once
// Minimal vector/matrix math for the renderer. Single- and double-precision
// vectors are deliberately distinct types so precision choices are explicit at
// call sites (this matters a lot at planet scale).

#include <cmath>

namespace gv {

constexpr double kPi = 3.14159265358979323846;

inline double radians(double deg) { return deg * (kPi / 180.0); }
inline double degrees(double rad) { return rad * (180.0 / kPi); }
inline float  radiansf(float deg) { return deg * (float)(kPi / 180.0); }

struct Vec2f { float x = 0, y = 0; };

struct Vec3f {
  float x = 0, y = 0, z = 0;
  Vec3f() = default;
  Vec3f(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
  Vec3f operator-(const Vec3f& o) const { return {x - o.x, y - o.y, z - o.z}; }
  Vec3f operator+(const Vec3f& o) const { return {x + o.x, y + o.y, z + o.z}; }
};

struct Vec3d {
  double x = 0, y = 0, z = 0;
  Vec3d() = default;
  Vec3d(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
  Vec3d operator-(const Vec3d& o) const { return {x - o.x, y - o.y, z - o.z}; }
  Vec3d operator+(const Vec3d& o) const { return {x + o.x, y + o.y, z + o.z}; }
  Vec3f toFloat() const { return {(float)x, (float)y, (float)z}; }
};

inline float  dot(const Vec3f& a, const Vec3f& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
inline Vec3f  cross(const Vec3f& a, const Vec3f& b) {
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}
inline Vec3f  normalize(const Vec3f& v) {
  float len = std::sqrt(dot(v, v));
  return len > 0 ? Vec3f{v.x/len, v.y/len, v.z/len} : v;
}

// Column-major 4x4, GL-style.
struct Mat4f {
  float m[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

  static Mat4f identity() { return Mat4f{}; }

  Mat4f operator*(const Mat4f& b) const {
    Mat4f r;
    for (int c = 0; c < 4; ++c)
      for (int row = 0; row < 4; ++row) {
        float s = 0;
        for (int k = 0; k < 4; ++k) s += m[k*4 + row] * b.m[c*4 + k];
        r.m[c*4 + row] = s;
      }
    return r;
  }
};

// Right-handed look-at built from a forward/up basis (float precision).
inline Mat4f lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up) {
  Vec3f f = normalize(center - eye);
  Vec3f s = normalize(cross(f, up));
  Vec3f u = cross(s, f);
  Mat4f r;
  r.m[0] = s.x; r.m[4] = s.y; r.m[8]  = s.z;
  r.m[1] = u.x; r.m[5] = u.y; r.m[9]  = u.z;
  r.m[2] = -f.x; r.m[6] = -f.y; r.m[10] = -f.z;
  r.m[12] = -dot(s, eye);
  r.m[13] = -dot(u, eye);
  r.m[14] =  dot(f, eye);
  return r;
}

} // namespace gv
