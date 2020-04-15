#include "gfx/shader_program.hpp"

#include <array>
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>


shader_program::shader_program(): id(glCreateProgram()) {}

shader_program::~shader_program() {
    glDeleteProgram(id);
}


void shader_program::use() const {
    glUseProgram(id);
}


void shader_program::add_shader(shader& to_add) {
    shaders.insert_or_assign(to_add.type, to_add);
}


void shader_program::compile() const {
    for (auto& [type, shader]: shaders) {
        shader.do_compile();
        glAttachShader(id, shader.id);
    }

    glLinkProgram(id);
    do_check_linking_error();

    for (auto const& [type, shader]: shaders) {
        glDetachShader(id, shader.id);
        glDeleteShader(shader.id);
    }
}


void shader_program::do_check_linking_error() const {
    int success;

    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        std::array<char, 512> log;
        int log_size{0};
        glGetProgramInfoLog(id, 512, &log_size, &log[0]);
        throw std::runtime_error("shader_program::compile: could not link shader: "
              + std::string(log.cbegin(), log.cbegin() + log_size));
    }
}


void shader_program::set_uniform(std::string_view name, bool const value) const {
    glUniform1i(glGetUniformLocation(id, name.data()), value);
}

void shader_program::set_uniform(std::string_view name, int const value) const {
    glUniform1i(glGetUniformLocation(id, name.data()), value);
}

void shader_program::set_uniform(std::string_view name, float const value) const {
    glUniform1f(glGetUniformLocation(id, name.data()), value);
}

void shader_program::set_uniform(std::string_view name, glm::vec2 const& value) const {
    glUniform2f(glGetUniformLocation(id, name.data()), value.x, value.y);
}

void shader_program::set_uniform(std::string_view name, glm::vec3 const& value) const {
    glUniform3fv(glGetUniformLocation(id, name.data()), 1, glm::value_ptr(value));
}

void shader_program::set_uniform(std::string_view name, glm::mat3 const& value) const {
    glUniformMatrix3fv(glGetUniformLocation(id, name.data()), 1, false, glm::value_ptr(value));
}

void shader_program::set_uniform(std::string_view name, glm::mat4 const& value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.data()), 1, GL_FALSE, glm::value_ptr(value));
}
