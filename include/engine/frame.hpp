#ifndef TETRIS_ENGINE_FRAME_HPP_
#define TETRIS_ENGINE_FRAME_HPP_

#include <optional>
#include <array>
#include <deque>

#include "engine/mino.hpp"


namespace tetris {
namespace engine {

class mino;
class tetrimino;

class frame {

  public:
    using block_t = std::optional<mino>;
    using row_t = std::array<block_t, 10>;
    using grid_t = std::deque<row_t>;

    enum class direction : std::uint8_t { left, right, up, down };

    frame();


    bool is_full(row_t const&) const noexcept;

    bool validate(tetrimino const&, int const = 0, int const = 0) const;
    bool can_move(tetrimino const&, direction) const;

    void place(tetrimino const&);

    grid_t get_grid() const;



  private:
    grid_t grid;
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_FRAME_HPP_
