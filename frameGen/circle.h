#include <SDL.h>

class Circle{
    public:
        /* Circle x and y coordinates, width and height, 
         * and SDL color choice.
         */
        Circle(const SDL_Point, const int, const int, const SDL_Color);
        void draw(SDL_Renderer* renderer);

    private:
        SDL_Point circleCenter;
        int circleRadiusW, circleRadiusH;
        SDL_Color circleColor;
};
