#include <SDL.h>

class Window{
    public:
        /* Window width and height, position x and y coordinates 
         * and SDL color choice.
         */
        Window(const int, const int, const int, const int);
        void draw(SDL_Renderer* renderer);

    private:
        const int positionX, positionY;
        const int width, height;
};
