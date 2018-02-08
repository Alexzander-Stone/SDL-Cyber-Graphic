#include <SDL.h>

class Lighting{
    public:
        /* Lighting x and y coordinates, 
         * width and height (of the smallest circle), 
         * and SDL color choice. */
        Lighting(const SDL_Point, const int, const int, 
                 const SDL_Color, const int);
        void draw(SDL_Renderer* renderer);

    private:
        const SDL_Point lightingCenter;
        const int lightingRadiusW, lightingRadiusH;
        SDL_Color lightingColor;
        const int totalCircles;
};
