#ifndef TETRIS_ENGINE_PHASE_HPP_
#define TETRIS_ENGINE_PHASE_HPP_

#include <memory>
#include <optional>
#include <chrono>

#include "core/keyboard.hpp"


namespace tetris {
namespace engine {


class game;

class phase {

  public:
    using pointer = std::unique_ptr<phase>;

    phase(game& g): game_state(g) {}


    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual std::optional<pointer> update(std::chrono::nanoseconds) = 0;

    virtual void handle_inputs() {
        // Defaults to doing nothing since not every phase needs to handle inputs
    }



  protected:
    game& game_state;
    std::chrono::nanoseconds elapsed{0};
};


} // namespace engine
} // namespace tetris



#endif // TETRIS_ENGINE_PHASE_HPP_
