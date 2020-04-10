#include "engine/game.hpp"

#include "engine/generation_phase.hpp"


namespace tetris {
namespace engine {



void game::update(std::chrono::nanoseconds dt) {

    if (auto new_phase = current_phase->update(dt); new_phase) {

        current_phase->exit();
        current_phase = std::move(new_phase.value());
        current_phase->enter();
    }
}


void game::start() {
    current_phase = std::make_unique<generation_phase>(*this);
    current_phase->enter();

    is_running = true;
}


bool game::running() const noexcept {
    return is_running;
}

bool game::can_fall() const {
    return grid.can_move(*current_tetrimino, frame::direction::down);
}



} // namespace engine
} // namespace tetris
