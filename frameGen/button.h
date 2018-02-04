#include <SDL.h>
#include "colorPalette.h"
class Button{
    public:
        /* Button x&y point, color palette, 
         * ellipse width radius, ellipse height radius,
         * rectangle width radius, ellipse height Radius. */ 
        Button(const SDL_Point, const ColorPalette, 
               const int, const int, const SDL_Rect);
        void draw(SDL_Renderer* renderer);

    private:
        int ellipseRadiusW, ellipseRadiusH;
        SDL_Point ellipseCenter;
        SDL_Rect squareButton;
        ColorPalette palette;
};
