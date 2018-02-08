#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "console.h"
#include "circle.h"
#include "button.h"
#include "line.h"
#include "star.h"
#include "lighting.h"

const float PI = 3.14159265;

Console::Console(const int cWidth, const int cHeight, const int posX, const int posY) 
                : consoleWidth(cWidth), consoleHeight(cHeight), positionX(posX), positionY(posY) 
{ 
    srand(time(0));
}

void Console::draw(SDL_Renderer* renderer)
{
    ColorPalette palette;
    palette.addPalette(1, 13, 33); // Background
    palette.addPalette(1, 18, 45); // Detail (Button)
    palette.addPalette(20, 55, 140); // Detail (Console Base)
    palette.addPalette(1, 48, 128); // Highlight (Slants)
    palette.addPalette(0, 94, 255); // Super Bright
    palette.addPalette(60, 85, 180); // Slant at middle console
    palette.addPalette(120, 20, 20); // Red button

    /* Sizing Ratio */
    float widthRatio = consoleWidth / 320.0, heightRatio = consoleHeight / 540.0;

    /* Console base */

    // Create the rectangles postition and size.
    // Use the width and size of both the screen and the rectangle to draw to
    // the middle of the screen.
    SDL_Rect console;
    console.w = consoleWidth;
    console.h = consoleHeight;
    console.x = positionX;
    console.y = positionY;

    SDL_SetRenderDrawColor( renderer, palette.getR(2), 
                            palette.getG(2), palette.getB(2), 255); 
    SDL_RenderDrawRect(renderer, &console);
    SDL_RenderFillRect(renderer, &console);    

    /* Slanted surfaces */
    SDL_Rect slantedSurface;

    // Slant at top of console.
    slantedSurface.w = consoleWidth;
    slantedSurface.h = 8 * heightRatio;
    slantedSurface.x = positionX;
    slantedSurface.y = positionY;

    SDL_SetRenderDrawColor( renderer, palette.getR(5), palette.getG(5), 
                            palette.getB(5), 255 );
    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);

    // Dark slant at bottom of console.
    slantedSurface.y = positionY + consoleHeight;
    
    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), 
                            palette.getB(0), 255 );
    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);
    
    // Slant at middle of console.
    slantedSurface.h = 100 * heightRatio;
    slantedSurface.y = positionY + (250 * heightRatio);
    
    SDL_SetRenderDrawColor( renderer, palette.getR(5), palette.getG(5), palette.getB(5), 255);
    SDL_RenderDrawRect(renderer, &slantedSurface);
    SDL_RenderFillRect(renderer, &slantedSurface);   
        
    /* Buttons */
    float ellipseRadiusW = 10 * widthRatio;
    float ellipseRadiusH = 9 * heightRatio;
    float buttonSpacing = 5 * heightRatio;    

    // The amount of buttons placed will be determined by the size of the
    // canvas/slanted surface it's sitting on (width).
    int colMax = slantedSurface.w / (ellipseRadiusW*2 + buttonSpacing);

    // Square button setup.
    SDL_Rect squareButton;

    // Square button on slanted surface.
    squareButton.w = 18 * widthRatio;
    squareButton.h = 18 * heightRatio;

    // Create three rows of buttons.
    for (int rows = 0; rows <= 2; rows++)
    {
        int col = 0;

        // Circle Buttons
        for (col = 0; col < colMax-3; col++)
        {
            
            SDL_Point buttonCenter = { (int)(positionX + (col * ellipseRadiusW*2) 
                                       + ellipseRadiusW + (col * buttonSpacing)) 
                                       + (int)(5 * widthRatio), 
                                       (int)(positionY + (int)(250 * heightRatio) 
                                       + ellipseRadiusH + (rows * ellipseRadiusH*2) 
                                       + (rows * buttonSpacing)) };

            Button consoleButton( ellipseRadiusW, ellipseRadiusH, 
                                  buttonCenter, squareButton, 
                                  palette);
            consoleButton.draw(renderer);
            std::cout << consoleButton << std::endl;
        }

        // Square Buttons
        while(col < colMax)
        {
            squareButton.x = positionX + (col * squareButton.w) 
                             + (col * buttonSpacing) + (widthRatio * 30);
            squareButton.y = positionY + (int)(253 * heightRatio) 
                             + (rows * squareButton.h) + (rows * buttonSpacing);

            SDL_RenderDrawRect(renderer, &squareButton);
            SDL_RenderFillRect(renderer, &squareButton);
            
            col++;
        }
    }

    /* Space bar */
    int spaceBarOffsetX = 10 * widthRatio;
    squareButton.x = slantedSurface.x + spaceBarOffsetX;
    squareButton.y = slantedSurface.y + (slantedSurface.h*.75);
    squareButton.w = consoleWidth - spaceBarOffsetX*2;
    
    SDL_RenderDrawRect(renderer, &squareButton);
    SDL_RenderFillRect(renderer, &squareButton);
    
    // Space bar depth
    squareButton.x = slantedSurface.x + spaceBarOffsetX;
    squareButton.y = slantedSurface.y + (slantedSurface.h*.75) + squareButton.h/2;
    squareButton.w = consoleWidth - spaceBarOffsetX*2;
    squareButton.h = 5 * heightRatio;
    
    SDL_SetRenderDrawColor( renderer, palette.getR(5), palette.getG(5), 
                            palette.getB(5), 255);
    SDL_RenderDrawRect(renderer, &squareButton);
    SDL_RenderFillRect(renderer, &squareButton);

    /* Terminals */
    SDL_Rect terminal;
    
    float terminalDownsizeW = 100 * widthRatio;
    float terminalDownsizeH = 100 * heightRatio;
    
    terminal.w = terminalDownsizeW;
    terminal.h = terminalDownsizeH;
         
    // Set the color of the rectangle then draw the rectangle to the renderer.
    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), palette.getB(0), 255);
        
    // Create four terminals by reusing the terminal values while chaning the x
    // and y. 
    // Border is the pixels between the edge of the console and the terminals.
    // Spacing is the pixels between each edge of the terminals.
    float terminalBorderX = terminalDownsizeW / 10;
    float terminalBorderY = terminalDownsizeH / 10;  
    float terminalSpacingX = terminalDownsizeW + (10 * widthRatio);
    float terminalSpacingY = terminalDownsizeH + (10 * heightRatio);
    
    for(int xTransform = 0; xTransform < 2; xTransform++)
    {
        for(int yTransform = 0; yTransform < 2; yTransform++)
        {
            terminal.x = console.x + terminalBorderX + (terminalSpacingX * xTransform);
            terminal.y = console.y + terminalBorderY + (terminalSpacingY * yTransform);
        

            /* Lighting on terminal */
            SDL_Point lightingCenter = {terminal.x + terminal.w/2, terminal.y + terminal.h/2};
            SDL_Color lightingColor = { 0, 50, 100, 200};
            int lightCircles = 3;
            Lighting terminalLighting( lightingCenter, terminal.w/2, terminal.h/2, 
                                       lightingColor, lightCircles);
            terminalLighting.draw(renderer);

            SDL_RenderDrawRect(renderer, &terminal); 
            SDL_RenderFillRect(renderer, &terminal);
        }
    }

    /* Speakers */
    int speakerWidth = 5 * widthRatio, speakerHeight = 5 * heightRatio; 
    int speakerSpacingW = 10 * widthRatio, speakerSpacingY = 10 * heightRatio;
    SDL_Color speakerColor = {palette.getR(0), palette.getG(0), palette.getB(0), 255};

    for( int colSpeakers = 0; colSpeakers < 6; colSpeakers++)
    {
        for(int rowSpeakers = 0; rowSpeakers < 5; rowSpeakers++)
        {
            // Honeycomb effect achieved by changing starting x position during
            // each second column. 
            int speakerX = console.x + (int)(console.w*.75) + (int)(speakerSpacingW * rowSpeakers) 
                           + (int)(speakerWidth * rowSpeakers) 
                           + (colSpeakers%2?1:0 * ((int)(speakerSpacingW * rowSpeakers) 
                           + (int)(speakerWidth * rowSpeakers))+ (int)(8 * widthRatio));
            int speakerY = terminal.y + (int)(5 * heightRatio) + (int)(speakerSpacingY * colSpeakers) 
                           + (int)(speakerWidth * colSpeakers) - (int)(terminal.h/2);
            
            SDL_Point speakerGrillCenter = {speakerX, speakerY}; 

            Circle speakerGrill( speakerGrillCenter, speakerWidth, speakerHeight, 
                                 speakerColor, 2);
            speakerGrill.draw(renderer);
        }
    }


    /* Special effects on terminals. */
    
    // Sin wave effect.
    Line terminalSinWave(renderer);
    SDL_SetRenderDrawColor( renderer, palette.getR(4), palette.getG(4), 
                            palette.getB(4), 255 );
    terminalSinWave.drawSinLine(1, terminalDownsizeW/7, terminal.x+(5*widthRatio), 
                                terminal.y+(terminalDownsizeH/2), PI * 0);
    
    // Star effect on top left terminal.
    int starWidth = 50 * widthRatio;
    int starHeight = 50 * heightRatio;
    SDL_Point starPoint= { (int)(terminal.x - terminalSpacingX/2)-(int)(5*widthRatio), 
                           (int)(terminal.y - terminalSpacingY/2)-(int)(5*heightRatio) };
    SDL_Color starColor = {palette.getR(4), palette.getG(4), palette.getB(4), 255};
    Star terminalStar(starPoint, starWidth, starHeight, starColor); 
    terminalStar.draw(renderer);

    // Static on top right and bottom right terminals.
    int terminalRightX = console.x + terminalBorderX + terminalSpacingX;
    int terminalRightY = console.y + terminalBorderY;
    int terminalLeftX = console.x + terminalBorderX;
    int terminalLeftY = console.y + terminalBorderY + terminalSpacingY;
    
    int totalX = terminal.w;
    int totalY = terminal.h;
    
    SDL_SetRenderDrawColor( renderer, 255, 255, 
                                255, 90 );

    for(int currentSpotX = 0; currentSpotX < totalX; currentSpotX++)
    {
        for(int currentSpotY = 0; currentSpotY < totalY; currentSpotY++)
        {
            // Top right.
            srand(time(0) + rand());
            if(rand()%2 == 0)
                SDL_RenderDrawPoint(renderer, currentSpotX + terminalRightX, 
                                    currentSpotY + terminalRightY);
            
            // Top left.
            srand(time(0) + rand());
            if(rand()%2 == 0)
                SDL_RenderDrawPoint(renderer, currentSpotX + terminalLeftX,
                                    currentSpotY + terminalLeftY);
        }
    }

    /* Drawers. */
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

        SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), 
                                palette.getB(0), 255 );
        SDL_RenderDrawRect(renderer, &drawer); 
        SDL_RenderFillRect(renderer, &drawer);

        // Inside of drawer 
        drawer.w = drawerDownsizeWidth - drawerRimOffsetWidth;
        drawer.h = drawerDownsizeHeight - drawerRimOffsetHeight;
        drawer.y += drawerRimOffsetHeight/2;
        drawer.x += drawerRimOffsetWidth/2;

        SDL_SetRenderDrawColor( renderer, palette.getR(2), palette.getG(2), 
                                palette.getB(2), 255 );
        SDL_RenderDrawRect(renderer, &drawer); 
        SDL_RenderFillRect(renderer, &drawer);

        // Handle of drawer
        drawer.w = drawerDownsizeWidth / 5;
        drawer.h = drawerDownsizeHeight / 5;
        drawer.x += 45 * widthRatio;
        drawer.y += 10 * heightRatio;

        SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), 
                                palette.getB(0), 255 );
        SDL_RenderDrawRect(renderer, &drawer); 
        SDL_RenderFillRect(renderer, &drawer);
    }

    // Create one large drawer/cabinet.
    drawer.w = 150 * widthRatio;
    drawer.h = 170 * heightRatio;
    drawer.x = positionX + (150 * widthRatio);
    drawer.y = positionY + (360 * heightRatio);
    
    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), 
                            palette.getB(0), 255 );
    SDL_RenderDrawRect(renderer, &drawer); 
    SDL_RenderFillRect(renderer, &drawer);
    
    // Inside of large drawer 
    drawer.w -= drawerRimOffsetWidth;
    drawer.h -= drawerRimOffsetHeight;
    drawer.y += drawerRimOffsetHeight/2;
    drawer.x += drawerRimOffsetWidth/2;

    SDL_SetRenderDrawColor( renderer, palette.getR(2), palette.getG(2), 
                            palette.getB(2), 255 );
    SDL_RenderDrawRect(renderer, &drawer); 
    SDL_RenderFillRect(renderer, &drawer);

    // Handle of large drawer
    drawer.w = drawerDownsizeWidth / 2;
    drawer.h = drawerDownsizeHeight / 2;
    drawer.x += 20 * widthRatio;
    drawer.y += 60 * heightRatio;

    SDL_SetRenderDrawColor( renderer, palette.getR(0), palette.getG(0), 
                            palette.getB(0), 255 );
    SDL_RenderDrawRect(renderer, &drawer); 
    SDL_RenderFillRect(renderer, &drawer);
}
