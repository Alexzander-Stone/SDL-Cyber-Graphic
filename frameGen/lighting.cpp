#include <iostream>
#include <math.h>
#include "lighting.h"
#include "circle.h"

Lighting::Lighting(const SDL_Point center, const int radiusW, const int radiusH, const SDL_Color color)
              : lightingCenter(center), lightingRadiusW(radiusW), 
                lightingRadiusH(radiusH), lightingColor(color)
{
}

void Lighting::draw(SDL_Renderer* renderer)
{
    int totalCircles = 6;
    
    // Draw lightings of varying opacity, (start with largest lighting w/ least
    // opacity and continue making smaller lightings with higher opacities).
    for(int lightingLoop = totalCircles; lightingLoop > 0; lightingLoop--)
    {
        float opacityRadiusW = lightingRadiusW + 
                               ((lightingLoop-totalCircles)*(lightingRadiusW/4)) * -1;
        float opacityRadiusH = lightingRadiusH + 
                               ((lightingLoop-totalCircles)*(lightingRadiusW/4)) * -1;

        SDL_Color portionColor = { (Uint8)(lightingColor.r ), 
                                   (Uint8)(lightingColor.g ), 
                                   (Uint8)(lightingColor.b ), 
                                   (Uint8)(lightingColor.a + lightingLoop) };

        // Change tint of lightingColor
        lightingColor.r *= .75;
        lightingColor.g *= .75;
        lightingColor.b *= .75;

        // Use circle to make the lighting.
        Circle lightingPortion(lightingCenter, opacityRadiusW, opacityRadiusH, portionColor);
        lightingPortion.draw(renderer);
    }
}
