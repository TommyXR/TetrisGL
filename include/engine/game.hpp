#ifndef TETRIS_ENGINE_GAME_HPP_
#define TETRIS_ENGINE_GAME_HPP_


#include <queue>
#include <chrono>
#include <SFML/Audio.hpp>

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

    sf::SoundBuffer sb[2];
    sf::Sound s[2];


    game(gfx::renderer&, core::keyboard&);

    void update(std::chrono::nanoseconds);
    void handle_inputs();

    void render() const;

    void start();
    void place_tetrimino();
    void remove_row(int);

    void store_current_piece();

    bool running() const noexcept;
    bool can_fall() const noexcept;
    bool can_fall(tetrimino const&) const noexcept;

    bool is_full(frame::row_t const&) const noexcept;
    bool can_move(frame::direction) const noexcept;
    bool can_rotate(core::rotation::direction) const noexcept;
    bool validate_movement(tetrimino const&, int const = 0, int const = 0) const noexcept;


  private:
    static int constexpr FAST_FALL_MULTIPLIER{20};
    static int constexpr AUTOREPEAT_MULTIPLIER{4};

    static std::chrono::milliseconds constexpr LOCKDOWN_DELAY{500};
    static std::chrono::milliseconds constexpr ROTATION_DELAY{150};
    static std::chrono::milliseconds constexpr MOVE_DELAY{150};
    static std::chrono::milliseconds constexpr AUTOREPEAT_DELAY{333};


    phase::pointer current_phase;
    tetrimino::pointer current_tetrimino;


    int level = 1;
    int lines_cleared = 0;

    frame grid;

    std::queue<tetrimino::tetrimino_t> next_queue;
    std::optional<tetrimino::tetrimino_t> held_piece;


    tetrimino_generator generator;

    gfx::renderer& renderer;
    core::keyboard& keyboard;

    bool is_running{false};
};



} // namespace engine
} // namespace tetris


#endif // TETRIS_ENGINE_GAME_HPP_
