#ifndef TETRIS_ENGINE_TETRIMINO_GENERATOR_HPP_
#define TETRIS_ENGINE_TETRIMINO_GENERATOR_HPP_

#include <array>
#include <random>
#include <chrono>

#include "engine/tetrimino.hpp"


namespace tetris {
namespace engine {



class tetrimino_generator {

  public:
    tetrimino_generator(int = std::chrono::steady_clock::now().time_since_epoch().count());

    std::array<tetrimino::tetrimino_t, 7> generate();

  private:
    std::mt19937 rng;
    std::array<tetrimino::tetrimino_t, 7> tetrimino_array;
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_TETRIMINO_GENERATOR_HPP_
