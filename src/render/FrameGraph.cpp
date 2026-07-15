#include "render/FrameGraph.h"

namespace gv {

void FrameGraph::ensureBuffer() {
  if (!scratchVbo_) glGenBuffers(1, &scratchVbo_);
}

void FrameGraph::renderOverlays(const std::vector<OverlayDraw>& overlays) {
  ensureBuffer();

  for (const auto& o : overlays) {
    glUseProgram(o.program);
    glBindBuffer(GL_ARRAY_BUFFER, scratchVbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(o.vertexData.size() * sizeof(float)),
                 o.vertexData.data(), GL_DYNAMIC_DRAW);
    glUniformMatrix4fv(0, 1, 0, o.transform.m);
    glDrawArrays(GL_TRIANGLES, 0, o.vertexCount);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace gv
