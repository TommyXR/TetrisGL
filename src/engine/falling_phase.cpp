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
    game_state.place_tetrimino();
}


std::optional<phase::pointer> falling_phase::update(std::chrono::nanoseconds dt) {

    using namespace std::chrono_literals;

    elapsed += dt;
    left_press_timer += dt;
    right_press_timer += dt;
    game_state.current_tetrimino->last_moved += dt;
    game_state.current_tetrimino->last_rotated += dt;



    if (current_stage == stage::lock) {
        lockdown_timer += dt;

        if (lockdown_timer >= 0.5s || hard_dropping) {
            // We place the current tetrimino then go to the pattern phase.
            return std::make_unique<pattern_phase>(game_state); // Next phase.
        }
    }

    std::chrono::duration<long double, std::milli> time_to_fall;
    if (hard_dropping) {
        time_to_fall = 0.0001s;
    } else if (fast_falling) {
        time_to_fall = fall_speed / 20;
    } else {
        time_to_fall = fall_speed;
    }

    if (elapsed > time_to_fall) {

        // Fall 1 row
        elapsed = 0s;
        do_fall();
    }

    return {};
} // namespace engine


void falling_phase::handle_inputs() {
    using namespace std::chrono_literals;

    if (game_state.keyboard.key_pressed(game_state.keyboard.down)) {
        fast_falling = true;
    } else {
        fast_falling = false;
    }

    if (game_state.keyboard.key_pressed(game_state.keyboard.space)) {
        hard_dropping = true;
    } else {
        hard_dropping = false;
    }


    if (game_state.keyboard.key_pressed(game_state.keyboard.up)
          && game_state.current_tetrimino->last_rotated > 0.15s
          && game_state.can_rotate(core::rotation::direction::clockwise)) {

        game_state.current_tetrimino->rotate(core::rotation::direction::clockwise);
        game_state.current_tetrimino->last_rotated = 0s;
    }



    bool const last_moved_delay{game_state.current_tetrimino->last_moved > 0.2s};
    bool const left_pressed{game_state.keyboard.key_pressed(game_state.keyboard.left)};
    bool const left_autorepeat{
          left_press_timer > 0.33s && game_state.current_tetrimino->last_moved > 0.05s};

    bool const right_pressed{game_state.keyboard.key_pressed(game_state.keyboard.right)};
    bool const right_autorepeat{
          right_press_timer > 0.33s && game_state.current_tetrimino->last_moved > 0.05s};

    // Normally, 0.2s between moves. If autorepeat (which activates after a third of a second),
    // moves every 0.05s.
    bool moved{false};
    if ((last_moved_delay || left_autorepeat) && left_pressed
          && game_state.can_move(frame::direction::left)) {

        game_state.current_tetrimino->position.j -= 1;
        game_state.current_tetrimino->last_moved = 0s;
        moved = true;

    } else if (!left_pressed) {
        left_press_timer = 0s;
    }

    if ((last_moved_delay || right_autorepeat) && right_pressed
          && game_state.can_move(frame::direction::right)) {

        game_state.current_tetrimino->position.j += 1;
        game_state.current_tetrimino->last_moved = 0ns;
        moved = true;
    } else if (!right_pressed) {
        right_press_timer = 0s;
    }


    if (moved && game_state.can_move(frame::direction::down)) {
        current_stage = stage::free;
        lockdown_timer = 0ns;
    }
} // namespace engine



void falling_phase::do_fall() {

    if (game_state.can_fall()) {
        game_state.current_tetrimino->fall();
    } else {
        current_stage = stage::lock;
    }
}



} // namespace engine
} // namespace tetris
