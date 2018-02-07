#include <iostream>
#include <math.h>
#include "line.h"

const float PI = 3.14159265;

// Constructors/Destructors, use const later.
// Can use inheritance to make some of the portions of layers easier.
Line::Line(SDL_Renderer* totalRenderer) 
    : renderer(totalRenderer)
{
}

// Distortion angle will rotate the line ( Uses radians as values currently).
void Line::drawCosLine(int curvesToRepeat, int lengthOfCurve, 
                                 int startingX, int startingY)
{ 
    for(int i = 0; i < curvesToRepeat; i++)
    {
        // Distortion angle is actually radians.
        //float distortionAngle = PI*1.25;
        float distortionAngle = PI*2;

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
void Line::drawSinLine(int curvesToRepeat, int lengthOfCurve, 
                                 int startingX, int startingY)
{
    for(int i = 0; i < curvesToRepeat; i++)
    {
        // Distortion angle is actually radians.
        float distortionAngle = PI*2;

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
void Line::drawTanLine(int curvesToRepeat, int lengthOfCurve, 
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
