#include <iostream>
#include "button.h"
#include "circle.h"

Button::Button(const SDL_Point center, const int radiusW, const int radiusH, const SDL_Color color)
              : ellipseRadiusW(radiusW), ellipseRadiusH(radiusH), ellipseCenter(center), palette(palette) 
{
}

void Button::draw(SDL_Renderer* renderer)
{
    SDL_Color ellipseColor = {palette[0].r, palette[0].g, palette[0].b, 255};
    Circle bottomButtonEllipse(ellipseCenter, ellipseRadiusW, ellipseRadiusH, ellipseColor);

    // Top of the buttons.
    ellipseCenter = {positionX + (col * ellipseRadiusW*2) + ellipseRadiusW 
                    + (col *buttonSpacing), 
                    positionY + (int)(300 * heightRatio) + ellipseRadiusH 
                    + (rows * ellipseRadiusH*2) + (rows * buttonSpacing)
                    - (ellipseRadiusH/4) - (int)(5 * heightRatio)};
    ellipseColor = {palette[1].r, palette[1].g, palette[1].b, 255};
    Circle topButtonEllipse(ellipseCenter, ellipseRadiusW, ellipseRadiusH, ellipseColor);

    // Add depth to the bottom of the buttons.
    SDL_SetRenderDrawColor( renderer, palette[0].r, palette[0].g, palette[0].b, 255);
    squareButton.x = ellipseCenter.x - squareButton.w/2;
    squareButton.y = ellipseCenter.y - squareButton.h/4;   

    //Render the bottom to the top.
    SDL_RenderDrawRect(renderer, &squareButton);
    SDL_RenderFillRect(renderer, &squareButton);
    bottomButtonEllipse.draw(renderer);
    topButtonEllipse.draw(renderer);
}
