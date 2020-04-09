#ifndef TETRIS_ENGINE_FALLING_PHASE_HPP_
#define TETRIS_ENGINE_FALLING_PHASE_HPP_

#include <optional>
#include <chrono>

#include "engine/phase.hpp"


namespace tetris {
namespace engine {


class game;

class falling_phase: public phase {

  public:
    falling_phase(game&);

    void enter() override;
    void exit() override;

    std::optional<phase::pointer> update(std::chrono::nanoseconds) override;


  private:
    std::chrono::duration<long double, std::milli> fall_speed;
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_FALLING_PHASE_HPP_
