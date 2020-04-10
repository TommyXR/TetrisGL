#ifndef TETRIS_ENGINE_GAME_HPP_
#define TETRIS_ENGINE_GAME_HPP_


#include <queue>
#include <chrono>

#include "engine/tetrimino_generator.hpp"
#include "engine/phase.hpp"
#include "engine/frame.hpp"
#include "core/keyboard.hpp"

namespace tetris {
namespace engine {



class game {

  public:
    friend class generation_phase;
    friend class falling_phase;
    friend class pattern_phase;

    game() = default;

    void update(std::chrono::nanoseconds);
    void handle_inputs(core::keyboard const&);


    void start();
    bool running() const noexcept;


    // private:
    bool can_fall() const;

    phase::pointer current_phase;
    tetrimino::pointer current_tetrimino;
    int level{1};

    frame grid;

    std::queue<tetrimino::tetrimino_t> next_queue;
    tetrimino_generator generator;

    bool is_running{false};
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_GAME_HPP_
