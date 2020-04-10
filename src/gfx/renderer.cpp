#include "gfx/renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "gfx/render_window.hpp"
#include "gfx/gl_context.hpp"


namespace tetris {
namespace gfx {



renderer::renderer(gl_context& c, render_window& w):
    projection(glm::perspective(
          glm::radians(45.f), static_cast<float>(w.width) / w.height, 0.1f, 100.f)),
    context(c), window(w) {}


void renderer::render(engine::game const&) {
    context.clear_buffers();



    window.swap_buffers();
}



} // namespace gfx
} // namespace tetris
