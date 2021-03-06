#include "engine/game.hpp"

#include <algorithm>

#include "engine/generation_phase.hpp"


namespace tetris {
namespace engine {



game::game(gfx::renderer& r, core::keyboard& k): renderer(r), keyboard(k) {
    sb[0].loadFromFile("resources/audio/hit.wav");
    sb[1].loadFromFile("resources/audio/lineclear.wav");
    s[0].setBuffer(sb[0]);
    s[1].setBuffer(sb[1]);
}


void game::update(std::chrono::nanoseconds dt) {

    if (auto new_phase = current_phase->update(dt); new_phase) {

        current_phase->exit();
        current_phase = std::move(new_phase.value());
        current_phase->enter();
    }
}


void game::handle_inputs() {
    current_phase->handle_inputs();
}


void game::render() const {
    renderer.render(*this);
}


void game::start() {
    current_phase = std::make_unique<generation_phase>(*this);
    current_phase->enter();

    is_running = true;
}

void game::place_tetrimino() {

    s[0].play(); // TEMPORARY

    for (auto i{0}; i < static_cast<int>(current_tetrimino->current_rotation->data.size()); ++i) {
        for (auto j{0};
              j < static_cast<int>(current_tetrimino->current_rotation->data.at(i).size()); ++j) {

            auto const grid_i{i + current_tetrimino->position.i};
            auto const grid_j{j + current_tetrimino->position.j};

            if (current_tetrimino->current_rotation->data.at(i).at(j)) {
                grid.data[grid_i][grid_j] = {*current_tetrimino};
            }
        }
    }
}


void game::remove_row(int idx) {
    s[1].play(); // TEMPORARY
    grid.data.erase(grid.data.begin() + idx);
    grid.data.emplace_front();
}

void game::store_current_piece() {

    auto const tmp = held_piece;

    held_piece = current_tetrimino->type;

    if (tmp) {

        current_tetrimino = std::make_unique<tetrimino>(*tmp);

    } else {

        current_tetrimino = std::make_unique<tetrimino>(next_queue.front());
        next_queue.pop();
    }
}


bool game::running() const noexcept {
    return is_running;
}


bool game::can_fall() const noexcept {
    return can_move(frame::direction::down);
}

bool game::can_fall(tetrimino const& t) const noexcept {
    return validate_movement(t, 1, 0);
}

bool game::is_full(frame::row_t const& row) const noexcept {
    return std::all_of(row.cbegin(), row.cend(), [](auto const& e) { return e; });
}


bool game::can_move(frame::direction d) const noexcept {
    int offset_i{0}, offset_j{0};

    switch (d) {
        case frame::direction::down: {
            offset_i = 1;
            offset_j = 0;
            break;
        }

        case frame::direction::up: {
            offset_i = -1;
            offset_j = 0;
            break;
        }

        case frame::direction::left: {
            offset_i = 0;
            offset_j = -1;
            break;
        }

        case frame::direction::right: {
            offset_i = 0;
            offset_j = 1;
            break;
        }
    }

    return validate_movement(*current_tetrimino, offset_i, offset_j);
}

bool game::can_rotate(core::rotation::direction dir) const noexcept {

    current_tetrimino->rotate(dir);

    bool can{validate_movement(*current_tetrimino)};

    current_tetrimino->rotate(static_cast<core::rotation::direction>(!static_cast<bool>(dir)));


    return can;
}


bool game::validate_movement(tetrimino const& t, int di, int dj) const noexcept {
    for (auto i{0}; i < static_cast<int>(t.current_rotation->data.size()); ++i) {

        for (auto j{0}; j < static_cast<int>(t.current_rotation->data.at(i).size()); ++j) {

            // If there is no block at that position, we skip it.
            if (!t.current_rotation->data.at(i).at(j)) {
                continue;
            }

            auto const grid_i{i + t.position.i + di};
            auto const grid_j{j + t.position.j + dj};

            // Out of bounds
            if (grid_i >= static_cast<int>(grid.data.size())
                  || grid_j >= static_cast<int>(grid.data[0].size()) || grid_i < 0 || grid_j < 0) {
                return false;
            }

            // Mino already present
            if (grid.data[grid_i][grid_j]) {
                return false;
            }
        }
    }

    return true;
}



} // namespace engine
} // namespace tetris
