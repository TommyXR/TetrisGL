#include "gfx/render_window.hpp"

#include <stdexcept>
#include <glbinding/gl/gl.h>

#include "gfx/gl_context.hpp"



namespace tetris {
namespace gfx {



render_window::render_window(gl_context const& context, properties p) {

    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context.gl_version.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context.gl_version.minor);
    glfwWindowHint(GLFW_RESIZABLE, false);

    window_impl =
          glfw_pointer(glfwCreateWindow(p.width, p.height, p.name.c_str(), nullptr, nullptr));

    glfwSetFramebufferSizeCallback(window_impl.get(),
          [](auto, auto width, auto height) { gl::glViewport(0, 0, width, height); });

    gl::glViewport(0, 0, p.height, p.width);
}

render_window::~render_window() {
    glfwTerminate();
}



} // namespace gfx
} // namespace tetris