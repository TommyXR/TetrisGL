#ifndef TETRIS_ENGINE_GAME_HPP_
#define TETRIS_ENGINE_GAME_HPP_


#include <queue>
#include <chrono>

#include "engine/tetrimino_generator.hpp"
#include "engine/phase.hpp"
#include "engine/frame.hpp"
#include "core/keyboard.hpp"
#include "gfx/renderer.hpp"


namespace tetris {
namespace engine {



class game {

  public:
    friend class generation_phase;
    friend class falling_phase;
    friend class pattern_phase;
    friend class gfx::renderer;


    game(gfx::renderer&, core::keyboard&);

    void update(std::chrono::nanoseconds);
    void handle_inputs();

    void render() const;

    void start();
    void place_tetrimino();
    void remove_row(int);

    bool running() const noexcept;
    bool can_fall() const noexcept;
    bool is_full(frame::row_t const&) const noexcept;
    bool can_move(frame::direction) const noexcept;
    bool can_rotate(core::rotation::direction) const noexcept;
    bool validate_movement(int const = 0, int const = 0) const noexcept;


    // private:
    phase::pointer current_phase;
    tetrimino::pointer current_tetrimino;
    int level{1};

    frame grid;

    std::queue<tetrimino::tetrimino_t> next_queue;
    tetrimino_generator generator;

    gfx::renderer& renderer;
    core::keyboard& keyboard;

    bool is_running{false};
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_GAME_HPP_
