#ifndef TETRIS_GFX_RENDERER_HPP_
#define TETRIS_GFX_RENDERER_HPP_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gfx/camera.hpp"
#include "gfx/shader.hpp"
#include "gfx/shader_program.hpp"


namespace tetris {
namespace engine {

class game;
class tetrimino;

} // namespace engine
namespace gfx {


class gl_context;
class render_window;
class renderer;


struct vertex_t {
    float x, y, z;
    float normal_x, normal_y, normal_z;
};


// This is a specialized class whose only role is to
// draw cubes on the screen.
class cube_renderer {
  public:
    cube_renderer(gfx::renderer&);
    void render(glm::vec3 const&, glm::vec3 const&);

  private:
    shader_program cube_shader;

    std::array<vertex_t, 36> vertices;
    unsigned int vao_idx;
    unsigned int vbo_idx;

    gfx::renderer& renderer;
};


// This is the main renderer class, which holds all the informations about
// the scene setup and is the only part of the public API.
class renderer {

  public:
    renderer(gl_context&, render_window&);

    friend class cube_renderer;

    void render(engine::game const&);

  private:
    void do_render_tetrimino(engine::tetrimino const&);

    gfx::camera camera;
    glm::mat4 const projection;

    gfx::cube_renderer cube_renderer;


    gl_context& context;
    render_window& window;
};



} // namespace gfx
} // namespace tetris

#endif // TETRIS_GFX_RENDERER_HPP_
