#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "backLayer.h"
#include "console.h"
#include "circle.h"
#include "star.h"
#include "button.h"
//#include "colorPalette.h"

const std::string NAME = "alexzas";
const int WIDTH = 1280;
const int HEIGHT = 720;

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;
  
  // Starts the game timer.
  SDL_Init(SDL_INIT_VIDEO);
  // C style parameter passing (by value only).
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );

  // Color to clear the window/canvas with. Use to prevent trails or "acid"
  // trips.
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // Create the back layer for drawing. Then draw the back layer. 
  //BackLayer backLayer(renderer);
  //backLayer.draw();

/*
  // Create the front layer for drawing. Then draw the front layer.
  FrontLayer frontLayer(renderer);
  frontLayer.draw();
*/

  /* Create consoles */
  // give them different initial starting event points.
  int cFirstWidth = 320, cFirstHeight = 540; 
  Console firstConsole(cFirstWidth, cFirstHeight, WIDTH/2 - (cFirstHeight), 
                       HEIGHT /2 - (cFirstWidth));
  firstConsole.draw(renderer);
/*
  int cSecondWidth = 500, cSecondHeight = 300; 
  Console secondConsole(cSecondWidth, cSecondHeight, 200, 200);
  secondConsole.draw(renderer);
  
  int cThirdWidth = 200, cThirdHeight = 200; 
  Console thirdConsole(cThirdWidth, cThirdHeight, 
                       900-cThirdWidth, 500-cThirdHeight);
  thirdConsole.draw(renderer);
*/

  /* Circles */ 
  SDL_Point circleCenter = {320, 240};
  SDL_Color circleColor = {255,0,0,255};
  int circleRadiusW = 50;
  int circleRadiusH = 50;

  Circle firstCircle(circleCenter, circleRadiusW, circleRadiusH, circleColor);
  firstCircle.draw(renderer);


  /* Stars */
  SDL_Point starCenter = {700, 240};
  SDL_Color starColor = {255,0,0,255};
  int starRadiusW = 50;
  int starRadiusH = 50;

  Star firstStar(starCenter, starRadiusW, starRadiusH, starColor);
  firstStar.draw(renderer);


  // Dump everything from the renderer to the screen.
  SDL_RenderPresent(renderer);

  // Might want to place the makeFrame() function inside the event loop. Will
  // allow for multiple pictures to be taken after the first one.
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
  frameGen.makeFrame();

  // Event/game loop.
  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }

  // Free memory used by renderer and window.
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
