#ifndef TETRIS_GFX_TEXTURE_HPP_
#define TETRIS_GFX_TEXTURE_HPP_

#include <filesystem>

namespace tetris {
namespace gfx {



class texture2d {

  public:
    texture2d(std::filesystem::path);
    void use() const;



    unsigned int id;
    unsigned int width, height;
    unsigned int format;
};



} // namespace gfx
} // namespace tetris


#endif // TETRIS_GFX_TEXTURE_HPP_
