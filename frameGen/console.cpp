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
    palette[0] = {1, 13, 33}; // Background
    palette[1] = {1, 18, 45}; // Detail (Button)
    palette[2] = {2, 25, 65}; // Detail (Console Base)
    palette[3] = {1, 48, 128}; // Highlight (Slants)
    palette[4] = {0, 94, 255}; // Super Bright

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
    SDL_SetRenderDrawColor( renderer, palette[2].r, palette[2].g, palette[2].b, 255); 
    SDL_RenderDrawRect(renderer, &console);
    SDL_RenderFillRect( renderer, &console );    
    





    /* Slanted surfaces */
    SDL_Rect slantedSurface;

    // Slant at top of console.
    slantedSurface.w = consoleWidth;
    slantedSurface.h = 8 * heightRatio;
    slantedSurface.x = positionX;
    slantedSurface.y = positionY;

    SDL_SetRenderDrawColor( renderer, palette[3].r, palette[3].g, palette[3].b, 255);
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

    SDL_SetRenderDrawColor( renderer, palette[3].r, palette[3].g, palette[3].b, 255);
    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);
   
    



    /* Buttons */
    int ellipseRadiusW = 10 * widthRatio;
    int ellipseRadiusH = 10 * heightRatio;
    int buttonSpacing = 5 * heightRatio;
   
    // col max, to allow for more buttons.
    int colMax = slantedSurface.w / (ellipseRadiusW*2 + buttonSpacing);

    // Square button setup.
    SDL_Rect squareButton;

    // Square button on slanted surface.
    squareButton.w = 18 * widthRatio;
    squareButton.h = 18 * heightRatio;
     

    for(int rows = 0; rows <= 1; rows++)
    {
        int col;
        // Circle Buttons
        for (col = 0; col < colMax - 3; col++)
        {
            // Create the ellipsis at the bottom of the button.
            SDL_Point ellipseCenter = {positionX + (col * ellipseRadiusW*2) + ellipseRadiusW 
                                      + (col * buttonSpacing), positionY + (int)(300 * heightRatio) 
                                      + ellipseRadiusH + (rows * ellipseRadiusH*2) + (rows * buttonSpacing)
                                      };
            SDL_Color ellipseColor = {palette[0].r, palette[0].g, palette[0].b, 255};
            Circle bottomButtonEllipse(ellipseCenter, ellipseRadiusW, ellipseRadiusH, ellipseColor);

            // Top of the buttons.
            ellipseCenter = {positionX + (col * ellipseRadiusW*2) + ellipseRadiusW 
                            + (col *buttonSpacing), 
                            positionY + (int)(300 * heightRatio) + ellipseRadiusH 
                            + (rows * ellipseRadiusH*2) + (rows * buttonSpacing)
                            - (ellipseRadiusH/4) - (int)(5 * heightRatio)};
            ellipseColor = {palette[1].r, palette[1].g, palette[1].b, 255};
            Circle topButtonEllipse(ellipseCenter, ellipseRadiusW, ellipseRadiusH, ellipseColor);

            // Add depth to the bottom of the buttons.
            SDL_SetRenderDrawColor( renderer, palette[0].r, palette[0].g, palette[0].b, 255);
            squareButton.x = ellipseCenter.x - squareButton.w/2;
            squareButton.y = ellipseCenter.y - squareButton.h/4;   

            //Render the bottom to the top.
            SDL_RenderDrawRect(renderer, &squareButton);
            SDL_RenderFillRect(renderer, &squareButton);
            bottomButtonEllipse.draw(renderer);
            topButtonEllipse.draw(renderer);
        }
        // Square Buttons
        while(col < colMax)
        {
            // Top of the button. 
            squareButton.x = positionX + (col * squareButton.w) + (col *buttonSpacing);
            squareButton.y = positionY + (int)(303 * heightRatio) + (rows *squareButton.h)
                               +  (rows * buttonSpacing);   
            
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
