#ifndef TETRIS_CORE_ROTATION_HPP_
#define TETRIS_CORE_ROTATION_HPP_

#include <vector>
#include <cstdint>

namespace tetris {
namespace core {



struct rotation {
    enum class direction : bool { clockwise, counterclockwise };
    using data_t = std::vector<std::vector<bool>>;


    data_t data;
};



} // namespace core
} // namespace tetris


#endif // TETRIS_CORE_ROTATION_HPP_
