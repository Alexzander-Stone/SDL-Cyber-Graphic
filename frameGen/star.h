#include <SDL.h>

class Star{
    public:
        /* Circle width and height, position x and y coordinates 
         * and SDL color choice.
         */
        Star(const SDL_Point, const int, const int, const SDL_Color);
        void draw(SDL_Renderer* renderer);

    private:
        const SDL_Point starCenter;
        const int starRadiusW, starRadiusH;
        const SDL_Color starColor;
};
