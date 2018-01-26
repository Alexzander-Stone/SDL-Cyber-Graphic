#include <SDL.h>

class BackLayer {
public:
    // Needs a constructor for passing the renderer.
    BackLayer(SDL_Renderer*);
    void draw();
private:
    SDL_Renderer* const renderer; 
};
