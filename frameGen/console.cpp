#include <iostream>
#include <math.h>
#include "console.h"
#include "circle.h"
#include "button.h"
//#include "colorPalette.h"

Console::Console(const int cWidth, const int cHeight, const int posX, const int posY) 
                : consoleWidth(cWidth), consoleHeight(cHeight), positionX(posX), positionY(posY) 
{ 
}

void Console::draw(SDL_Renderer* renderer)
{
    ColorPalette palette;
    palette.addPalette(1, 13, 33); // Background
    palette.addPalette(1, 18, 45); // Detail (Button)
    palette.addPalette(2, 25, 65); // Detail (Console Base)
    palette.addPalette(1, 48, 128); // Highlight (Slants)
    palette.addPalette(0, 94, 255); // Super Bright

    /* Sizing Ratio */
    float widthRatio = (consoleWidth / 320.0), heightRatio = (consoleHeight / 540.0);

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
    SDL_SetRenderDrawColor( renderer, palette.getR(2), 
                            palette.getG(2), palette.getB(2), 255); 
    SDL_RenderDrawRect(renderer, &console);
    SDL_RenderFillRect( renderer, &console );    

    


    //Slanted surfaces
    SDL_Rect slantedSurface;

    // Slant at top of console.
    slantedSurface.w = consoleWidth;
    slantedSurface.h = 8 * heightRatio;
    slantedSurface.x = positionX;
    slantedSurface.y = positionY;

    SDL_SetRenderDrawColor( renderer,
                            palette.getR(3), palette.getG(3), palette.getB(3), 255);



    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);

    // Dark slant at bottom of console.
    slantedSurface.y = positionY + consoleHeight;
    
    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);
    
    // Slant at middle of console.
    slantedSurface.w = 200 * widthRatio;
    slantedSurface.h = 50 * heightRatio;
    slantedSurface.x = positionX;
    slantedSurface.y = positionY + (300 * heightRatio);
    
    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);
       
        
        
    /* Buttons */
    float ellipseRadiusW = 10 * widthRatio;
    float ellipseRadiusH = 9 * heightRatio;
    float buttonSpacing = 5 * heightRatio;    

    // The amount of buttons placed will be determined by the size of the
    // canvas it's sitting on (width).
    int colMax = slantedSurface.w / (ellipseRadiusW*2 + buttonSpacing);

    // Square button setup.
    SDL_Rect squareButton;

    // Square button on slanted surface.
    squareButton.w = 18 * widthRatio;
    squareButton.h = 18 * heightRatio;


    for (int rows = 0; rows <= 1; rows++)
    {
        int col = 0;

        // Circle Buttons
        for (col = 0; col < colMax-3; col++)
        {
            
            SDL_Point buttonCenter = {(int)(positionX + (col * ellipseRadiusW*2) 
                                      + ellipseRadiusW + (col * buttonSpacing)), 
                                      (int)(positionY + (int)(300 * heightRatio) 
                                      + ellipseRadiusH + (rows * ellipseRadiusH*2) 
                                      + (rows * buttonSpacing))};
            std::cout << "positionx: " << positionX << " ellipseRadiusW: " 
                      << ellipseRadiusW << " x is " << buttonCenter.x 
                      << "and y is " << buttonCenter.y << std::endl;

            Button consoleButton(ellipseRadiusW, ellipseRadiusH, 
                                 buttonCenter, squareButton, 
                                 palette);
            consoleButton.draw(renderer);
        }

        // Square Buttons
        while(col < colMax)
        {
            squareButton.x = positionX + (col * squareButton.w) + (col * buttonSpacing) 
                             + (widthRatio * 12);
            squareButton.y = positionY + (int)(303 * heightRatio) + (rows * squareButton.h)
                             + (rows * buttonSpacing);

            SDL_RenderDrawRect(renderer, &squareButton);
            SDL_RenderFillRect(renderer, &squareButton);

            col++;
        }
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
            
    // Set the color of the rectangle then draw the rectangle to the renderer.
    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
        
    // Create four terminals by reusing the terminal values while chaning the x
    // and y. 
    // Border is the pixels between the edge of the console and the terminals.
    // Spacing is the pixels between each edge of the terminals.
    float terminalBorderX = 10 * widthRatio;
    float terminalBorderY = 10 * heightRatio; 
    float terminalSpacingX = 65 * widthRatio;
    float terminalSpacingY = 65 * heightRatio;
    
        
    std::cout << "downsize: " << terminalDownsizeX << " and " 
              << terminalDownsizeY << "    border: " << terminalBorderX 
              << " and " << terminalBorderY 
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
