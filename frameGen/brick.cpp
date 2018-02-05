#include <iostream>
#include <math.h>
#include "brick.h"
#include "colorPalette.h"

Brick::Brick( const int posX, const int posY, 
              const int bW, const int bH)
            : positionX(posX), positionY(posY), 
              brickW(bW), brickH(bH)
{
}

void Brick::draw(SDL_Renderer* renderer)
{

    ColorPalette palette;
    palette.addPalette(0, 50, 0); // Brick Background color
    palette.addPalette(0, 0, 0); // Brick spacing/divet color



    // Color in the background of the brick tile
    SDL_Rect brickBackground;

    brickBackground.w = brickW;
    brickBackground.h = brickH;
    brickBackground.x = positionX;
    brickBackground.y = positionY;

    SDL_SetRenderDrawColor(renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
    SDL_RenderFillRect(renderer, &brickBackground);

    // Add lines to create the divets in the bricks
    SDL_SetRenderDrawColor(renderer, palette.getR(1), palette.getG(1), palette.getB(1), 255);
    
    // Horizontal lines
    // -1 is used as an offset
    for(int row = 0; row < 5; row++)
    {
        int lineBeginX = positionX;
        int lineBeginY = positionY + (row * (brickH / 5));
        int lineEndX = lineBeginX + brickW - 1;
        int lineEndY = lineBeginY;

        // Render horizontal lines
        SDL_RenderDrawLine(renderer, lineBeginX, lineBeginY, 
                           lineEndX, lineEndY);

        // Vertical lines
        for(int col = 0; col < 2; col++)
        {
            // Alternate each line location (similar to honeycomb effect).
            lineBeginX = positionX + (brickH *.25) + (col * brickH * .5) 
                         + (row%2?0:1 * (brickH * .25)) - 1;
            lineEndX = lineBeginX;
            lineEndY = lineBeginY + (brickH/5) - 1;
        
            // Render vertical lines
            SDL_RenderDrawLine(renderer, lineBeginX, lineBeginY, 
                               lineEndX, lineEndY);
        }
    }
    

}
