#include <iostream>
#include <math.h>
#include "brick.h"

Brick::Brick( const int posX, const int posY, 
              const int bW, const int bH)
            : positionX(posX), positionY(posY), 
              brickW(bW), brickH(bH)
{
}

void Brick::draw(SDL_Renderer* renderer)
{
    // Color in the background of the brick tile
    SDL_Rect brickBackground;

    brickBackground.w = brickW;
    brickBackground.h = brickH;
    brickBackground.x = positionX;
    brickBackground.y = positionY;

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &brickBackground);
}
