#include <SDL.h>

class Circle{
    public:
        /* Circle width and height, position x and y coordinates 
         * and SDL color choice.
         */
        Circle(const SDL_Point, const int, const int, const SDL_Color);
        void draw(SDL_Renderer* renderer);

    private:
        SDL_Point circleCenter;
        int circleRadiusW, circleRadiusH;
        SDL_Color circleColor;
};
