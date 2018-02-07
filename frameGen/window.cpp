#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "window.h"
#include "brick.h"
#include "star.h"
#include "button.h"

Window::Window(const int posX, const int posY, const int windowW, const int windowH)
              : positionX(posX), positionY(posY), 
                width(windowW), height(windowH)
{
    srand(time(0));
}

void Window::draw(SDL_Renderer* renderer)
{
    ColorPalette palette;
    palette.addPalette(0, 0, 0); // Black background
    palette.addPalette(244, 252, 126); // Star color
    palette.addPalette(0, 0, 0); // Button rect
    palette.addPalette(60, 60, 60); // Bottom curtain
    palette.addPalette(120, 120, 120); // Top curtain 

    // Background of window, clear black.
    SDL_Rect windowBackground;

    windowBackground.w = width;
    windowBackground.h = height;
    windowBackground.x = positionX;
    windowBackground.y = positionY;

    SDL_SetRenderDrawColor(renderer, palette.getR(0), palette.getG(0), 
                           palette.getB(0), 255);
    SDL_RenderDrawRect(renderer, &windowBackground);
    SDL_RenderFillRect(renderer, &windowBackground);

    /* Create stars in window */
    
    for(int totalStars = 0; totalStars < 10; totalStars++)
    {
        int starWidth = 50 - rand()%30, starHeight = 50 - rand()%30;
        int starX = positionX + 25 + rand()%(width - (int)(50*1.5));
        int starY = positionY + 25 + rand()%(height - (int)(50*1.5));
        SDL_Point starCenter = {starX, starY};

        SDL_Color color = {palette.getR(1), palette.getG(1), palette.getB(1), 128};
        Star star( starCenter, starWidth, starHeight, color );
        star.draw(renderer);
    }

    /* Trimming */
    int trimSpacing = 10;

    // Top and bottom trimming of window.
    for( int totalHoriTrim = 0; totalHoriTrim < 2; totalHoriTrim++)
    {
        int trimX = positionX;
        int trimY = positionY - trimSpacing + (height * totalHoriTrim);

        Brick trimBrick(trimX, trimY, width - trimSpacing, trimSpacing);
        trimBrick.draw(renderer);
    }

    // Left and right trimming of window.
    SDL_Rect buttonRect;
    buttonRect.w = 10;
    buttonRect.h = 10;

    for( int totalVertTrim = 0; totalVertTrim < 2; totalVertTrim++)
    {
        int trimX = positionX - trimSpacing+5 + (width * totalVertTrim);
        int trimY = positionY;

        SDL_Point buttonLocation = {trimX, trimY + height/2};

        Button trimButton(trimSpacing*2, height/2,
                          buttonLocation, buttonRect,
                          palette);
        trimButton.draw(renderer);
    } 
}
