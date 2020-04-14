#include "gfx/renderer.hpp"

#include <glbinding/gl/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include "gfx/render_window.hpp"
#include "gfx/gl_context.hpp"
#include "engine/game.hpp"

#include <iostream>

namespace tetris {
namespace gfx {



cube_renderer::cube_renderer(gfx::renderer& r): renderer(r) {

    vertices = {{
          {-0.5f, -0.5f, -0.5f, 0, 0, -1}, // Front face
          {0.5f, -0.5f, -0.5f, 0, 0, -1},  //
          {0.5f, 0.5f, -0.5f, 0, 0, -1},   //
          {0.5f, 0.5f, -0.5f, 0, 0, -1},   //
          {-0.5f, 0.5f, -0.5f, 0, 0, -1},  //
          {-0.5f, -0.5f, -0.5f, 0, 0, -1}, //

          {-0.5f, -0.5f, 0.5f, 0, 0, 1}, // Back face
          {0.5f, -0.5f, 0.5f, 0, 0, 1},  //
          {0.5f, 0.5f, 0.5f, 0, 0, 1},   //
          {0.5f, 0.5f, 0.5f, 0, 0, 1},   //
          {-0.5f, 0.5f, 0.5f, 0, 0, 1},  //
          {-0.5f, -0.5f, 0.5f, 0, 0, 1}, //

          {-0.5f, 0.5f, 0.5f, -1, 0, 0},   // left face
          {-0.5f, 0.5f, -0.5f, -1, 0, 0},  //
          {-0.5f, -0.5f, -0.5f, -1, 0, 0}, //
          {-0.5f, -0.5f, -0.5f, -1, 0, 0}, //
          {-0.5f, -0.5f, 0.5f, -1, 0, 0},  //
          {-0.5f, 0.5f, 0.5f, -1, 0, 0},   //

          {0.5f, 0.5f, 0.5f, 1, 0, 0},   // right face
          {0.5f, 0.5f, -0.5f, 1, 0, 0},  //
          {0.5f, -0.5f, -0.5f, 1, 0, 0}, //
          {0.5f, -0.5f, -0.5f, 1, 0, 0}, //
          {0.5f, -0.5f, 0.5f, 1, 0, 0},  //
          {0.5f, 0.5f, 0.5f, 1, 0, 0},   //

          {-0.5f, -0.5f, -0.5f, 0, -1, 0}, // Bottom face
          {0.5f, -0.5f, -0.5f, 0, -1, 0},  //
          {0.5f, -0.5f, 0.5f, 0, -1, 0},   //
          {0.5f, -0.5f, 0.5f, 0, -1, 0},   //
          {-0.5f, -0.5f, 0.5f, 0, -1, 0},  //
          {-0.5f, -0.5f, -0.5f, 0, -1, 0}, //

          {-0.5f, 0.5f, -0.5f, 0, 1, 0}, // top face
          {0.5f, 0.5f, -0.5f, 0, 1, 0},  //
          {0.5f, 0.5f, 0.5f, 0, 1, 0},   //
          {0.5f, 0.5f, 0.5f, 0, 1, 0},   //
          {-0.5f, 0.5f, 0.5f, 0, 1, 0},  //
          {-0.5f, 0.5f, -0.5f, 0, 1, 0}  //

    }};

    // We generate the gpu buffer for the cube vertices.

    gl::glGenVertexArrays(1, &vao_idx);
    gl::glGenBuffers(1, &vbo_idx);

    gl::glBindVertexArray(vao_idx);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo_idx);

    gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(vertex_t) * vertices.size(), vertices.data(),
          gl::GL_STATIC_DRAW);

    // position attribute
    gl::glVertexAttribPointer(
          0, 3, gl::GL_FLOAT, false, 6 * sizeof(float), reinterpret_cast<void*>(0));
    gl::glEnableVertexAttribArray(0);

    // normal attribute
    gl::glVertexAttribPointer(
          1, 3, gl::GL_FLOAT, false, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));

    gl::glEnableVertexAttribArray(1);

    // unbind the buffers
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
    gl::glBindVertexArray(0);


    // Finally, create the shader and prepare it.
    shader cube_vs("resources/shaders/cube.vs.glsl", shader::shader_t::vertex);
    shader cube_fs("resources/shaders/cube.fs.glsl", shader::shader_t::fragment);

    cube_shader.add_shader(cube_vs);
    cube_shader.add_shader(cube_fs);
    cube_shader.compile();

    cube_shader.use();
    cube_shader.set_uniform("projection", renderer.projection);
}


void cube_renderer::render(
      glm::vec3 const& position, glm::vec3 const& color, gl::GLenum type) const {
    cube_shader.use();

    glm::mat4 model(1.f);
    model = glm::translate(model, position);

    cube_shader.set_uniform("model", model);
    cube_shader.set_uniform("color", color);
    cube_shader.set_uniform("view", renderer.camera.get_view_matrix());


    gl::glBindVertexArray(vao_idx);
    gl::glDrawArrays(type, 0, 36);
}



frame_renderer::frame_renderer(gfx::renderer& r):
    texture("resources/images/frame.png"), renderer(r) {

    // Manually adjusted vertices, TODO rework the whole rendering
    // system
    vertices = {{
          {6, 12, -30, 1, 0, 0},
          {-7.2, 12, -30, 0, 0, 0},
          {-7.2, -13, -30, 0, 1, 0},
          {6, 12, -30, 1, 0, 0},
          {-7.2, -13, -30, 0, 1, 0},
          {6, -13, -30, 1, 1, 0},
    }};

    // We generate the gpu buffer for the cube vertices.

    gl::glGenVertexArrays(1, &vao_idx);
    gl::glGenBuffers(1, &vbo_idx);

    gl::glBindVertexArray(vao_idx);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo_idx);

    gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(vertex_t) * vertices.size(), vertices.data(),
          gl::GL_STATIC_DRAW);

    // position attribute
    gl::glVertexAttribPointer(
          0, 3, gl::GL_FLOAT, false, 6 * sizeof(float), reinterpret_cast<void*>(0));
    gl::glEnableVertexAttribArray(0);

    // normal attribute
    gl::glVertexAttribPointer(
          1, 3, gl::GL_FLOAT, false, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));

    gl::glEnableVertexAttribArray(1);

    // unbind the buffers
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
    gl::glBindVertexArray(0);


    // Finally, create the shader and prepare it.
    shader vs("resources/shaders/frame.vs.glsl", shader::shader_t::vertex);
    shader fs("resources/shaders/frame.fs.glsl", shader::shader_t::fragment);

    frame_shader.add_shader(vs);
    frame_shader.add_shader(fs);
    frame_shader.compile();

    frame_shader.use();
    frame_shader.set_uniform("projection", renderer.projection);
}


void frame_renderer::render() const {

    frame_shader.use();
    texture.use();

    frame_shader.set_uniform("view", renderer.camera.get_view_matrix());

    gl::glBindVertexArray(vao_idx);
    gl::glDrawArrays(gl::GL_TRIANGLES, 0, 6);


    gl::glBindVertexArray(0);
}



renderer::renderer(gl_context& c, render_window& w):
    camera({0, 0, 0}, {0, 0, -1}, {0, 1, 0}),
    projection(glm::perspective(
          glm::radians(65.f), static_cast<float>(w.width) / w.height, 0.1f, 100.f)),
    cube_renderer(*this), frame_renderer(*this), context(c), window(w) {}


void renderer::render(engine::game const& game) {
    context.clear_buffers();

    frame_renderer.render();

    for (int i{23}; i >= 4; --i) {
        for (int j{0}; j < 10; ++j) {

            if (auto mino{game.grid.data[i][j]}; mino) {
                cube_renderer.render(
                      {j - 5, 13 - i, -25}, {mino->color.r, mino->color.g, mino->color.b});
            }
        }
    }

    if (auto& t{game.current_tetrimino}; t) {

        for (int i = static_cast<int>(t->current_rotation->data.size()) - 1; i >= 0; --i) {
            for (int j = 0; j < static_cast<int>(t->current_rotation->data[0].size()); ++j) {

                if (auto mino{t->current_rotation->data[i][j]}; mino && i + t->position.i > 2) {

                    cube_renderer.render({t->position.j + j - 5, 13 - i - t->position.i, -25},
                          {t->color.r, t->color.g, t->color.b});
                }
            }
        }

        engine::tetrimino ghost(*t);
        while (game.can_fall(ghost)) {
            ++ghost.position.i;
        }

        for (int i = static_cast<int>(ghost.current_rotation->data.size()) - 1; i >= 0; --i) {
            for (int j = 0; j < static_cast<int>(ghost.current_rotation->data[0].size()); ++j) {

                if (auto mino{ghost.current_rotation->data[i][j]};
                      mino && i + ghost.position.i > 2) {

                    cube_renderer.render({ghost.position.j + j - 5, 13 - i - ghost.position.i, -25},
                          {ghost.color.r, ghost.color.g, ghost.color.b}, gl::GL_LINE_STRIP);
                }
            }
        }
    }

    window.swap_buffers();
}



} // namespace gfx
} // namespace tetris
