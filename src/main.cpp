#include <cstdint>
#include <chrono>
#include <iostream>
#include <thread>
#include <string>
#include <SFML/Audio.hpp>

#include "core/keyboard.hpp"
#include "engine/game.hpp"
#include "gfx/gl_context.hpp"
#include "gfx/render_window.hpp"
#include "gfx/renderer.hpp"



int main() {

    using namespace tetris;
    using namespace std::chrono_literals;
    namespace chrono = std::chrono;

    sf::Music music;
    music.openFromFile("resources/audio/connected.wav");
    music.play();


    gfx::gl_context context({4, 0});
    gfx::render_window window(context, {860, 1280, "Tetris"});
    gfx::renderer renderer(context, window);
    core::keyboard keyboard(window);


    chrono::high_resolution_clock clock;

    engine::game game(renderer, keyboard);

    game.start();

    auto frame_begin{clock.now()};
    while (game.running() && !window.should_close()) {

        window.poll_events();


        game.handle_inputs();


        auto const frame_end{clock.now()};
        auto const dt{chrono::duration_cast<chrono::nanoseconds>(frame_end - frame_begin)};

        game.update(dt);

        frame_begin = frame_end;


        game.render();
    }



    return 0;
}
