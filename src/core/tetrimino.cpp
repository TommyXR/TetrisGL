#include "core/tetrimino.hpp"

#include "core/tetrimino_data.hpp"


namespace tetris {
namespace core {



tetrimino::tetrimino(tetrimino_t t): type(t) {

    switch (t) {
        case tetrimino_t::I: {
            color = data::I_color;
            position = data::I_startpos;
            rotations = data::I_rotations;
            break;
        }

        case tetrimino_t::J: {
            color = data::J_color;
            position = data::J_startpos;
            rotations = data::J_rotations;
            break;
        }

        case tetrimino_t::L: {
            color = data::L_color;
            position = data::L_startpos;
            rotations = data::L_rotations;
            break;
        }

        case tetrimino_t::O: {
            color = data::O_color;
            position = data::O_startpos;
            rotations = data::O_rotations;
            break;
        }

        case tetrimino_t::S: {
            color = data::S_color;
            position = data::S_startpos;
            rotations = data::S_rotations;
            break;
        }

        case tetrimino_t::T: {
            color = data::T_color;
            position = data::T_startpos;
            rotations = data::T_rotations;
            break;
        }

        case tetrimino_t::Z: {
            color = data::Z_color;
            position = data::Z_startpos;
            rotations = data::Z_rotations;
            break;
        }
    }

    current_rotation = rotations.cbegin();
}


void tetrimino::rotate(rotation::direction dir) noexcept {

    switch (dir) {

        case rotation::direction::clockwise: {
            ++current_rotation;

            if (current_rotation == rotations.cend()) {
                current_rotation = rotations.cbegin();
            }

            break;
        }

        case rotation::direction::counterclockwise: {
            if (current_rotation == rotations.cbegin()) {
                current_rotation += 3;
                break;
            }

            --current_rotation;
            break;
        }
    }
}



} // namespace core
} // namespace tetris
