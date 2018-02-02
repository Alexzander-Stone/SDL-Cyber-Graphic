#include <iostream>
#include <math.h>
#include "console.h"
#include "circle.h"

Console::Console(const int cWidth, const int cHeight, const int posX, const int posY) 
                : consoleWidth(cWidth), consoleHeight(cHeight), positionX(posX), positionY(posY) 
{ 
}

void Console::draw(SDL_Renderer* renderer)
{
    // Color palette for the console. Goes from darkest to brightest values.
    struct ConsoleColor
    {
        Uint8 r;
        Uint8 g;
        Uint8 b;
    };
    ConsoleColor palette[4];
    palette[0] = {1, 13, 33};
    palette[1] = {2, 25, 65};
    palette[2] = {1, 48, 128};
    palette[3] = {0, 94, 255};

    /* Sizing Ratio */
    float widthRatio = (consoleWidth / 300.0), heightRatio = (consoleHeight / 500.0);

    /* Console base */

    // Create the rectangles postition and size.
    // Use the width and size of both the screen and the rectangle to draw to
    // the middle of the screen.
    SDL_Rect console;
    console.w = consoleWidth;
    console.h = consoleHeight;
    console.x = positionX;
    console.y = positionY;

    // Set the color of the console and draw to the canvas.
    SDL_SetRenderDrawColor( renderer, palette[1].r, palette[1].g, palette[1].b, 255); 
    SDL_RenderDrawRect(renderer, &console);
    SDL_RenderFillRect( renderer, &console );    
    





    /* Slanted surfaces */
    SDL_Rect slantedSurface;

    // Slant at top of console.
    slantedSurface.w = consoleWidth;
    slantedSurface.h = 8 * heightRatio;
    slantedSurface.x = positionX;
    slantedSurface.y = positionY;

    SDL_SetRenderDrawColor( renderer, palette[2].r, palette[2].g, palette[2].b, 255);
    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);

    // Dark slant at bottom of console.
    slantedSurface.y = positionY + consoleHeight;

    SDL_SetRenderDrawColor( renderer, palette[0].r, palette[0].g, palette[0].b, 255);
    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);

    // Slant at middle of console.
    slantedSurface.w = 200 * widthRatio;
    slantedSurface.h = 50 * heightRatio;
    slantedSurface.x = positionX;
    slantedSurface.y = positionY + (300 * heightRatio);

    SDL_SetRenderDrawColor( renderer, palette[2].r, palette[2].g, palette[2].b, 255);
    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);
   
    



    /* Buttons */
    int circleRadiusW = 10 * widthRatio;
    int circleRadiusH = 10 * heightRatio;
    
    for (int i = 0; i <= 9; i++)
    {
        SDL_Point circleCenter = {positionX + circleRadiusW + (10 * i), 
                              positionY + (int)(300 * heightRatio) + circleRadiusH};
        SDL_Color circleColor = {palette[0].r, palette[0].g, palette[0].b, 255};
    
        Circle firstCircle(circleCenter, circleRadiusW, circleRadiusH, circleColor);
        firstCircle.draw(renderer);
    }





    /* Terminals */
    // Default size created for console. Helps for resizing.
    SDL_Rect terminal;
     
    float terminalDownsizeX = 50 * widthRatio;
    float terminalDownsizeY = 50 * heightRatio;

    terminal.w = terminalDownsizeX;
    terminal.h = terminalDownsizeY;
     
    std::cout << "terminal width: " << terminal.w << "    terminal height: " 
              << terminal.h << std::endl;

    // Fill the rectangle with color.
    // Set the color of the rectangle then draw the rectangle to the renderer.
    SDL_SetRenderDrawColor( renderer, palette[0].r, palette[0].g, palette[0].b, 255);
    
    // Create four terminals by reusing the terminal values while chaning the x
    // and y. 
    // Border is the pixels between the edge of the console and the terminals.
    // Spacing is the pixels between each edge of the terminals.
    float terminalBorderX = 10 * widthRatio;
    float terminalBorderY = 10 * heightRatio; 
    float terminalSpacingX = 65 * widthRatio;
    float terminalSpacingY = 65 * heightRatio;


    std::cout << "downsize: " << terminalDownsizeX << " and " << terminalDownsizeY 
              << "    border: " << terminalBorderX << " and " << terminalBorderY 
              << "    spacing x and y: " << terminalSpacingX 
              << " and " << terminalSpacingY << std::endl;
    
    for(int xTransform = 0; xTransform < 2; xTransform++)
    {
        for(int yTransform = 0; yTransform < 2; yTransform++)
        {
            terminal.x = console.x + terminalBorderX + (terminalSpacingX * xTransform);
            terminal.y = console.y + terminalBorderY + (terminalSpacingY * yTransform);
         
            SDL_RenderDrawRect(renderer, &terminal); 
            SDL_RenderFillRect(renderer, &terminal);
        }
    }
    
 
}
