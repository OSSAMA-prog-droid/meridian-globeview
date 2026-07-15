#pragma once
// Thin OpenGL surface. Only the entry points the renderer actually uses are
// declared here. With GLOBEVIEW_STUB_GL (default) they resolve to no-op stubs so
// the project builds and runs its logic offline; define GLOBEVIEW_STUB_GL=0 and
// link a real loader (GLAD/GLEW) for a GPU-backed client.

#include <cstdint>
#include <cstddef>

using GLuint     = unsigned int;
using GLint      = int;
using GLenum     = unsigned int;
using GLsizei    = int;
using GLfloat    = float;
using GLboolean  = unsigned char;
using GLintptr   = std::ptrdiff_t;
using GLsizeiptr = std::ptrdiff_t;

// Enums (values match real GL).
constexpr GLenum GL_TEXTURE_2D        = 0x0DE1;
constexpr GLenum GL_TEXTURE_MIN_FILTER= 0x2801;
constexpr GLenum GL_TEXTURE_MAG_FILTER= 0x2800;
constexpr GLenum GL_LINEAR            = 0x2601;
constexpr GLenum GL_RGBA              = 0x1908;
constexpr GLenum GL_BGRA              = 0x80E1;
constexpr GLenum GL_RGBA8             = 0x8058;
constexpr GLenum GL_SRGB8_ALPHA8      = 0x8C43;
constexpr GLenum GL_UNSIGNED_BYTE     = 0x1401;
constexpr GLenum GL_FLOAT             = 0x1406;
constexpr GLenum GL_TRIANGLES         = 0x0004;
constexpr GLenum GL_ARRAY_BUFFER      = 0x8892;
constexpr GLenum GL_ELEMENT_ARRAY_BUFFER = 0x8893;
constexpr GLenum GL_STATIC_DRAW       = 0x88E4;
constexpr GLenum GL_DYNAMIC_DRAW      = 0x88E8;
constexpr GLenum GL_DEPTH_TEST        = 0x0B71;
constexpr GLenum GL_LEQUAL            = 0x0203;
constexpr GLenum GL_GEQUAL            = 0x0206;
constexpr GLenum GL_FRAMEBUFFER_SRGB  = 0x8DB9;

#if defined(GLOBEVIEW_STUB_GL) && GLOBEVIEW_STUB_GL
// No-op stubs: enough for the logic to run without a driver.
inline void   glGenTextures(GLsizei, GLuint* t) { static GLuint n = 1; if (t) *t = n++; }
inline void   glBindTexture(GLenum, GLuint) {}
inline void   glTexParameteri(GLenum, GLenum, GLint) {}
inline void   glTexImage2D(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*) {}
inline void   glDeleteTextures(GLsizei, const GLuint*) {}
inline void   glGenBuffers(GLsizei, GLuint* b) { static GLuint n = 1; if (b) *b = n++; }
inline void   glBindBuffer(GLenum, GLuint) {}
inline void   glBufferData(GLenum, GLsizeiptr, const void*, GLenum) {}
inline void   glBufferSubData(GLenum, GLintptr, GLsizeiptr, const void*) {}
inline void   glDeleteBuffers(GLsizei, const GLuint*) {}
inline void   glDrawArrays(GLenum, GLint, GLsizei) {}
inline void   glDrawElements(GLenum, GLsizei, GLenum, const void*) {}
inline void   glUseProgram(GLuint) {}
inline void   glUniformMatrix4fv(GLint, GLsizei, GLboolean, const GLfloat*) {}
inline void   glUniform1i(GLint, GLint) {}
inline void   glEnable(GLenum) {}
inline void   glDisable(GLenum) {}
inline void   glDepthFunc(GLenum) {}
inline void   glClearDepthf(GLfloat) {}
inline void   glFinish() {}
#else
extern "C" {
  void glGenTextures(GLsizei, GLuint*);
  void glBindTexture(GLenum, GLuint);
  void glTexParameteri(GLenum, GLenum, GLint);
  void glTexImage2D(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
  void glDeleteTextures(GLsizei, const GLuint*);
  void glGenBuffers(GLsizei, GLuint*);
  void glBindBuffer(GLenum, GLuint);
  void glBufferData(GLenum, GLsizeiptr, const void*, GLenum);
  void glBufferSubData(GLenum, GLintptr, GLsizeiptr, const void*);
  void glDeleteBuffers(GLsizei, const GLuint*);
  void glDrawArrays(GLenum, GLint, GLsizei);
  void glDrawElements(GLenum, GLsizei, GLenum, const void*);
  void glUseProgram(GLuint);
  void glUniformMatrix4fv(GLint, GLsizei, GLboolean, const GLfloat*);
  void glUniform1i(GLint, GLint);
  void glEnable(GLenum);
  void glDisable(GLenum);
  void glDepthFunc(GLenum);
  void glClearDepthf(GLfloat);
  void glFinish();
}
#endif

namespace gv {

// RAII wrapper for a GL texture handle — deletes on destruction, move-only.
// Available for correct resource management; not every call site uses it yet.
class GlTexture {
public:
  GlTexture() = default;
  explicit GlTexture(GLuint id) : id_(id) {}
  ~GlTexture() { reset(); }
  GlTexture(GlTexture&& o) noexcept : id_(o.id_) { o.id_ = 0; }
  GlTexture& operator=(GlTexture&& o) noexcept {
    if (this != &o) { reset(); id_ = o.id_; o.id_ = 0; }
    return *this;
  }
  GlTexture(const GlTexture&) = delete;
  GlTexture& operator=(const GlTexture&) = delete;

  GLuint get() const { return id_; }
  void reset() { if (id_) { glDeleteTextures(1, &id_); id_ = 0; } }

private:
  GLuint id_ = 0;
};

} // namespace gv
