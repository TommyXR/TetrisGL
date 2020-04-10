#include "gfx/shader.hpp"

#include <fstream>
#include <array>
#include <string>

#include <glbinding/gl/gl.h>

namespace fs = std::filesystem;

shader::shader(fs::path file_path, shader_t shader_type): type(shader_type) {
    std::ifstream file(file_path);

    std::string file_content(std::istreambuf_iterator<char>(file), {});

    // This will get destroyed by file_content, but glShaderSource copies
    // it so it's fine.
    char const* raw{file_content.c_str()};

    switch (type) {
        case shader_t::vertex: id = gl::glCreateShader(gl::GL_VERTEX_SHADER); break;
        case shader_t::fragment: id = gl::glCreateShader(gl::GL_FRAGMENT_SHADER); break;
        case shader_t::geometry: id = gl::glCreateShader(gl::GL_GEOMETRY_SHADER); break;
    }

    gl::glShaderSource(id, 1, &raw, nullptr);
}


shader::~shader() {
    gl::glDeleteShader(id);
}

void shader::do_compile() const {
    gl::glCompileShader(id);
    do_check_compile_error();
}


void shader::do_check_compile_error() const {
    int success{0};

    gl::glGetShaderiv(id, gl::GL_COMPILE_STATUS, &success);

    if (!success) {

        int log_size{0};
        std::array<char, 1024> log;
        gl::glGetShaderInfoLog(id, 1024, &log_size, &log[0]);


        throw std::runtime_error("shader::do_compile: could not compile shader: "
              + std::string(log.cbegin(), log.cbegin() + log_size));
    }
}
