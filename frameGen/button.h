#include <SDL.h>

class Button{
    public:
        /* Button x&y point, color palette, width radius, and height radius. */ 
        Button(const SDL_Point, const ConsoleColor, const int, const int);
        void draw(SDL_Renderer* renderer);

    private:
        int ellipseRadiusW, ellipseRadiusH;
        SDL_Point eclipseCenter;
        ConsoleColor palette;
};
