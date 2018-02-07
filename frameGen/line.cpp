#include <iostream>
#include <math.h>
#include "line.h"

const float PI = 3.14159265;

Line::Line(SDL_Renderer* totalRenderer) 
    : renderer(totalRenderer)
{
}

// rotation angle will rotate the line ( Uses radians as values currently).
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
            float cosPointX = (theta*lengthOfCurve); 
            float cosPointY = ((cos(theta)*lengthOfCurve)); 
            float rotatedPointX = (cosPointX*cos(rotationAngle)) 
                                  - (cosPointY*sin(rotationAngle)) + startingX;
            float rotatedPointY = (cosPointX*sin(rotationAngle)) 
                                  + (cosPointY*cos(rotationAngle)) + startingY;

            SDL_RenderDrawPoint(renderer, rotatedPointX, rotatedPointY); 
        }
        startingX += ((2*PI*lengthOfCurve) * cos(rotationAngle));
        startingY += ((2*PI*lengthOfCurve) * sin(rotationAngle));
    }
}

// rotation angle will rotate the line ( Uses radians as values currently).
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
            float sinPointX = (theta*lengthOfCurve); //+ startingX;
            float sinPointY = ((sin(theta)*lengthOfCurve)); //+ startingY;

            float rotatedPointX = (sinPointX*cos(rotationAngle)) 
                                  - (sinPointY*sin(rotationAngle)) + startingX;
            float rotatedPointY = (sinPointX*sin(rotationAngle)) 
                                  + (sinPointY*cos(rotationAngle)) + startingY;
            
            SDL_RenderDrawPoint(renderer, rotatedPointX, rotatedPointY); 
        }
        startingX += ((2*PI*lengthOfCurve) * cos(rotationAngle));
        startingY += ((2*PI*lengthOfCurve) * sin(rotationAngle));
    }
}


// rotation angle will rotate the line ( Uses radians as values currently).
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
            float tanPointX = (theta*lengthOfCurve); //+ startingX;
            float tanPointY = ((tan(theta)*lengthOfCurve)); //+ startingY;

            float rotatedPointX = (tanPointX*cos(rotationAngle)) 
                                  - (tanPointY*sin(rotationAngle)) + startingX;
            float rotatedPointY = (tanPointX*sin(rotationAngle)) 
                                  + (tanPointY*cos(rotationAngle)) + startingY;

            SDL_RenderDrawPoint(renderer, rotatedPointX, rotatedPointY); 
        }
        startingX += ((2*PI*lengthOfCurve) * cos(rotationAngle));
        startingY += ((2*PI*lengthOfCurve) * sin(rotationAngle));
    }
}
