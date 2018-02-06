#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "window.h"
#include "colorPalette.h"
#include "brick.h"
#include "star.h"

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

    // Left and right trimming of window.
    for( int totalVertTrim = 0; totalVertTrim < 2; totalVertTrim++)
    {
        int trimX = positionX - trimSpacing + (width * totalVertTrim);
        int trimY = positionY;

        Brick trimBrick(trimX, trimY, trimSpacing, height);
        trimBrick.draw(renderer);
    }
    // Top and bottom trimming of window.
    for( int totalHoriTrim = 0; totalHoriTrim < 2; totalHoriTrim++)
    {
        int trimX = positionX;
        int trimY = positionY - trimSpacing + (height * totalHoriTrim);

        Brick trimBrick(trimX, trimY, width - trimSpacing, trimSpacing);
        trimBrick.draw(renderer);
    }

     
}
