#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "line.h"
#include "console.h"
#include "circle.h"
#include "star.h"
#include "button.h"
#include "lighting.h"
#include "brick.h"
#include "trim.h"
#include "window.h"

// Function declarations
void fillBrickBackground(SDL_Renderer* renderer,
                         const int brickWidth, const int brickHeight, 
                         const int totalBrickW, const int totalBrickH);

const std::string NAME = "alexzas";
const int WIDTH = 720;
const int HEIGHT = 1280;
const int FLOOR_HEIGHT = 20;

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;
  
  // Starts the game timer.
  SDL_Init(SDL_INIT_VIDEO);
  // C style parameter passing (by value only).
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );
  // Turn blending/alpha modes on.
  //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


  // Color to clear the window/canvas with. Use to prevent trails or "acid"
  // trips.
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  /* Create bricks for background */
  int brickWidth = 200, brickHeight = 200;
  int totalBrickW = WIDTH / brickWidth + 1, 
      totalBrickH = HEIGHT / brickHeight + 1; // Set size to fit on screen.
  fillBrickBackground(renderer, brickWidth, brickHeight, totalBrickW, totalBrickH); 

  /* Create trimming on background */
  Trim trimBackground(0, HEIGHT - FLOOR_HEIGHT, WIDTH, FLOOR_HEIGHT);
  trimBackground.draw(renderer);

  /* Create window in background */
  Window windowBackground(WIDTH / 2, 0, 500, 300);
  windowBackground.draw(renderer);

  /* Create consoles */
  // Give them different initial starting event points.
  int cFirstWidth = 480, cFirstHeight = 810; 
  Console firstConsole(cFirstWidth, cFirstHeight, 10, 
                       HEIGHT - (cFirstHeight)-8);
  firstConsole.draw(renderer);
 
  /* Lighting */ 
  SDL_Point lightingCenter = {900, 500};
  SDL_Color lightingColor = {216, 144, 49, 5};
  int lightingRadiusW = 10;
  int lightingRadiusH = 10;

  Lighting firstLighting(lightingCenter, lightingRadiusW, lightingRadiusH, 
                         lightingColor);
  firstLighting.draw(renderer);

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

void fillBrickBackground(SDL_Renderer* renderer,
                         const int brickWidth, const int brickHeight, 
                         const int totalBrickW, const int totalBrickH)
{
  for(int currentX = 0; currentX < totalBrickW; currentX++)
  {
      for(int currentY = 0; currentY < totalBrickH; currentY++)
      {
          Brick brickBackground((currentX*brickWidth), (currentY*brickHeight), 
                                brickWidth, brickHeight);
          brickBackground.draw(renderer);
      }
  }
}
