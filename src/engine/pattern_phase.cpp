#include "engine/pattern_phase.hpp"

#include "engine/game.hpp"
#include "engine/generation_phase.hpp"

namespace tetris {
namespace engine {



pattern_phase::pattern_phase(game& g): phase(g) {}


void pattern_phase::enter() {
    do_check_patterns();

    // Delete and pull down
}

void pattern_phase::exit() {}


std::optional<phase::pointer> pattern_phase::update(std::chrono::nanoseconds) {
    return std::make_unique<generation_phase>(game_state);
}

void pattern_phase::do_check_patterns() {
    // We only have to check for rows for now, might add new patterns later.

    int i = 0;
    for (auto row_it{game_state.grid.get_grid().cbegin()};
          row_it != game_state.grid.get_grid().cend(); ++row_it) {

        if (game_state.grid.is_full(*row_it)) {
            hit_list.push_back(i);
        }

        ++i;
    }
}

void pattern_phase::do_remove_full_lines() {}


} // namespace engine
} // namespace tetris
