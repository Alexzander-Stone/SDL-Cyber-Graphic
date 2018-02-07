#include <SDL.h>

class Brick{
    public:
        /* Brick position x and y coordinates, width and height.
         */
        Brick(const int, const int, const int, const int);
        void draw(SDL_Renderer* renderer);

    private:
        const int positionX, positionY, brickW, brickH;
};
