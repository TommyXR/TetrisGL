#ifndef TETRIS_GFX_RENDERER_HPP_
#define TETRIS_GFX_RENDERER_HPP_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



namespace tetris {
namespace engine {

class game;

} // namespace engine
namespace gfx {


class gl_context;
class render_window;

class renderer {

  public:
    renderer(gl_context&, render_window&);

    void render(engine::game const&);

  private:
    glm::mat4 projection;

    gl_context& context;
    render_window& window;
};



} // namespace gfx
} // namespace tetris

#endif // TETRIS_GFX_RENDERER_HPP_
