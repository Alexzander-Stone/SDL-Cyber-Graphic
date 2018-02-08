#include <iostream>
#include <math.h>
#include "circleEasySolution.h"

CircleEasySolution::CircleEasySolution(const SDL_Point center, const int radiusW, const int radiusH, const SDL_Color color)
              : circleCenter(center), circleRadiusW(radiusW), 
                circleRadiusH(radiusH), circleColor(color)
{
}

void CircleEasySolution::draw(SDL_Renderer* renderer)
{
    // Draw circles
    SDL_SetRenderDrawColor(renderer, circleColor.r, circleColor.g, circleColor.b, circleColor.a);
    for(int w = 0; w < circleRadiusW * 2; w++)
    {
        for( int h = 0; h < circleRadiusH * 2; h++)
        {
            int dx = circleRadiusW - w;
            int dy = circleRadiusH - h;
            if(((dx*dx + dy*dy) <= (circleRadiusW * circleRadiusH)))
            {
                SDL_RenderDrawPoint(renderer, circleCenter.x + dx, circleCenter.y + dy);
            }
        }
    }
}
