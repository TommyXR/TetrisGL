#ifndef TETRIS_ENGINE_MINO_HPP_
#define TETRIS_ENGINE_MINO_HPP_


#include "core/color_t.hpp"
#include "engine/tetrimino.hpp"


namespace tetris {
namespace engine {



struct mino {

    mino(tetrimino const& t): color(t.color) {}

    core::color_t color;
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_MINO_HPP_
