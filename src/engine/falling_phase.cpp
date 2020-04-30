#include "engine/falling_phase.hpp"

#include <cmath>

#include "engine/game.hpp"
#include "engine/pattern_phase.hpp"


namespace tetris {
namespace engine {



falling_phase::falling_phase(game& g):
    phase(g),
    fall_speed(1000 * std::pow(0.8 - (game_state.level - 1) * 0.007, game_state.level - 1)) {}


void falling_phase::enter() {

    if (!game_state.can_fall()) {
        // For now, just stop the game, but TODO create gameover_phase.
        game_state.is_running = false;
    }

    game_state.current_tetrimino->fall();
}

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

        if (lockdown_timer >= game_state.LOCKDOWN_DELAY) {
            // We place the current tetrimino then go to the pattern phase.
            return std::make_unique<pattern_phase>(game_state); // Next phase.
        }
    }

    // We want rational values, and std::chrono::milliseconds is only for integral..
    std::chrono::duration<long double, std::milli> time_to_fall;

    // If we're hard dropping, we drop the current tetrimino and go to the next phase.
    if (hard_dropping) {

        while (game_state.can_fall()) {
            game_state.current_tetrimino->position.i += 1;
        }
        return std::make_unique<pattern_phase>(game_state);

    } else if (fast_falling) {

        time_to_fall = fall_speed / game_state.FAST_FALL_MULTIPLIER;

    } else {

        time_to_fall = fall_speed;
    }

    if (elapsed > time_to_fall) {

        // Fall 1 row
        elapsed = 0s;
        do_fall();
    }

    return {};
}


void falling_phase::handle_inputs() {

    using namespace std::chrono_literals;


    if (!already_swapped_piece && game_state.keyboard.key_pressed(game_state.keyboard.C)) {
        already_swapped_piece = true;

        game_state.store_current_piece();
    }


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
          && game_state.current_tetrimino->last_rotated > game_state.ROTATION_DELAY
          && game_state.can_rotate(core::rotation::direction::clockwise)) {

        game_state.current_tetrimino->rotate(core::rotation::direction::clockwise);
        game_state.current_tetrimino->last_rotated = 0s;

        // Maybe change this later, you can stay indefinetely on a block with a cube.
        // (maybe check if not in air before locking)
        lockdown_timer = 0s;
    }


    bool const last_moved_delay{game_state.current_tetrimino->last_moved > game_state.MOVE_DELAY};

    bool const left_pressed{game_state.keyboard.key_pressed(game_state.keyboard.left)};
    bool const left_autorepeat{left_press_timer > game_state.AUTOREPEAT_DELAY
          && game_state.current_tetrimino->last_moved
                > game_state.MOVE_DELAY / game_state.AUTOREPEAT_MULTIPLIER};

    bool const right_pressed{game_state.keyboard.key_pressed(game_state.keyboard.right)};
    bool const right_autorepeat{right_press_timer > game_state.AUTOREPEAT_DELAY
          && game_state.current_tetrimino->last_moved
                > game_state.MOVE_DELAY / game_state.AUTOREPEAT_MULTIPLIER};


    bool moved{false};
    if (left_pressed && (last_moved_delay || left_autorepeat)
          && game_state.can_move(frame::direction::left)) {

        game_state.current_tetrimino->position.j -= 1;
        game_state.current_tetrimino->last_moved = 0s;
        moved = true;

    } else if (!left_pressed) {
        left_press_timer = 0s;
    }


    if (right_pressed && (last_moved_delay || right_autorepeat)
          && game_state.can_move(frame::direction::right)) {

        game_state.current_tetrimino->position.j += 1;
        game_state.current_tetrimino->last_moved = 0s;
        moved = true;

    } else if (!right_pressed) {
        right_press_timer = 0s;
    }


    if (moved && game_state.can_move(frame::direction::down)) {

        current_stage = stage::free;
        lockdown_timer = 0s;
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
