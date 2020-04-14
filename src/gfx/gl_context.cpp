#include "gfx/gl_context.hpp"

#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>


namespace tetris {
namespace gfx {



gl_context::gl_context(version gl_version): gl_version(gl_version) {
    glbinding::Binding::initialize();
}

void gl_context::clear_buffers() const noexcept {
    gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
}

} // namespace gfx
} // namespace tetris
