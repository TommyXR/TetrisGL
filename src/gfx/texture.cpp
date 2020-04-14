#include "gfx/texture.hpp"


#include <iostream>
#include <string>
#include <fstream>
#include <glbinding/gl/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


namespace fs = std::filesystem;

namespace tetris {
namespace gfx {


texture2d::texture2d(fs::path file) {

    int w, h, channels;
    auto data{stbi_load(file.c_str(), &w, &h, &channels, 0)};



    width = w;
    height = h;

    gl::glGenTextures(1, &id);

    gl::glBindTexture(gl::GL_TEXTURE_2D, id);

    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_S, gl::GL_REPEAT);
    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_T, gl::GL_REPEAT);

    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);
    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);


    gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, gl::GL_RGBA, width, height, 0, gl::GL_RGBA,
          gl::GL_UNSIGNED_BYTE, data);


    stbi_image_free(data);
    gl::glBindTexture(gl::GL_TEXTURE_2D, 0);
}


void texture2d::use() const {
    gl::glBindTexture(gl::GL_TEXTURE_2D, id);
}


} // namespace gfx
} // namespace tetris
