#include <SDL.h>

class Line {
public:
    // Needs a constructor for passing the renderer.
    Line(SDL_Renderer*); 
    // Curves
    void drawCosLine(int, int, int, int);
    void drawSinLine(int, int, int, int);
    void drawTanLine(int, int, int, int);

private:
    SDL_Renderer* const renderer;
};
