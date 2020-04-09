#ifndef TETRIS_GFX_GL_CONTEXT_HPP_
#define TETRIS_GFX_GL_CONTEXT_HPP_

#include <cstdint>


namespace tetris {
namespace gfx {



class gl_context {

  public:
    struct version {
        std::uint8_t major;
        std::uint8_t minor;
    };

    gl_context(version);

    void clear_buffers() const noexcept;

    version gl_version;
};



} // namespace gfx
} // namespace tetris


#endif // TETRIS_GFX_GL_CONTEXT_HPP_
