#ifndef TETRIS_CORE_COLOR_HPP_
#define TETRIS_CORE_COLOR_HPP_


namespace tetris {
namespace core {



struct color {

    constexpr color(int r, int g, int b): r(r), g(g), b(b) {}

    int r, g, b;


    static color const O;
    static color const I;
    static color const T;
    static color const L;
    static color const J;
    static color const S;
    static color const Z;
};


color const color::O(255, 219, 74);
color const color::I(5, 188, 242);
color const color::T(144, 42, 141);
color const color::L(227, 132, 28);
color const color::J(0, 80, 128);
color const color::S(102, 165, 57);
color const color::Z(207, 24, 31);



} // namespace core
} // namespace tetris


#endif // TETRIS_CORE_COLOR_HPP_
