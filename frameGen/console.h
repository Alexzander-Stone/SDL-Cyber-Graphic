#include <SDL.h>

class Console{
    
    public:
        /* Console width and height, 
         * and console x and y coordinates 
         */
        Console(const int, const int, 
                const int, const int);
        void draw(SDL_Renderer*);

    private:
        const int consoleWidth, consoleHeight;
        const int positionX, positionY;
};
