#include "engine/falling_phase.hpp"

#include <cmath>

#include "engine/game.hpp"
#include "engine/pattern_phase.hpp"


namespace tetris {
namespace engine {



falling_phase::falling_phase(game& g):
    phase(g),
    fall_speed(1000 * std::pow(0.8 - (game_state.level - 1) * 0.007, game_state.level - 1)) {}


void falling_phase::enter() {}

void falling_phase::exit() {
    game_state.grid.place(*game_state.current_tetrimino);
}


std::optional<phase::pointer> falling_phase::update(std::chrono::nanoseconds dt) {

    using namespace std::chrono_literals;

    elapsed += dt;

    if (current_stage == stage::lock) {
        lockdown_timer += dt;

        if (lockdown_timer >= 0.5s) {
            // We place the current tetrimino then go to the pattern phase.
            return std::make_unique<pattern_phase>(game_state); // Next phase.
        }
    }


    if (elapsed > fall_speed) {

        // Fall 1 row
        elapsed -= std::chrono::duration_cast<std::chrono::nanoseconds>(fall_speed);
        do_fall();
    }

    return {};
}



void falling_phase::do_fall() {

    if (game_state.can_fall()) {
        game_state.current_tetrimino->fall();
    } else {
        current_stage = stage::lock;
    }
}



} // namespace engine
} // namespace tetris
