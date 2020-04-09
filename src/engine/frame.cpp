#include "engine/frame.hpp"

#include <algorithm>
#include <cstdint>


#include "engine/tetrimino.hpp"


namespace tetris {
namespace engine {


using namespace tetris::core;


frame::frame() {

    // Tetris grid is 20x10, but 4 hidden rows for spawning blocks.
    for (int i{0}; i < 24; ++i) {
        grid.emplace_back();
    }
}



bool frame::is_full(row_t const& row) const noexcept {
    return std::all_of(row.cbegin(), row.cend(), [](auto const& e) { return e; });
}


bool frame::validate(tetrimino const& t, int const off_i, int const off_j) const {

    for (auto i{0}; i < static_cast<int>(t.current_rotation->data.size()); ++i) {

        for (auto j{0}; j < static_cast<int>(t.current_rotation->data.at(i).size()); ++j) {

            // If there is no block at that position, we skip it.
            if (!t.current_rotation->data.at(i).at(j)) {
                continue;
            }

            auto const grid_i{i + t.position.i + off_i};
            auto const grid_j{j + t.position.j + off_j};

            // Out of bounds
            if (grid_i >= static_cast<int>(grid.size())
                  || grid_j >= static_cast<int>(grid[0].size()) || grid_i < 0 || grid_j < 0) {
                return false;
            }

            // Mino already present
            if (grid[grid_i][grid_j]) {
                return false;
            }
        }
    }

    return true;
}


bool frame::can_move(tetrimino const& t, direction d) const {

    int offset_i, offset_j;

    switch (d) {
        case direction::down: {
            offset_i = 1;
            offset_j = 0;
            break;
        }

        case direction::up: {
            offset_i = -1;
            offset_j = 0;
            break;
        }

        case direction::left: {
            offset_i = 0;
            offset_j = -1;
            break;
        }

        case direction::right: {
            offset_i = 0;
            offset_j = 1;
            break;
        }
    }

    return validate(t, offset_i, offset_j);
}



void frame::place(tetrimino const& t) {

    for (auto i{0}; i < static_cast<int>(t.current_rotation->data.size()); ++i) {

        for (auto j{0}; j < static_cast<int>(t.current_rotation->data.at(i).size()); ++j) {

            auto const grid_i{i + t.position.i};
            auto const grid_j{j + t.position.j};

            if (t.current_rotation->data.at(i).at(j)) {
                grid[grid_i][grid_j] = {t};
            }
        }
    }
}


frame::grid_t frame::get_grid() const {
    return grid;
}



} // namespace engine
} // namespace tetris
