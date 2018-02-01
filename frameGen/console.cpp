#include <iostream>
#include <math.h>
#include "console.h"

const float PI = 3.14159265;

Console::Console(const int cWidth, const int cHeight, const int posX, const int posY) 
                : consoleWidth(cWidth), consoleHeight(cHeight), positionX(posX), positionY(posY) 
{ 
}

void Console::draw(SDL_Renderer* renderer)
{
    // Color palette for the console. Goes from darkest to brightest values.
    struct ConsoleColor
    {
        int r;
        int g;
        int b;
    };
    ConsoleColor palette[4];
    palette[0] = {1, 13, 33};
    palette[1] = {2, 25, 65};
    palette[2] = {1, 48, 128};
    palette[3] = {0, 94, 255};


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
    slantedSurface.w = consoleWidth;
    slantedSurface.h = consoleHeight;
    



    /* Terminals */
    // Default size created for console. Helps for resizing.
    SDL_Rect terminal;
    
    float terminalWidthRatio = (consoleWidth / 300.0), terminalHeightRatio = (consoleHeight / 500.0); 
    float terminalDownsizeX = 50 * terminalWidthRatio;
    float terminalDownsizeY = 50 * terminalHeightRatio;

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
    float terminalBorderX = 10 * terminalWidthRatio;
    float terminalBorderY = 10 * terminalHeightRatio; 
    float terminalSpacingX = 65 * terminalWidthRatio;
    float terminalSpacingY = 65 * terminalHeightRatio;


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
