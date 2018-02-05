#include <SDL.h>

class BackLayer {
public:
    // Needs a constructor for passing the renderer.
    BackLayer(SDL_Renderer*); 
    void draw();
    // Curves
    void createCosLine(int, int, int, int);
    void createSinLine(int, int, int, int);
    void createTanLine(int, int, int, int);

private:
    SDL_Renderer* const renderer;

    void createSun();
    void createCircle(SDL_Point, int, SDL_Color);
    
    

    // Console
    void createConsole(int, int, int, int);
};
