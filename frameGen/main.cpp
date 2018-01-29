#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "backLayer.h"
#include "frontLayer.h"

const std::string NAME = "alexzas";
const int WIDTH = 1280;
const int HEIGHT = 720;

void drawCircle(SDL_Renderer* renderer,
  SDL_Point center, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

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
  BackLayer backLayer(renderer);
  backLayer.draw();

/*
  // Create the front layer for drawing. Then draw the front layer.
  FrontLayer frontLayer(renderer);
  frontLayer.draw();
*/

  // Draw the circle on the window/canvas.
  SDL_Point circleCenter = {320, 240};
  SDL_Color circleColor = {255,0,0,255};
  drawCircle(renderer, circleCenter, 50, circleColor);

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
