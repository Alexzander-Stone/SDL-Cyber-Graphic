#include <iostream>
#include <math.h>
#include <SDL.h>
#include "trim.h"
#include "button.h"
#include "line.h"

Trim::Trim(const int posX, const int posY, const int trimW, const int trimH)
              :positionX(posX), positionY(posY),
               width(trimW), height(trimH)
{
}

// Needs lighter color than brick background.
void Trim::draw(SDL_Renderer* renderer)
{
    // Color palette to use.
    ColorPalette palette;
    palette.addPalette(0, 0, 30); // Sin curve detailing
    palette.addPalette(0, 0, 50); // Trim background
    palette.addPalette(0, 0, 50); // Inside Rectangle detailing
    palette.addPalette(0, 0, 70); // Outside Rectangle detailing

    // Base background for trim.
    SDL_Rect trimBackground;

    trimBackground.w = width;
    trimBackground.h = height;
    trimBackground.x = positionX;
    trimBackground.y = positionY; 

    SDL_SetRenderDrawColor(renderer, palette.getR(1), palette.getG(1), palette.getB(1), 255);
    SDL_RenderDrawRect(renderer, &trimBackground);
    SDL_RenderFillRect(renderer, &trimBackground);

    // Add detail to the trimming.
    
    // Sin wave detailing, create two sets on top and bottom of trim.
    Line sinDetail(renderer);
    float sinLength = 5;

    SDL_SetRenderDrawColor(renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
    for(int yChange = 0; yChange < 2; yChange++)
    {
        sinDetail.drawCosLine(50, sinLength, positionX, positionY + sinLength + (sinLength * 2 * yChange));
        sinDetail.drawSinLine(50, sinLength, positionX, positionY + sinLength + (sinLength * 2 * yChange));
    }

    // Large Detailing
    int detailWidth = 30, detailHeight = 40, detailY = trimBackground.y;
    int detailSpacing = 100;
    int totalDetails = width / detailSpacing + 1; // Offset, needed to extend across screen.
    
    int indentSpacing = 5; // Used for indents on rectangles for depth.

    
    for(int detailX = 0; detailX < totalDetails; detailX++)
    {
        // Outer Rectangle
        trimBackground.y = detailY - 20; // Based on FLOOR_HEIGHT
        trimBackground.x = detailX * detailSpacing;
        trimBackground.w = detailWidth;
        trimBackground.h = detailHeight;
    
        SDL_SetRenderDrawColor(renderer, palette.getR(3), palette.getG(3), palette.getB(3), 255);
        SDL_RenderDrawRect(renderer, &trimBackground);
        SDL_RenderFillRect(renderer, &trimBackground);

        // Inner Rectangle
        trimBackground.y = detailY - 20 + indentSpacing; // Based on FLOOR_HEIGHT
        trimBackground.x = detailX * detailSpacing + indentSpacing;
        trimBackground.w = detailWidth - indentSpacing*2;
        trimBackground.h = detailHeight - indentSpacing*2;
    
        SDL_SetRenderDrawColor(renderer, palette.getR(2), palette.getG(2), palette.getB(2), 255);
        SDL_RenderDrawRect(renderer, &trimBackground);
        SDL_RenderFillRect(renderer, &trimBackground);
/*
        SDL_Point trimCenter = {trimBackground.x, trimBackground.y};
        Button trimButton(30, 10,trimCenter, trimBackground, ColorPalette(5,5,5));
        trimButton.draw(renderer);
*/
    }
    
    
}
