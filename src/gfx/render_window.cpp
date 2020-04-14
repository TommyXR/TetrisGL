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

    glfwMakeContextCurrent(window_impl.get());

    gl::glEnable(gl::GL_DEPTH_TEST);
    // gl::glEnable(gl::GL_CULL_FACE);
    gl::glEnable(gl::GL_BLEND);
    gl::glClearColor(0, 0, 0, 0);

    gl::glBlendFunc(gl::GL_SRC_ALPHA, gl::GL_ONE_MINUS_SRC_ALPHA);
}


render_window::~render_window() {
    glfwTerminate();
}



} // namespace gfx
} // namespace tetris