#include <iostream>
#include <math.h>
#include "lighting.h"
#include "circle.h"

Lighting::Lighting(const SDL_Point center, const int radiusW, const int radiusH, const SDL_Color color, const int circles)
              : lightingCenter(center), lightingRadiusW(radiusW), 
                lightingRadiusH(radiusH), lightingColor(color),
                totalCircles(circles)
{
}

void Lighting::draw(SDL_Renderer* renderer)
{
    // Change to additive mode.
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    
    // Draw lightings of varying opacity, (start with largest lighting w/ least
    // opacity and continue making smaller lightings with higher opacities).
    for(int lightingLoop = 0; lightingLoop <= totalCircles; lightingLoop++)
    {
        float opacityRadiusW = lightingRadiusW - 
                               ((lightingLoop-totalCircles)*(lightingRadiusW/8)) 
                               * -1;
        float opacityRadiusH = lightingRadiusH -
                               ((lightingLoop-totalCircles)*(lightingRadiusW/8)) 
                               * -1;

        SDL_Color portionColor = { (Uint8)(lightingColor.r ), 
                                   (Uint8)(lightingColor.g ), 
                                   (Uint8)(lightingColor.b ), 
                                   (Uint8)(lightingColor.a - lightingLoop) };

        SDL_Color resetCanvas = { (Uint8)(60 + (10 * lightingLoop)), (Uint8)(40 + (10 * lightingLoop)), 
                                  (Uint8)(0 + (10 * lightingLoop)), 2};

        // Change tint of lightingColor
        lightingColor.r *= .8;
        lightingColor.g *= .8;
        lightingColor.b *= .8;

        // Use circle to make the lighting.
        // Clear the canvas beneath the light.

        Circle lightingClear(lightingCenter, opacityRadiusW, opacityRadiusH, resetCanvas, 2);
        lightingClear.draw(renderer);

        Circle lightingPortion(lightingCenter, opacityRadiusW, opacityRadiusH, portionColor, 2);
        lightingPortion.draw(renderer);
    }

    // Set blend mode back to blend.
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}
