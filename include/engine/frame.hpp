#ifndef TETRIS_ENGINE_FRAME_HPP_
#define TETRIS_ENGINE_FRAME_HPP_

#include <optional>
#include <array>
#include <deque>

#include "engine/mino.hpp"
#include "core/rotation.hpp"


namespace tetris {
namespace engine {



struct mino;
class tetrimino;

struct frame {

    using block_t = std::optional<mino>;
    using row_t = std::array<block_t, 10>;
    using grid_t = std::deque<row_t>;

    enum class direction : std::uint8_t { left, right, up, down };

    frame();

    grid_t data;
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_FRAME_HPP_
