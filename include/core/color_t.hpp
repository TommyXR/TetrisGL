#ifndef TETRIS_CORE_COLOR_T_HPP_
#define TETRIS_CORE_COLOR_T_HPP_


namespace tetris {
namespace core {



struct color_t {

    color_t(float r, float g, float b): r(r), g(g), b(b) {}

    float r, g, b;
};



} // namespace core
} // namespace tetris


#endif // TETRIS_CORE_COLOR_T_HPP_
