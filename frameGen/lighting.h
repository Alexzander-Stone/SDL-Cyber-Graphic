#include <SDL.h>

class Lighting{
    public:
        /* Circle width and height, position x and y coordinates 
         * and SDL color choice. */
        Lighting(const SDL_Point, const int, const int, const SDL_Color);
        void draw(SDL_Renderer* renderer);

    private:
        SDL_Point lightingCenter;
        int lightingRadiusW, lightingRadiusH;
        SDL_Color lightingColor;
};
