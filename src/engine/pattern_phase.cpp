#include "engine/pattern_phase.hpp"

#include <iterator>
#include <algorithm>

#include "engine/game.hpp"
#include "engine/generation_phase.hpp"


namespace tetris {
namespace engine {



pattern_phase::pattern_phase(game& g): phase(g) {}


void pattern_phase::enter() {
    do_check_patterns();

    game_state.lines_cleared += hit_list.size();
    game_state.level = std::max(game_state.level, std::min(game_state.lines_cleared / 10, 15));

    do_remove_full_lines();
}

void pattern_phase::exit() {}


std::optional<phase::pointer> pattern_phase::update(std::chrono::nanoseconds) {
    return std::make_unique<generation_phase>(game_state);
}

void pattern_phase::do_check_patterns() {
    // We only have to check for rows for now, might add new patterns later.

    for (auto row_it{game_state.grid.data.cbegin()}; row_it != game_state.grid.data.cend();
          ++row_it) {

        if (game_state.is_full(*row_it)) {
            hit_list.push_back(std::distance(game_state.grid.data.cbegin(), row_it));
        }
    }
}

void pattern_phase::do_remove_full_lines() {
    for (auto i: hit_list) {
        game_state.remove_row(i);
    }

    hit_list.clear();
}


} // namespace engine
} // namespace tetris
