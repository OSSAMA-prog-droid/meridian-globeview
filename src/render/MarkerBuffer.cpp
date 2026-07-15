#include "render/MarkerBuffer.h"

namespace gv {

MarkerBuffer::~MarkerBuffer() {
  if (vbo_) glDeleteBuffers(1, &vbo_);
}

void MarkerBuffer::init(std::size_t capacity) {
  capacity_ = capacity;
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(capacity * 3 * sizeof(float)),
               nullptr, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MarkerBuffer::updatePositions(const std::vector<Marker>& markers) {
  std::vector<float> data;
  data.reserve(markers.size() * 3);
  for (const auto& m : markers) {
    Vec3d w = latLngToWorld({ m.lat, m.lng });
    data.push_back(static_cast<float>(w.x));
    data.push_back(static_cast<float>(w.y));
    data.push_back(static_cast<float>(w.z));
  }

  // Push the fresh positions into the buffer the renderer draws from.
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferSubData(GL_ARRAY_BUFFER, 0,
                  static_cast<GLsizeiptr>(data.size() * sizeof(float)),
                  data.data());
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  count_ = static_cast<int>(markers.size());
}

void MarkerBuffer::draw() {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glDrawArrays(GL_TRIANGLES, 0, count_);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace gv
