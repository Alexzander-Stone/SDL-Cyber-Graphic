#include <iostream>
#include <math.h>
#include "circle.h"

Circle::Circle(const SDL_Point center, const int radiusW, const int radiusH, const SDL_Color color)
              : circleCenter(center), circleRadiusW(radiusW), 
                circleRadiusH(radiusH), circleColor(color)
{
}

void Circle::draw(SDL_Renderer* renderer)
{
    int squaredRadW = circleRadiusW * circleRadiusW;
    int squaredRadH = circleRadiusH * circleRadiusH;
    
    /* Begin drawing the circle using ellipsis formula.
     * Allows for circle and oval shapes.
     */
    SDL_SetRenderDrawColor( renderer, 
                            circleColor.r, circleColor.g, 
                            circleColor.b, circleColor.a );
    for(float w = 0; w < circleRadiusW * 2; w+=1)
    {
        for(float h = 0; h < circleRadiusH * 2; h+=1)
        {
            // x = a cos theta and y = b cos theta
            float dx = w - circleRadiusW;
            float dy = h - circleRadiusH;

            // If statement originally had circle formula in it, try placing
            // the ellipsis formula into it like how the circle formula was set
            // up (move radius to right side).
            //
            // (x^2) + (b^2) = 1         -> (x^2) + (b^2) = r^2
            // (x^2/a^2) + (y^2/b^2) = 1 -> (x^2*b^2) + (y^2*a^2) = a^2*b^2
            // a = radius width, b = radius height
            if(( (dx*dx*squaredRadH) + (dy*dy*squaredRadW) ) <= squaredRadW*squaredRadH)
            {
                SDL_RenderDrawPoint(renderer, circleCenter.x + dx, circleCenter.y + dy);
            }
        }
    }
}
