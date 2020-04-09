#include "gfx/gl_context.hpp"
#include "gfx/render_window.hpp"



int main() {
    using namespace tetris;

    gfx::gl_context context({4, 0});
    gfx::render_window window(context, {800, 600, "Tetris"});



    return 0;
}
