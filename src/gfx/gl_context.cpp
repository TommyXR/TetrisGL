#include "gfx/gl_context.hpp"

#include <stdexcept>

#include "glad/glad.h"
#include "gfx/render_window.hpp"


namespace tetris {
namespace gfx {



gl_context::gl_context(version gl_version): gl_version(gl_version) {}

void gl_context::link(render_window&) const {

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("gl_context::link: Failed to initialize GLAD");
    }
}


} // namespace gfx
} // namespace tetris
