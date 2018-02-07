#include <SDL.h>

class Line {
public:
    // Needs a constructor for passing the renderer.
    Line(SDL_Renderer*); 
    
    /* Number of curves to repeat, the length of each curve,
     * position x, position y, and rotation angle.
     * */
    void drawCosLine(const int, const int, const int, const int, const int);
    void drawSinLine(const int, const int, const int, const int, const int);
    void drawTanLine(const int, const int, const int, const int, const int);

private:
    SDL_Renderer* const renderer;
};
