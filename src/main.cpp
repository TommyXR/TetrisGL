#include <cstdint>
#include <chrono>
#include <iostream>
#include <thread>

#include "gfx/gl_context.hpp"
#include "gfx/render_window.hpp"

#include "engine/game.hpp"


int main() {

    using namespace tetris;
    using namespace std::chrono_literals;
    namespace chrono = std::chrono;



    gfx::gl_context context({4, 0});
    // gfx::render_window window(context, {800, 600, "Tetris"});

    chrono::high_resolution_clock clock;
    engine::game game;

    game.start();
    auto frame_begin{clock.now()};

    while (game.running()) {

        // handle inputs

        auto const frame_end{clock.now()};
        auto const dt{chrono::duration_cast<chrono::nanoseconds>(frame_end - frame_begin)};

        game.update(dt);


        frame_begin = frame_end;


        // render

        // std::cerr << "Frame lasted " << dt.count() << "ms.\n";
    }



    return 0;
}
