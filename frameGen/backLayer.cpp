#include <iostream>
#include <math.h>
#include "backLayer.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

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
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255/4 );

    // Fill the rectangle with color.
    SDL_RenderFillRect( renderer, &rectangle );

    // Set the color of the rectangle then draw the rectangle to the renderer.
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255/4 ); 
    SDL_RenderDrawRect(renderer, &rectangle);

    // Create a sun on the window.
    createSun();
}


void BackLayer::createSun()
{
    // Create a circle given center coordinates (top left corner) 
    // and a color. Then draw.
    int circleRadius = 200;
    SDL_Point circleCenter = {circleRadius, circleRadius};
    SDL_Color circleColor = {255, 255, 0, 255/2};
    createCircle(circleCenter, circleRadius, circleColor);

    // Draw a lines around the sun.
    SDL_SetRenderDrawColor(renderer, 220, 20, 60, 255);
    SDL_RenderDrawLine(renderer, 0, circleRadius, circleRadius*2, circleRadius);

    // Curved lines.
    createCurvedLine(2, 50);
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

// Possible offset of curve later.
// tan, sin, cos possible
void BackLayer::createCurvedLine(int curvesToRepeat, int lengthOfCurve)
{
    int startingX = 50, startingY = 500;
    
    for(int i = 0; i < curvesToRepeat; i++)
    {
        for(float theta = 0; theta < 2*3.14159265; theta+=.001)
        {
            SDL_RenderDrawPoint(renderer, startingX + theta*lengthOfCurve, 
                   startingY + (cos(theta)*lengthOfCurve)); 
        }
        startingX += 2*3.14159265*lengthOfCurve;
    }
}
