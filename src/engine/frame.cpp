#include "engine/frame.hpp"

#include <algorithm>
#include <cstdint>

#include <iostream>

#include "engine/tetrimino.hpp"


namespace tetris {
namespace engine {


using namespace tetris::core;


frame::frame() {

    // Tetris grid is 20x10, but 4 hidden rows for spawning blocks.
    for (int i{0}; i < 24; ++i) {
        data.emplace_back();
    }
}



} // namespace engine
} // namespace tetris
