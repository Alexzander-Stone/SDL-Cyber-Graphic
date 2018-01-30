#include <iostream>
#include <math.h>
#include "backLayer.h"

const int WIDTH = 1280;
const int HEIGHT = 720;
const float PI = 3.14159265;

// Constructors/Destructors, use const later.
// Can use inheritance to make some of the portions of layers easier.
BackLayer::BackLayer(SDL_Renderer* totalRenderer) 
    : renderer(totalRenderer)
{
    std::cout << "Back layer created (passed renderer)" << std::endl;
}

void BackLayer::draw()
{
    std::cout << "Begin drawing back layer" << std::endl;

    // Create the rectangles postition and size.
    // Use the width and size of both the screen and the rectangle to draw to
    // the middle of the screen.
    SDL_Rect rectangle;
    rectangle.w = 200;
    rectangle.h = 250;
    rectangle.x = WIDTH/2 - (rectangle.w / 2);
    rectangle.y = HEIGHT/2 - (rectangle.h / 2);
    std::cout << "rectangle x is " << rectangle.x+rectangle.w/2 << " and y is " 
              << rectangle.y+rectangle.h/2 << std::endl;

    // Turn on alpha blending?
    //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 122 );

    // Fill the rectangle with color.
    SDL_RenderFillRect( renderer, &rectangle );

    // Set the color of the rectangle then draw the rectangle to the renderer.
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 122 ); 
    SDL_RenderDrawRect(renderer, &rectangle);

    // Create a sun on the window.
    createSun();

    // Create a console in the center of the canvas.
    int consoleWidth = 300;
    int consoleHeight = 500;
    createConsole(consoleWidth, consoleHeight, WIDTH/2 - (consoleWidth / 2), 
                  HEIGHT/2 - (consoleHeight / 2));
}


void BackLayer::createSun()
{
    // Create a circle given center coordinates (top left corner) 
    // and a color. Then draw.
    int circleRadius = 200;
    SDL_Point circleCenter = {circleRadius, circleRadius};
    SDL_Color circleColor = {255, 255, 0, 122};
    createCircle(circleCenter, circleRadius, circleColor);

    // Draw a lines around the sun.
    SDL_SetRenderDrawColor(renderer, 220, 20, 60, 255);
    SDL_RenderDrawLine(renderer, 0, circleRadius, circleRadius*2, circleRadius);

    // Curved lines.
    createCosLine(3, 10, 500, 500);
    createSinLine(2, 50, 200, 200);
    createTanLine(4, 20, 300, 300);
}

void BackLayer::createCircle(SDL_Point center, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for(int w = 0; w < radius * 2; w++)
    {
        for(int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
            }
        }
    }
}

// Distortion angle will rotate the line ( Uses radians as values currently).
void BackLayer::createCosLine(int curvesToRepeat, int lengthOfCurve, 
                                 int startingX, int startingY)
{ 
    for(int i = 0; i < curvesToRepeat; i++)
    {
        // Distortion angle is actually radians.
        float distortionAngle = PI*1.25;

        for(float theta = 0; theta < 2*PI; theta+=.001)
        {
            // Origin is top left, so place rotation origin point at current
            // point.
            float cosPointX = (theta*lengthOfCurve); //+ startingX;
            float cosPointY = ((cos(theta)*lengthOfCurve)); //+ startingY;
           
            // Debug
            //SDL_RenderDrawPoint(renderer, cosPointX + startingX, cosPointY + startingY); 
            //std::cout << "x is " << cosPointX << " y is " << cosPointY << std::endl;

            float rotatedPointX = (cosPointX*cos(distortionAngle)) 
                                  - (cosPointY*sin(distortionAngle)) + startingX;
            float rotatedPointY = (cosPointX*sin(distortionAngle)) 
                                  + (cosPointY*cos(distortionAngle)) + startingY;
            
            // debug
            //std::cout << "x is " << rotatedPointX << " y is " << rotatedPointY << std::endl;

            SDL_RenderDrawPoint(renderer, rotatedPointX, rotatedPointY); 
        }
        startingX += ((2*PI*lengthOfCurve) * cos(distortionAngle));
        startingY += ((2*PI*lengthOfCurve) * sin(distortionAngle));
    }
}

// Distortion angle will rotate the line ( Uses radians as values currently).
void BackLayer::createSinLine(int curvesToRepeat, int lengthOfCurve, 
                                 int startingX, int startingY)
{
    for(int i = 0; i < curvesToRepeat; i++)
    {
        // Distortion angle is actually radians.
        float distortionAngle = PI/2;

        for(float theta = 0; theta < 2*PI; theta+=.001)
        {
            // Origin is top left, so place rotation origin point at current
            // point.
            float sinPointX = (theta*lengthOfCurve); //+ startingX;
            float sinPointY = ((sin(theta)*lengthOfCurve)); //+ startingY;
           
            // Debug
            //SDL_RenderDrawPoint(renderer, sinPointX + startingX, sinPointY + startingY); 
            //std::cout << "x is " << sinPointX << " y is " << sinPointY << std::endl;

            float rotatedPointX = (sinPointX*cos(distortionAngle)) 
                                  - (sinPointY*sin(distortionAngle)) + startingX;
            float rotatedPointY = (sinPointX*sin(distortionAngle)) 
                                  + (sinPointY*cos(distortionAngle)) + startingY;
            
            // debug
            //std::cout << "x is " << rotatedPointX << " y is " << rotatedPointY << std::endl;

            SDL_RenderDrawPoint(renderer, rotatedPointX, rotatedPointY); 
        }
        startingX += ((2*PI*lengthOfCurve) * cos(distortionAngle));
        startingY += ((2*PI*lengthOfCurve) * sin(distortionAngle));
    }
}


// Distortion angle will rotate the line ( Uses radians as values currently).
void BackLayer::createTanLine(int curvesToRepeat, int lengthOfCurve, 
                                 int startingX, int startingY)
{
    for(int i = 0; i < curvesToRepeat; i++)
    {
        // Distortion angle is actually radians.
        float distortionAngle = PI*1.5;

        for(float theta = 0; theta < 2*PI; theta+=.001)
        {
            // Origin is top left, so place rotation origin point at current
            // point.
            float tanPointX = (theta*lengthOfCurve); //+ startingX;
            float tanPointY = ((tan(theta)*lengthOfCurve)); //+ startingY;
           
            // Debug
            //SDL_RenderDrawPoint(renderer, tanPointX + startingX, tanPointY + startingY); 
            //std::cout << "x is " << tanPointX << " y is " << tanPointY << std::endl;

            float rotatedPointX = (tanPointX*cos(distortionAngle)) 
                                  - (tanPointY*sin(distortionAngle)) + startingX;
            float rotatedPointY = (tanPointX*sin(distortionAngle)) 
                                  + (tanPointY*cos(distortionAngle)) + startingY;
            
            // debug
            //std::cout << "x is " << rotatedPointX << " y is " << rotatedPointY << std::endl;

            SDL_RenderDrawPoint(renderer, rotatedPointX, rotatedPointY); 
        }
        startingX += ((2*PI*lengthOfCurve) * cos(distortionAngle));
        startingY += ((2*PI*lengthOfCurve) * sin(distortionAngle));
    }
}

void BackLayer::createConsole(int width, int height, int positionX, int positionY)
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
    console.w = width;
    console.h = height;
    console.x = positionX;
    console.y = positionY;

    // Set the color of the console and draw to the canvas.
    SDL_SetRenderDrawColor( renderer, palette[1].r, palette[1].g, palette[1].b, 255); 
    SDL_RenderDrawRect(renderer, &console);
    SDL_RenderFillRect( renderer, &console );    
    

    /* Slanted surfaces */
    SDL_Rect slantedSurface;
    slantedSurface.w = width;
    slantedSurface.h = height;
    



    /* Terminals */
    // Default size created for console. Helps for resizing.
    SDL_Rect terminal;
    
    float terminalWidthRatio = (width / 300.0), terminalHeightRatio = (height / 500.0); 
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

// Create golden ratio function.
