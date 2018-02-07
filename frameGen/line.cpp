#include <iostream>
#include <math.h>
#include "line.h"

const float PI = 3.14159265;

Line::Line(SDL_Renderer* totalRenderer) 
    : renderer(totalRenderer)
{
}

void Line::drawCosLine(int curvesToRepeat, int lengthOfCurve, 
                       int startingX, int startingY,
                       int rotationAngle)
{ 
    for(int i = 0; i < curvesToRepeat; i++)
    {
        for(float theta = 0; theta < 2*PI; theta+=.001)
        {
            // Origin is top left, so place rotation origin point at current
            // point.
            float cosPointX = theta*lengthOfCurve; 
            float cosPointY = cos(theta)*lengthOfCurve; 
            float rotatedPointX = (cosPointX*cos(rotationAngle)) 
                                  - (cosPointY*sin(rotationAngle)) + startingX;
            float rotatedPointY = (cosPointX*sin(rotationAngle)) 
                                  + (cosPointY*cos(rotationAngle)) + startingY;

            SDL_RenderDrawPoint(renderer, rotatedPointX, rotatedPointY); 
        }
        startingX += (2*PI*lengthOfCurve) * cos(rotationAngle);
        startingY += (2*PI*lengthOfCurve) * sin(rotationAngle);
    }
}

void Line::drawSinLine(int curvesToRepeat, int lengthOfCurve, 
                       int startingX, int startingY,
                       int rotationAngle)
{
    for(int i = 0; i < curvesToRepeat; i++)
    {
        for(float theta = 0; theta < 2*PI; theta+=.001)
        {
            // Origin is top left, so place rotation origin point at current
            // point.
            float sinPointX = theta*lengthOfCurve;
            float sinPointY = sin(theta)*lengthOfCurve;

            float rotatedPointX = (sinPointX*cos(rotationAngle)) 
                                  - (sinPointY*sin(rotationAngle)) + startingX;
            float rotatedPointY = (sinPointX*sin(rotationAngle)) 
                                  + (sinPointY*cos(rotationAngle)) + startingY;
            
            SDL_RenderDrawPoint(renderer, rotatedPointX, rotatedPointY); 
        }
        startingX += (2*PI*lengthOfCurve) * cos(rotationAngle);
        startingY += (2*PI*lengthOfCurve) * sin(rotationAngle);
    }
}

void Line::drawTanLine(int curvesToRepeat, int lengthOfCurve, 
                       int startingX, int startingY,
                       int rotationAngle)
{
    for(int i = 0; i < curvesToRepeat; i++)
    {
        for(float theta = 0; theta < 2*PI; theta+=.001)
        {
            // Origin is top left, so place rotation origin point at current
            // point.
            float tanPointX = theta*lengthOfCurve; 
            float tanPointY = tan(theta)*lengthOfCurve; 

            float rotatedPointX = (tanPointX*cos(rotationAngle)) 
                                  - (tanPointY*sin(rotationAngle)) + startingX;
            float rotatedPointY = (tanPointX*sin(rotationAngle)) 
                                  + (tanPointY*cos(rotationAngle)) + startingY;

            SDL_RenderDrawPoint(renderer, rotatedPointX, rotatedPointY); 
        }
        startingX += (2*PI*lengthOfCurve) * cos(rotationAngle);
        startingY += (2*PI*lengthOfCurve) * sin(rotationAngle);
    }
}
