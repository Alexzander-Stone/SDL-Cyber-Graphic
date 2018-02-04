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
    SDL_Color ellipseColor = {palette.getR(3), palette.getG(3), palette.getB(3), 255};
    ellipseCenter.y += ellipseRadiusH/2;
    Circle bottomButtonEllipse(ellipseCenter, ellipseRadiusW, ellipseRadiusH, ellipseColor);
    ellipseCenter.y -= ellipseRadiusH/2;

    // Top of the buttons.
    ellipseColor = {palette.getR(4), palette.getG(4), palette.getB(4), 255};
    
    // Add depth to the bottom of the buttons.
    SDL_SetRenderDrawColor( renderer, palette.getR(3), palette.getG(3), palette.getB(3), 255);
    squareButton.x = ellipseCenter.x - squareButton.w/2;
    squareButton.y = ellipseCenter.y - squareButton.h/2;   

    // Off set the top of the button in the y coordinates (gives depth
    // appearance).
    ellipseCenter.y -= ellipseRadiusH/2;
    Circle topButtonEllipse(ellipseCenter, ellipseRadiusW, ellipseRadiusH, ellipseColor);

    //Render the bottom to the top.
    SDL_RenderDrawRect(renderer, &squareButton);
    SDL_RenderFillRect(renderer, &squareButton);
    bottomButtonEllipse.draw(renderer);
    topButtonEllipse.draw(renderer);
}
