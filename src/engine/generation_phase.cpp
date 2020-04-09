#include "engine/generation_phase.hpp"

#include "engine/game.hpp"
#include "engine/falling_phase.hpp"


namespace tetris {
namespace engine {


generation_phase::generation_phase(game& g): phase(g) {}


void generation_phase::enter() {

    while (game_state.next_queue.size() < 14) {
        do_generate_tetriminos();
    }
}


void generation_phase::exit() {
    game_state.current_tetrimino = std::make_unique<tetrimino>(game_state.next_queue.front());
    game_state.next_queue.pop();
}


std::optional<phase::pointer> generation_phase::update(std::chrono::nanoseconds dt) {

    using namespace std::chrono_literals;

    elapsed += dt;


    // Generation phase is 0.2s
    if (elapsed >= 0.2s) {
        return std::make_unique<falling_phase>(game_state);
    }

    return {};
}


void generation_phase::do_generate_tetriminos() {

    for (auto t: game_state.generator.generate()) {
        game_state.next_queue.push(t);
    }
}



} // namespace engine
} // namespace tetris
