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
    // Draw lightings of varying opacity, (start with largest lighting w/ least
    // opacity and continue making smaller lightings with higher opacities).
    for(int lightingLoop = 4; lightingLoop > 0; lightingLoop--)
    {
        float opacityRadiusW = lightingRadiusW * lightingLoop/2;
        float opacityRadiusH = lightingRadiusH * lightingLoop/2;

        SDL_SetRenderDrawColor(renderer, lightingColor.r + (20 * lightingLoop), 
                lightingColor.g + (20 * lightingLoop), lightingColor.b + (20 * lightingLoop), lightingColor.a);
       
        SDL_Color portionColor = {(Uint8)(lightingColor.r + (20 * lightingLoop)), (Uint8)(lightingColor.g + (20 * lightingLoop)), 
                                  (Uint8)(lightingColor.b + (20 * lightingLoop)), (Uint8)(lightingColor.a + (20 * lightingLoop))};

        // Use circle to make the lighting.
        Circle lightingPortion(lightingCenter, opacityRadiusW, opacityRadiusH, portionColor);
        lightingPortion.draw(renderer);


    }
}
