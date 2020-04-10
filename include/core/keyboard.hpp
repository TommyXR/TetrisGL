#ifndef TETRIS_CORE_KEYBOARD_HPP_
#define TETRIS_CORE_KEYBOARD_HPP_


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gfx/render_window.hpp"


namespace tetris {
namespace core {



class keyboard {

  public:
    using key = unsigned int;

    keyboard(gfx::render_window& w): window_impl(w.window_impl.get()) {
        // glfwSetInputMode(window_impl, GLFW_STICKY_KEYS, true);
    }

    bool key_pressed(key k) const noexcept {
        auto state = glfwGetKey(window_impl, k);

        return state == GLFW_PRESS;
    }

    static key constexpr left{GLFW_KEY_LEFT};
    static key constexpr right{GLFW_KEY_RIGHT};
    static key constexpr up{GLFW_KEY_UP};
    static key constexpr down{GLFW_KEY_DOWN};
    static key constexpr space{GLFW_KEY_SPACE};

  private:
    GLFWwindow* window_impl;
};



} // namespace core
} // namespace tetris

#endif // TETRIS_CORE_KEYBOARD_HPP_