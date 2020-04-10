#include "engine/falling_phase.hpp"

#include <cmath>

#include "engine/game.hpp"
#include "engine/pattern_phase.hpp"

#include <iostream>
namespace tetris {
namespace engine {



falling_phase::falling_phase(game& g):
    phase(g),
    fall_speed(1000 * std::pow(0.8 - (game_state.level - 1) * 0.007, game_state.level - 1)) {}


void falling_phase::enter() {}

void falling_phase::exit() {
    game_state.place();
}


std::optional<phase::pointer> falling_phase::update(std::chrono::nanoseconds dt) {

    using namespace std::chrono_literals;

    elapsed += dt;
    game_state.current_tetrimino->last_moved += dt;
    game_state.current_tetrimino->last_rotated += dt;


    if (current_stage == stage::lock) {
        lockdown_timer += dt;

        if (lockdown_timer >= 0.5s) {
            // We place the current tetrimino then go to the pattern phase.
            return std::make_unique<pattern_phase>(game_state); // Next phase.
        }
    }


    if (elapsed > (fast_falling ? fall_speed / 20 : fall_speed)) {

        // Fall 1 row
        elapsed = 0s;
        do_fall();
    }

    return {};
}

void falling_phase::handle_inputs(core::keyboard const& keyboard) {
    using namespace std::chrono_literals;

    if (keyboard.key_pressed(keyboard.down)) {
        fast_falling = true;
    } else {
        fast_falling = false;
    }

    if (keyboard.key_pressed(keyboard.up) && game_state.current_tetrimino->last_rotated > 0.15s
          && game_state.can_rotate(core::rotation::direction::clockwise)) {

        game_state.current_tetrimino->rotate(core::rotation::direction::clockwise);
        game_state.current_tetrimino->last_rotated = 0s;
    }

    bool moved{false};
    if (game_state.current_tetrimino->last_moved > 0.2s) {

        if (keyboard.key_pressed(keyboard.left) && game_state.can_move(frame::direction::left)) {


            game_state.current_tetrimino->position.j -= 1;
            game_state.current_tetrimino->last_moved = 0ns;
            moved = true;
        }

        if (keyboard.key_pressed(keyboard.right) && game_state.can_move(frame::direction::right)) {

            game_state.current_tetrimino->position.j += 1;
            game_state.current_tetrimino->last_moved = 0ns;
            moved = true;
        }
    }

    if (moved && game_state.can_move(frame::direction::down)) {
        current_stage = stage::free;
        lockdown_timer = 0ns;
    }
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
