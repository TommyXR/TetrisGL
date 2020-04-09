#ifndef TETRIS_ENGINE_GENERATION_PHASE_HPP_
#define TETRIS_ENGINE_GENERATION_PHASE_HPP_

#include <optional>
#include <chrono>

#include "engine/phase.hpp"


namespace tetris {
namespace engine {


class game;

class generation_phase: public phase {

  public:
    generation_phase(game&);

    void enter() override;
    void exit() override;
    std::optional<phase::pointer> update(std::chrono::nanoseconds) override;


  private:
    void do_generate_tetriminos();
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_GENERATION_PHASE_HPP_
