#ifndef TETRIS_GFX_RENDERER_HPP_
#define TETRIS_GFX_RENDERER_HPP_


namespace tetris {
namespace engine {

class game;

} // namespace engine
namespace gfx {



class render_window;

class renderer {

  public:
    renderer(render_window&);

    void render(engine::game const&);

  private:
};



} // namespace gfx
} // namespace tetris

#endif // TETRIS_GFX_RENDERER_HPP_
