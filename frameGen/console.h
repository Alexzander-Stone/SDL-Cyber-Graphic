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
        // Try to change var's to const later. 
        int consoleWidth, consoleHeight;
        int positionX, positionY;
};
