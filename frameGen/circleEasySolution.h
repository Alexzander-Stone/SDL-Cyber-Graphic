#include <SDL.h>

class CircleEasySolution{
    public:
        /* Circle x and y coordinates, width and height, 
         * and SDL color choice.
         */
        CircleEasySolution(const SDL_Point, const int, const int, const SDL_Color);
        void draw(SDL_Renderer* renderer);

    private:
        const SDL_Point circleCenter;
        const int circleRadiusW, circleRadiusH;
        const SDL_Color circleColor;
};
