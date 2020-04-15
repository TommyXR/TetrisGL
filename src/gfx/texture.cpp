#include "gfx/texture.hpp"


#include <iostream>
#include <string>
#include <fstream>

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


namespace fs = std::filesystem;

namespace tetris {
namespace gfx {


texture2d::texture2d(fs::path file) {

    int w, h, channels;
    auto data{stbi_load(file.c_str(), &w, &h, &channels, 0)};



    width = w;
    height = h;

    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void texture2d::use() const {
    glBindTexture(GL_TEXTURE_2D, id);
}


} // namespace gfx
} // namespace tetris
