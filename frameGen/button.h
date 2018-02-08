#include <SDL.h>
#include "colorPalette.h"
class Button{
    public:
        /* Button width radius, Button height radius,
         * Button coordinates, Rectangle to link button,
         * and Color palette. */ 
        Button(const int, const int, const SDL_Point, 
               const SDL_Rect, const ColorPalette);
        void draw(SDL_Renderer* renderer);

    private:
        const int ellipseRadiusW, ellipseRadiusH;
        SDL_Point ellipseCenter;
        SDL_Rect squareButton;
        const ColorPalette palette;
        static int buttonCounter;
};
