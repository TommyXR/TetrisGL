#ifndef TETRIS_CORE_TETRIMINO_HPP_
#define TETRIS_CORE_TETRIMINO_HPP_


#include <cstdint>
#include <vector>
#include <array>


namespace tetris {
namespace core {


class tetrimino {

  public:
    enum class tetrimino_t : std::uint8_t { I, J, L, O, S, T, Z };
    enum class rotation_direction : bool { clockwise, counterclockwise };

    struct color_t {
        float r, g, b;
    };
    struct position_t {
        int i, j;
    };

    using rotation_t = std::vector<std::vector<bool>>;
    using rotation_array = std::array<rotation_t, 4>;


    tetrimino(tetrimino_t);

    void rotate(rotation_direction) noexcept;


    tetrimino_t type;
    color_t color;
    position_t position;

    rotation_array::const_iterator current_rotation;


  private:
    rotation_array rotations;


}; // namespace tetris


} // namespace core
} // namespace tetris


#endif // TETRIS_CORE_TETRIMINO_HPP_
