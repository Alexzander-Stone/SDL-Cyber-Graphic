#include <iostream>
#include "circle.h"
#include "button.h"

Button::Button(const int eRadiusW, const int eRadiusH, 
               const SDL_Point center, const SDL_Rect sqrRect,
               const ColorPalette pal)
              : ellipseRadiusW(eRadiusW), ellipseRadiusH(eRadiusH), 
              ellipseCenter(center), squareButton(sqrRect), 
              palette(pal)   
{
}

void Button::draw(SDL_Renderer* renderer)
{
    //SDL_Color ellipseColor = {palette[0].r, palette[0].g, palette[0].b, 255};
    SDL_Color ellipseColor = {55, 55, 55, 255};
    Circle bottomButtonEllipse(ellipseCenter, ellipseRadiusW, ellipseRadiusH, ellipseColor);

    // Top of the buttons.
    //ellipseColor = {palette[1].r, palette[1].g, palette[1].b, 255};
    ellipseColor = {55, 55, 55, 255};
    Circle topButtonEllipse(ellipseCenter, ellipseRadiusW, ellipseRadiusH, ellipseColor);

    // Add depth to the bottom of the buttons.
    //SDL_SetRenderDrawColor( renderer, palette[0].r, palette[0].g, palette[0].b, 255);
    SDL_SetRenderDrawColor( renderer, 20, 20, 20, 255);
    squareButton.x = ellipseCenter.x - squareButton.w/2;
    squareButton.y = ellipseCenter.y - squareButton.h/4;   

    //Render the bottom to the top.
    SDL_RenderDrawRect(renderer, &squareButton);
    SDL_RenderFillRect(renderer, &squareButton);
    bottomButtonEllipse.draw(renderer);
    topButtonEllipse.draw(renderer);
}
