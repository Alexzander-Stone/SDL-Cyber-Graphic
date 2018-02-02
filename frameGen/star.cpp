#include <iostream>
#include <math.h>
#include "star.h"

Star::Star(const SDL_Point center, const int radiusW, const int radiusH, const SDL_Color color)
              : starCenter(center), starRadiusW(radiusW), 
                starRadiusH(radiusH), starColor(color)
{
}

void Star::draw(SDL_Renderer* renderer)
{
    int squaredRadW = starRadiusW * starRadiusW;
    int squaredRadH = starRadiusH * starRadiusH;
    
    SDL_SetRenderDrawColor(renderer, starColor.r, starColor.g, starColor.b, starColor.a);
    for(int w = 0; w < starRadiusW * 2; w++)
    {
        for(int h = 0; h < starRadiusH * 2; h++)
        {
            // x = a cos theta and y = b cos theta
            float dx = w - starRadiusW;
            float dy = h - starRadiusH;

            // If statement originally had circle formula in it, try placing
            // the ellipsis formula into it like how the circle formula was set
            // up (move radius to right side).
            //
            // (x^2) + (b^2) = r^2
            // (x^2/a^2) + (y^2/b^2) = 1 -> (x^2*b^2) + (y^2*a^2) = a^2*b^2
            // a = radius width, b = radius height
            

            /* Messed up the formula, but made really cool star object. */
            if((dx*dx*starRadiusH* + dy*dy*starRadiusW ) <= squaredRadW*squaredRadH)
            {
                SDL_RenderDrawPoint(renderer, starCenter.x + dx, starCenter.y + dy);
            }
        }
    }
}
