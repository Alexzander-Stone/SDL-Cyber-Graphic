#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "brick.h"
#include "colorPalette.h"

Brick::Brick( const int posX, const int posY, 
              const int bW, const int bH)
            : positionX(posX), positionY(posY), 
              brickW(bW), brickH(bH)
{
    srand(time(0));
}

void Brick::draw(SDL_Renderer* renderer)
{

    ColorPalette palette;
    palette.addPalette(0, 50, 0); // Brick Background 
    palette.addPalette(0, 0, 0); // Brick spacing/divet 
    palette.addPalette(0, 100, 0); // Brick highlight
    palette.addPalette(0, 20, 0); // Brick shadow/lowlight

    // Color in the background of the brick tile
    SDL_Rect brickBackground;

    brickBackground.w = brickW;
    brickBackground.h = brickH;
    brickBackground.x = positionX;
    brickBackground.y = positionY;

    SDL_SetRenderDrawColor(renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
    SDL_RenderFillRect(renderer, &brickBackground);

    // Add lines to create the divets in the bricks.
    // Include the lowlights and highlights for the bricks.
    // -1 is used as an offset
    for(int row = 0; row < 5; row++)
    {
        // Horizontal lines
        int lineBeginX = positionX;
        int lineBeginY = positionY + (int)(row * (brickH / 5));
        int lineEndX = lineBeginX + brickW - 1;
        int lineEndY = lineBeginY;
        
        SDL_SetRenderDrawColor(renderer, palette.getR(1), palette.getG(1), 
                               palette.getB(1), 255);
        SDL_RenderDrawLine(renderer, lineBeginX, lineBeginY, 
                           lineEndX, lineEndY);
        
        // Add a highlight to the bottom of each line and shadow
        // to the top of each line to give depth.
        // Give the highlight thickness/width.
        for(int depthThickness = 1; depthThickness < 3; depthThickness++)
        {
            // Highlight
            int depthBeginY = lineBeginY + depthThickness;
            int depthEndY = depthBeginY;

            SDL_SetRenderDrawColor(renderer, palette.getR(2), palette.getG(2), 
                               palette.getB(2), 155);
            SDL_RenderDrawLine(renderer, lineBeginX, depthBeginY, 
                               lineEndX, depthEndY);

            // Shadow/low light
            depthBeginY = lineBeginY - depthThickness;
            depthEndY = depthBeginY;

            SDL_SetRenderDrawColor(renderer, palette.getR(3), palette.getG(3), 
                               palette.getB(3), 155);
            SDL_RenderDrawLine(renderer, lineBeginX, depthBeginY, 
                               lineEndX, depthEndY);
        }


        // Vertical lines
        SDL_SetRenderDrawColor(renderer, palette.getR(1), palette.getG(1), 
                               palette.getB(1), 255);
        for(int col = 0; col < 2; col++)
        {
            // Alternate each line location (similar to honeycomb effect).
            lineBeginX = positionX + (brickH *.25) + (col * brickH * .5) 
                         + (row%2?0:1 * (brickH * .25)) - 1;
            lineEndX = lineBeginX;
            lineEndY = lineBeginY + (brickH/5) - 1;
        
            SDL_RenderDrawLine(renderer, lineBeginX, lineBeginY, 
                               lineEndX, lineEndY);
        }
    }
    
    // Dithering, creates roughness and texture on the brick.
    // Randomly made.
    for(int numbDithers = 0; numbDithers < 1000; numbDithers++)
    {
        int ditherX = positionX + rand()%(brickW-1);
        int ditherY = positionY + rand()%(brickH-1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 
                               0, rand()%255 + 1);
        SDL_RenderDrawPoint(renderer, ditherX, ditherY);
    }
    

}
