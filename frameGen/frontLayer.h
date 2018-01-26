#include <SDL.h>

class FrontLayer {
public:
    // Needs a constructor for passing the renderer.
    FrontLayer(SDL_Renderer*);
    void draw();
private:
    SDL_Renderer* const renderer; 
};
