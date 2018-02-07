#include <SDL.h>

class Trim{
    public:
        /* Trim position x and y coordinates, width and height.
         */
        Trim(const int, const int, const int, const int);
        void draw(SDL_Renderer* renderer);

    private:
        const int positionX, positionY, width, height;
};
