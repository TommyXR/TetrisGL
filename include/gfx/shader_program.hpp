#ifndef SHADER_PROGRAM_HPP_
#define SHADER_PROGRAM_HPP_

#include <string_view>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "gfx/shader.hpp"



class shader_program {

  public:
    shader_program();
    ~shader_program();

    void use() const;
    void add_shader(shader&);
    void compile() const;

    void set_uniform(std::string_view, bool const) const;
    void set_uniform(std::string_view, int const) const;
    void set_uniform(std::string_view, float const) const;
    void set_uniform(std::string_view, glm::vec2 const&) const;
    void set_uniform(std::string_view, glm::vec3 const&) const;
    void set_uniform(std::string_view, glm::vec4 const&) const;
    void set_uniform(std::string_view, glm::mat3 const&) const;
    void set_uniform(std::string_view, glm::mat4 const&) const;


  private:
    void do_check_linking_error() const;
    unsigned int id;
    std::unordered_map<shader::shader_t, shader> shaders;
};



#endif // SHADER_PROGRAM_HPP_
