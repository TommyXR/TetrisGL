#ifndef TETRIS_TETROMINO_DATA_HPP_
#define TETRIS_TETROMINO_DATA_HPP_

#include <vector>
#include <array>

#include "engine/tetrimino.hpp"
#include "core/position_t.hpp"
#include "core/rotation.hpp"


// This file contains the data for the tetrimino. It contains the shapes
// for every rotation, TOADD...
namespace tetris {
namespace data {



namespace {

// I
core::rotation const I_r0{{
      {false, false, false, false},
      {true, true, true, true},
      {false, false, false, false},
      {false, false, false, false},
}};

core::rotation const I_r1{{
      {false, false, true, false},
      {false, false, true, false},
      {false, false, true, false},
      {false, false, true, false},
}};

core::rotation const I_r2{{
      {false, false, false, false},
      {false, false, false, false},
      {true, true, true, true},
      {false, false, false, false},
}};

core::rotation const I_r3{{
      {false, true, false, false},
      {false, true, false, false},
      {false, true, false, false},
      {false, true, false, false},
}};


// J
core::rotation const J_r0{{
      {true, false, false}, //
      {true, true, true},   //
      {false, false, false} //
}};

core::rotation const J_r1{{
      {false, true, true},  //
      {false, true, false}, //
      {false, true, false}  //
}};

core::rotation const J_r2{{
      {false, false, false}, //
      {true, true, true},    //
      {false, false, true}   //
}};

core::rotation const J_r3{{
      {false, true, false}, //
      {false, true, false}, //
      {true, true, false}   //
}};


// L
core::rotation const L_r0{{
      {false, false, true}, //
      {true, true, true},   //
      {false, false, false} //
}};

core::rotation const L_r1{{
      {false, true, false}, //
      {false, true, false}, //
      {false, true, true}   //
}};

core::rotation const L_r2{{
      {false, false, false}, //
      {true, true, true},    //
      {true, false, false}   //
}};

core::rotation const L_r3{{
      {true, true, false},  //
      {false, true, false}, //
      {false, true, false}  //
}};


// O
core::rotation const O_r0{{
      {false, true, true},  //
      {false, true, true},  //
      {false, false, false} //
}};


// S
core::rotation const S_r0{{
      {false, true, true},   //
      {true, true, false},   //
      {false, false, false}, //
}};

core::rotation const S_r1{{
      {false, true, false}, //
      {false, true, true},  //
      {false, false, true}, //
}};

core::rotation const S_r2{{
      {false, false, false}, //
      {false, true, true},   //
      {true, true, false},   //
}};

core::rotation const S_r3{{
      {true, false, false}, //
      {true, true, false},  //
      {false, true, false}, //
}};


// T
core::rotation const T_r0{{
      {false, true, false}, //
      {true, true, true},   //
      {false, false, false} //
}};

core::rotation const T_r1{{
      {false, true, false}, //
      {false, true, true},  //
      {false, true, false}  //
}};

core::rotation const T_r2{{
      {false, false, false}, //
      {true, true, true},    //
      {false, true, false}   //
}};

core::rotation const T_r3{{
      {false, true, false}, //
      {true, true, false},  //
      {false, true, false}  //
}};


// Z
core::rotation const Z_r0{{
      {true, true, false},  //
      {false, true, true},  //
      {false, false, false} //
}};

core::rotation const Z_r1{{
      {false, false, true}, //
      {false, true, true},  //
      {false, true, false}  //
}};

core::rotation const Z_r2{{
      {false, false, false}, //
      {true, true, false},   //
      {false, true, true}    //
}};

core::rotation const Z_r3{{
      {false, true, false}, //
      {true, true, false},  //
      {true, false, false}  //
}};

} // namespace


engine::tetrimino::rotation_array const I_rotations{I_r0, I_r1, I_r2, I_r3};
core::position_t const I_startpos{1, 3};
core::color_t const I_color{0.25, 0.78, 0.96};


engine::tetrimino::rotation_array const J_rotations{J_r0, J_r1, J_r2, J_r3};
core::position_t const J_startpos{1, 3};
core::color_t const J_color{0, 0.44, 0.68};


engine::tetrimino::rotation_array const L_rotations{L_r0, L_r1, L_r2, L_r3};
core::position_t const L_startpos{1, 3};
core::color_t const L_color{0.92, 0.53, 0.11};


engine::tetrimino::rotation_array const O_rotations{O_r0, O_r0, O_r0, O_r0};
core::position_t const O_startpos{1, 3};
core::color_t const O_color{1, 0.87, 0.15};


engine::tetrimino::rotation_array const S_rotations{S_r0, S_r1, S_r2, S_r3};
core::position_t const S_startpos{1, 3};
core::color_t const S_color{0.45, 0.72, 0.24};


engine::tetrimino::rotation_array const T_rotations{T_r0, T_r1, T_r2, T_r3};
core::position_t const T_startpos{1, 3};
core::color_t const T_color{0.51, 0.11, 0.5};


engine::tetrimino::rotation_array const Z_rotations{Z_r0, Z_r1, Z_r2, Z_r3};
core::position_t const Z_startpos{1, 3};
core::color_t const Z_color{0.79, 0.09, 0.11};



} // namespace data
} // namespace tetris


#endif // TETRIS_TETROMINO_DATA_HPP_
