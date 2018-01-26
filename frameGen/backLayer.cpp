#include <iostream>
#include "backLayer.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

// Constructors
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

}
