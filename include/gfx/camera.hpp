#ifndef TETRIS_GFX_CAMERA_HPP_
#define TETRIS_GFX_CAMERA_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tetris {
namespace gfx {



class camera {
  public:
    camera(glm::vec3 p, glm::vec3 la, glm::vec3 u): position(p), look_at(la), up(u) {}

    glm::mat4 get_view_matrix() const {
        return glm::lookAt(position, look_at, up);
    }

  private:
    glm::vec3 position;
    glm::vec3 look_at;
    glm::vec3 up;
};



} // namespace gfx
} // namespace tetris

#endif // TETRIS_GFX_CAMERA_HPP_
