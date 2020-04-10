#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <cstdint>
#include <filesystem>


class shader {

  public:
    enum class shader_t : std::uint8_t { vertex, fragment, geometry };

    friend class shader_program;

    shader() = delete;
    ~shader();
    shader(std::filesystem::path, shader_t);

    shader_t type;

    // private:
    void do_compile() const;
    void do_check_compile_error() const;

    unsigned int id;
};

#endif // SHADER_HPP_
