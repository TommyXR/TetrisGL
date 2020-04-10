#include <cstdint>
#include <chrono>
#include <iostream>
#include <thread>

#include "core/keyboard.hpp"
#include "engine/game.hpp"
#include "gfx/gl_context.hpp"
#include "gfx/render_window.hpp"
#include <string>


std::string draw(tetris::engine::game& g) {
    std::array<std::array<char, 10>, 24> txt{{'z'}};

    std::string res{""};

    auto grid = g.grid.get_grid();

    for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 10; ++j) {

            if (grid[i][j]) {
                txt[i][j] = 'x';
            } else {
                txt[i][j] = '_';
            }
        }
    }

    if (g.current_tetrimino) {

        auto t = *g.current_tetrimino;
        auto rot = *t.current_rotation;

        auto du = (int)rot.data.size();

        auto dv = (int)rot.data[0].size();


        for (int di = 0; di < du; ++di) {
            for (int dj = 0; dj < dv; ++dj) {

                if (rot.data[di][dj]) {
                    txt[t.position.i + di][t.position.j + dj] = 'o';
                }
            }
        }
    }


    res += "##########\n";
    for (auto row: txt) {
        for (auto ch: row) {
            res += ch;
        }

        res += "\n";
    }
    res += "##########\n";

    return res;
}


int main() {

    using namespace tetris;
    using namespace std::chrono_literals;
    namespace chrono = std::chrono;


    gfx::gl_context context({4, 0});
    gfx::render_window window(context, {800, 600, "Tetris"});
    core::keyboard keyboard(window);

    chrono::high_resolution_clock clock;
    engine::game game;

    game.start();
    auto frame_begin{clock.now()};

    std::string prec{""};

    while (game.running()) {

        window.poll_events();


        game.handle_inputs(keyboard);


        auto const frame_end{clock.now()};
        auto const dt{chrono::duration_cast<chrono::nanoseconds>(frame_end - frame_begin)};


        game.update(dt);


        frame_begin = frame_end;


        // render
        std::string curr = draw(game);
        if (curr != prec) {
            prec = curr;
            std::cerr << curr;
        }
    }



    return 0;
}
