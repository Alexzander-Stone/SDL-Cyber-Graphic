#include <iostream>
#include <math.h>
#include "circle.h"

Circle::Circle(const SDL_Point center, const int radius, const SDL_Color color)
              : circleCenter(center), circleRadius(radius), circleColor(color)
{
}

void Circle::draw(SDL_Renderer* renderer)
{
    // Draw circles
    SDL_SetRenderDrawColor(renderer, circleColor.r, circleColor.g, circleColor.b, circleColor.a);
    for(int w = 0; w < circleRadius * 2; w++)
    {
        for(int h = 0; h < circleRadius * 2; h++)
        {
            int dx = circleRadius - w;
            int dy = circleRadius - h;
            if((dx*dx + dy*dy) <= (circleRadius * circleRadius))
            {
                SDL_RenderDrawPoint(renderer, circleCenter.x + dx, circleCenter.y + dy);
            }
        }
    }
}
