#include "engine/tetrimino_generator.hpp"

#include <algorithm>


namespace tetris {
namespace engine {


using namespace tetris::core;


tetrimino_generator::tetrimino_generator(int seed):
    rng(seed), tetrimino_array{//
                     tetrimino::tetrimino_t::I, tetrimino::tetrimino_t::J,
                     tetrimino::tetrimino_t::L, tetrimino::tetrimino_t::O,
                     tetrimino::tetrimino_t::S, tetrimino::tetrimino_t::T,
                     tetrimino::tetrimino_t::Z} {}

std::array<tetrimino::tetrimino_t, 7> tetrimino_generator::generate() {

    std::shuffle(tetrimino_array.begin(), tetrimino_array.end(), rng);

    return tetrimino_array;
}



} // namespace engine
} // namespace tetris
