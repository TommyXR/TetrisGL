#ifndef TETRIS_GFX_RENDER_WINDOW_HPP_
#define TETRIS_GFX_RENDER_WINDOW_HPP_

#include <cstdint>
#include <string>
#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>



namespace tetris {
namespace gfx {


namespace priv {

// We need to provide this destroyer to the unique_ptr template,
// because GLFWwindow cannot be destroyed with `delete`.
struct glfw_window_destroyer {
    void operator()(GLFWwindow* w) noexcept {
        glfwDestroyWindow(w);
    }
};

} // namespace priv


class gl_context;


class render_window {

  public:
    struct properties {
        std::size_t height;
        std::size_t width;
        std::string name;
    };

    render_window(gl_context const&, properties);
    ~render_window();


    // Wrappers for GLFW

    inline bool should_close() const noexcept {
        return glfwWindowShouldClose(window_impl.get());
    }

    inline void swap_buffers() const noexcept {
        glfwSwapBuffers(window_impl.get());
    }

    inline void poll_events() const noexcept {
        glfwPollEvents();
    }


  private:
    using glfw_pointer = std::unique_ptr<GLFWwindow, priv::glfw_window_destroyer>;
    glfw_pointer window_impl;
};



} // namespace gfx
} // namespace tetris


#endif // TETRIS_GFX_RENDER_WINDOW_HPP_
