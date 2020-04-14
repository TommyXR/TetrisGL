# TetrisGL

This is an implementation of Tetris following the official [Tetris Design Guideline](doc/tetris_design_guideline.pdf) as closely as possible.
 It is written with modern C++ and OpenGL.


## Design decisions

### Tetris grid
I was hesitating between using a `deque` and a `vector` of arrays for the mino grid. Even
if a lot of push and pop operations are needed, I thought maybe iterating through the 
grid every frame could make `vector` faster because of memory being contiguous. I ended
up making a [benchmark](extras/tetris_grid_benchmark.cpp) to compare, and it turned out
`deque` is better.

### Phase map
For the engine phases map, my first thought was to use an `unordered_map`, since I use a `phase` enum.
However, as it turns out, the [benchmark](extras/state_container_benchmark.cpp) puts `std::array` with
casting the enum to an `int` as the definitive winner.

### Time
I decided to refer to time in milliseconds through the code. Most of the engine relies in
tenth of seconds, so it is the best compromise between clarity and precision.
