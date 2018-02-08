#include <iostream>
#include <ctime>
#include <cstdlib>
#include "circle.h"
#include "button.h"

// static var
int Button::buttonCounter = 0;

int Button::getCounter() const
{
    return buttonCounter;
}

// Overloaded operator, helped with the static var.
std::ostream& operator <<(std::ostream& out, const Button &b)
{
    out << "The current button is button #" << b.getCounter();
    return out;
}


Button::Button(const int eRadiusW, const int eRadiusH,  
               const SDL_Point center, SDL_Rect sqrRect,
               const ColorPalette pal)
              : ellipseRadiusW(eRadiusW), ellipseRadiusH(eRadiusH), 
              ellipseCenter(center), squareButton(sqrRect), 
              palette(pal) 
{
    srand(time(0) + buttonCounter++);
}

void Button::draw(SDL_Renderer* renderer)
{
    /* Bottom ellipse */
    // Off set the bottom of the button in the y coordinates (gives depth
    // appearance).
    SDL_Color ellipseColor = { palette.getR(3), palette.getG(3), 
                               palette.getB(3), 255 };
    ellipseCenter.y += ellipseRadiusH/2;
    Circle bottomButtonEllipse( ellipseCenter, ellipseRadiusW, ellipseRadiusH, 
                                ellipseColor, 1);
    ellipseCenter.y -= ellipseRadiusH/2;

    /* Square to link together top and bottom ellipse. */
    SDL_SetRenderDrawColor( renderer, palette.getR(3), palette.getG(3), 
                            palette.getB(3), 255 );
    squareButton.x = ellipseCenter.x - squareButton.w/2;
    squareButton.y = ellipseCenter.y - squareButton.h/2;   

    /* Top ellipse */
    ellipseCenter.y -= ellipseRadiusH/2;
    ellipseColor = { rand()%2?palette.getR(4):palette.getR(6), rand()%2?palette.getG(4):palette.getG(6), 
                     rand()%2?palette.getB(4):palette.getB(6), 255 };
    Circle topButtonEllipse( ellipseCenter, ellipseRadiusW, ellipseRadiusH, 
                             ellipseColor, 1);

    //Render from the bottom to the top.
    SDL_RenderDrawRect(renderer, &squareButton);
    SDL_RenderFillRect(renderer, &squareButton);
    bottomButtonEllipse.draw(renderer);
    topButtonEllipse.draw(renderer);
}



