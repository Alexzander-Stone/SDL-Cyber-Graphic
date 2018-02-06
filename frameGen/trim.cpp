#include <iostream>
#include <math.h>
#include <SDL.h>
#include "trim.h"
#include "button.h"

Trim::Trim(const int posX, const int posY, const int trimW, const int trimH)
              :positionX(posX), positionY(posY),
               width(trimW), height(trimH)
{
}

// Needs lighter color than brick background.
void Trim::draw(SDL_Renderer* renderer)
{
    // Base background for trim.
    SDL_Rect trimBackground;

    trimBackground.w = width;
    trimBackground.h = height;
    trimBackground.x = positionX;
    trimBackground.y = positionY; 

    SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &trimBackground);
    SDL_RenderFillRect(renderer, &trimBackground);
    
    // Add detail to the trimming.
    int detailWidth = 30, detailHeight = 40;
    int detailSpacing = 100;
    int totalDetails = width / detailSpacing + 1; // Offset
    
    trimBackground.w = detailWidth;
    trimBackground.h = detailHeight;
    trimBackground.y -= 20; // Based on FLOOR_HEIGHT
    
    for(int detailX = 0; detailX < totalDetails; detailX++)
    {
        trimBackground.x = detailX * detailSpacing;
    
        SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
        SDL_RenderDrawRect(renderer, &trimBackground);
        SDL_RenderFillRect(renderer, &trimBackground);
/*
        SDL_Point trimCenter = {trimBackground.x, trimBackground.y};
        Button trimButton(30, 10,trimCenter, trimBackground, ColorPalette(5,5,5));
        trimButton.draw(renderer);
*/
    }
}
