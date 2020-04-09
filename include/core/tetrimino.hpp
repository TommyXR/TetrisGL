#ifndef TETRIS_CORE_TETRIMINO_HPP_
#define TETRIS_CORE_TETRIMINO_HPP_


#include <cstdint>
#include <vector>
#include <array>

#include "core/color_t.hpp"
#include "core/position_t.hpp"
#include "core/rotation.hpp"



namespace tetris {
namespace core {



class tetrimino {

  public:
    enum class tetrimino_t : std::uint8_t { I, J, L, O, S, T, Z };

    using rotation_array = std::array<rotation, 4>;


    tetrimino(tetrimino_t);

    void rotate(rotation::direction) noexcept;


    tetrimino_t type;
    color_t color{0, 0, 0};
    position_t position{0, 0};

    rotation_array::const_iterator current_rotation;


  private:
    rotation_array rotations;
};



} // namespace core
} // namespace tetris


#endif // TETRIS_CORE_TETRIMINO_HPP_
