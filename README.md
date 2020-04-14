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

### Time
At first, I was refering to time using `std::milliseconds`. However, the engine ended up being too fast for this, so
I had to go with `std::nanoseconds`

