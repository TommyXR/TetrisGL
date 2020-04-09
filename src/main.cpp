#include <cstdint>
#include <chrono>

#include "gfx/gl_context.hpp"
#include "gfx/render_window.hpp"
#include "core/color.hpp"



int main() {

    using namespace tetris;
    using namespace std::chrono_literals;
    namespace chrono = std::chrono;


    gfx::gl_context context({4, 0});
    gfx::render_window window(context, {800, 600, "Tetris"});



    return 0;
}
