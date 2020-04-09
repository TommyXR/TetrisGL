#include "engine/falling_phase.hpp"

#include <cmath>

#include "engine/game.hpp"


namespace tetris {
namespace engine {



falling_phase::falling_phase(game& g):
    phase(g),
    fall_speed(1000 * std::pow(0.8 - (game_state.level - 1) * 0.007, game_state.level - 1)) {}


void falling_phase::enter() {}

void falling_phase::exit() {}


std::optional<phase::pointer> falling_phase::update(std::chrono::nanoseconds dt) {

    elapsed += dt;

    if (elapsed > fall_speed) {

        // Fall 1 row
        elapsed -= std::chrono::duration_cast<std::chrono::nanoseconds>(fall_speed);
    }

    return {};
}



} // namespace engine
} // namespace tetris
