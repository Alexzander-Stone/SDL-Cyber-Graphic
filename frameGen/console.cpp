#include <iostream>
#include <math.h>
#include "console.h"
#include "circle.h"
#include "button.h"
#include "backLayer.h"
#include "star.h"
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
    palette.addPalette(2, 34, 85); // Detail (Console Base)
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
    slantedSurface.w = consoleWidth;//200 * widthRatio;
    slantedSurface.h = 100 * heightRatio;
    slantedSurface.x = positionX;
    slantedSurface.y = positionY + (250 * heightRatio);
    
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


    for (int rows = 0; rows <= 2; rows++)
    {
        int col = 0;

        // Circle Buttons
        for (col = 0; col < colMax-3; col++)
        {
            
            SDL_Point buttonCenter = {(int)(positionX + (col * ellipseRadiusW*2) 
                                      + ellipseRadiusW + (col * buttonSpacing)) + (int)(5 * widthRatio), 
                                      (int)(positionY + (int)(250 * heightRatio) 
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
                             + (widthRatio * 30);
            squareButton.y = positionY + (int)(253 * heightRatio) + (rows * squareButton.h)
                             + (rows * buttonSpacing);

            SDL_RenderDrawRect(renderer, &squareButton);
            SDL_RenderFillRect(renderer, &squareButton);

            col++;
        }
    }

    // Space bar
    int spaceBarOffsetX = 10 * widthRatio;
    squareButton.x = slantedSurface.x + spaceBarOffsetX;
    squareButton.y = slantedSurface.y + (slantedSurface.h*.75);
    squareButton.w = consoleWidth - spaceBarOffsetX*2;
    
    // render space marines.
    SDL_RenderDrawRect(renderer, &squareButton);
    SDL_RenderFillRect(renderer, &squareButton);
    
    // Space bar depth
    squareButton.x = slantedSurface.x + spaceBarOffsetX;
    squareButton.y = slantedSurface.y + (slantedSurface.h*.75) + squareButton.h/2;
    squareButton.w = consoleWidth - spaceBarOffsetX*2;
    squareButton.h = 5 * heightRatio;
    
    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
    SDL_RenderDrawRect(renderer, &squareButton);
    SDL_RenderFillRect(renderer, &squareButton);


    /* Terminals */
    // Default size created for console. Helps for resizing.
    SDL_Rect terminal;
    
    float terminalDownsizeX = 100 * widthRatio;
    float terminalDownsizeY = 100 * heightRatio;
    
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
    float terminalSpacingX = (terminalDownsizeX + 10) * widthRatio;
    float terminalSpacingY = (terminalDownsizeX + 10) * heightRatio;
    
        
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
            
            std::cout << "terminal.x : " << terminal.x << " terminal.y : " << terminal.y << " console.y " << console.y << " terminalBorderY" << terminalBorderY  << std::endl;

            SDL_RenderDrawRect(renderer, &terminal); 
            SDL_RenderFillRect(renderer, &terminal);
        }
    }

    /* Speakers */
    for( int colSpeakers = 0; colSpeakers < 10; colSpeakers++)
    {
        for(int rowSpeakers = 0; rowSpeakers < 10; rowSpeakers++)
        {
            SDL_Point speakerGrillCenter = {console.x + console.w, terminal.y}; 
            Circle speakerGrill();




        }
    }


    /* Special effects on terminals */
    
    // Sin wave effect
    BackLayer terminalSinWave(renderer);
    SDL_SetRenderDrawColor(renderer, palette.getR(4), palette.getG(4), palette.getB(4), 255);
    terminalSinWave.createCosLine(1, terminalDownsizeX/7, terminal.x+(5*widthRatio), terminal.y+(terminalDownsizeY/2));
    
    // Star effect
    // Place on top left terminal
    int starWidth = 50 * widthRatio;
    int starHeight = 50 * heightRatio;
    SDL_Point starPoint= {(int)(terminal.x - terminalSpacingX/2)-(int)(5*widthRatio), (int)(terminal.y - terminalSpacingY/2)-(int)(5*heightRatio)};
    SDL_Color starColor = {palette.getR(4), palette.getG(4), palette.getB(4), 255};
    Star terminalStar(starPoint, starWidth, starHeight, starColor); 
    terminalStar.draw(renderer);

    /* Drawers */
    SDL_Rect drawer;
    
    float drawerDownsizeWidth = 80 * widthRatio;
    float drawerDownsizeHeight = 35 * heightRatio;
    float drawerSpacing = 10 * heightRatio; 
    float drawerRimOffsetWidth = 10 * widthRatio;
    float drawerRimOffsetHeight = 10 * heightRatio;

    // Create three drawers.
    for( int numbDrawers = 0; numbDrawers < 4; numbDrawers++)
    {
        // Outside rim of drawer 
        drawer.w = drawerDownsizeWidth;
        drawer.h = drawerDownsizeHeight;
        drawer.y = positionY + (360 * heightRatio) + (numbDrawers * drawer.h) 
                   + (numbDrawers * drawerSpacing);
        drawer.x = positionX + (20 * widthRatio);

        SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
        SDL_RenderDrawRect(renderer, &drawer); 
        SDL_RenderFillRect(renderer, &drawer);

        // Inside of drawer 
        drawer.w = drawerDownsizeWidth - drawerRimOffsetWidth;
        drawer.h = drawerDownsizeHeight - drawerRimOffsetHeight;
        drawer.y += drawerRimOffsetHeight/2;
        drawer.x += drawerRimOffsetWidth/2;

        SDL_SetRenderDrawColor( renderer, palette.getR(2), palette.getG(2), palette.getB(2), 255);
        SDL_RenderDrawRect(renderer, &drawer); 
        SDL_RenderFillRect(renderer, &drawer);

        // Handle of drawer
        drawer.w = drawerDownsizeWidth / 5;
        drawer.h = drawerDownsizeHeight / 5;
        drawer.x += 45 * widthRatio;
        drawer.y += 10 * heightRatio;

        SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
        SDL_RenderDrawRect(renderer, &drawer); 
        SDL_RenderFillRect(renderer, &drawer);
    }

    // Create one large drawer/cabinet.
    drawer.w = 150 * widthRatio;
    drawer.h = 170 * heightRatio;
    drawer.x = positionX + (150 * widthRatio);
    drawer.y = positionY + (360 * heightRatio);
    
    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
    SDL_RenderDrawRect(renderer, &drawer); 
    SDL_RenderFillRect(renderer, &drawer);
    
    // Inside of drawer 
    drawer.w -= drawerRimOffsetWidth;
    drawer.h -= drawerRimOffsetHeight;
    drawer.y += drawerRimOffsetHeight/2;
    drawer.x += drawerRimOffsetWidth/2;

    SDL_SetRenderDrawColor( renderer, palette.getR(2), palette.getG(2), palette.getB(2), 255);
    SDL_RenderDrawRect(renderer, &drawer); 
    SDL_RenderFillRect(renderer, &drawer);

    // Handle of drawer
    drawer.w = drawerDownsizeWidth / 2;
    drawer.h = drawerDownsizeHeight / 2;
    drawer.x += 20 * widthRatio;
    drawer.y += 60 * heightRatio;

    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
    SDL_RenderDrawRect(renderer, &drawer); 
    SDL_RenderFillRect(renderer, &drawer);

     
}
