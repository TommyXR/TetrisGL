#ifndef TETRIS_ENGINE_PATTERN_PHASE_HPP_
#define TETRIS_ENGINE_PATTERN_PHASE_HPP_

#include <vector>

#include "engine/phase.hpp"
#include "core/position_t.hpp"


namespace tetris {
namespace engine {


class game;

class pattern_phase: public phase {

  public:
    pattern_phase(game&);

    void enter() override;
    void exit() override;

    std::optional<phase::pointer> update(std::chrono::nanoseconds) override;

  private:
    void do_check_patterns();
    void do_remove_full_lines();

    std::vector<int> hit_list;
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_PATTERN_PHASE_HPP_
