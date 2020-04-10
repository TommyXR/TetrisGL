#ifndef TETRIS_ENGINE_TETRIMINO_HPP_
#define TETRIS_ENGINE_TETRIMINO_HPP_


#include <cstdint>
#include <vector>
#include <memory>
#include <array>

#include "core/color_t.hpp"
#include "core/position_t.hpp"
#include "core/rotation.hpp"



namespace tetris {
namespace engine {



class tetrimino {

  public:
    enum class tetrimino_t : std::uint8_t { I, J, L, O, S, T, Z };
    using rotation_array = std::array<core::rotation, 4>;
    using pointer = std::unique_ptr<tetrimino>;


    tetrimino(tetrimino_t);


    void rotate(core::rotation::direction) noexcept;
    void fall() noexcept;


    tetrimino_t type;
    core::color_t color{0, 0, 0};
    core::position_t position{0, 0};

    rotation_array::const_iterator current_rotation;


  private:
    rotation_array rotations;
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_TETRIMINO_HPP_
