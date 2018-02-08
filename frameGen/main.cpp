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

void drawOutlet(SDL_Renderer* renderer, 
                const int outletX, const int outletY, 
                const int outletWidth, const int outletHeight);

void drawLamp( SDL_Renderer* renderer,
               const int positionX, const int positionY, 
               const int width, const int height,
               const SDL_Color lightingColor );

void animateScene(SDL_Renderer* renderer,
                  const int brickWidth, const int brickHeight,
                  const int totalBrickW, const int totalBrickH,
                  const int outletX, const int outletY,
                  const int outletWidth, const int outletHeight,
                  const int lightingRadiusW, const int lightingRadiusH,
                  const SDL_Color lightingColor, Trim trimBackground,
                  Window windowBackground, Console firstConsole);

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
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


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

  /* Create console. */
  int cFirstWidth = 480, cFirstHeight = 810; 
  Console firstConsole(cFirstWidth, cFirstHeight, 10, 
                       HEIGHT - (cFirstHeight)-8);
  firstConsole.draw(renderer);

  /* Create outlet */
  int outletX = 575, outletY = 1100;
  int outletWidth = 60, outletHeight = 85; 
  drawOutlet( renderer, 
              outletX, outletY,
              outletWidth, outletHeight );

  /* Lighting */ 
  SDL_Color lightingColor = {250, 250, 49, 5};
  int lightingRadiusW = 300;
  int lightingRadiusH = 300;
  
  drawLamp(renderer, 200, 200, lightingRadiusW, 
           lightingRadiusH, lightingColor);

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
    animateScene(renderer,
                  brickWidth, brickHeight,
                  totalBrickW, totalBrickH,
                  outletX, outletY,
                  outletWidth, outletHeight,
                  lightingRadiusW, lightingRadiusH,
                  lightingColor, trimBackground,
                  windowBackground, firstConsole);
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

void drawOutlet(SDL_Renderer* renderer, 
                const int outletX, const int outletY, 
                const int outletWidth, const int outletHeight)
{
  
  /* Base of outlet */
  // Draw multiple rectangles to show depth.
  SDL_Rect outlet;
  outlet.w = outletWidth;
  outlet.h = outletHeight;
  outlet.x = outletX;
  outlet.y = outletY;

  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderDrawRect(renderer, &outlet);
  SDL_RenderFillRect(renderer, &outlet);

  /* Panel of outlet */
  // Use multiple rect's to give depth.
  int offSet = 20;

  for( int currentDepth = 3; currentDepth > 0; currentDepth--)
  {
    outlet.w = outletWidth - offSet + (10 * currentDepth);
    outlet.h = outletHeight - offSet + (10 * currentDepth);
    outlet.x = outletX + offSet/2 - (5 * currentDepth);
    outlet.y = outletY + offSet/2 - (5 * currentDepth);

    SDL_SetRenderDrawColor( renderer, 40 + (20 * currentDepth), 
                            40 + (20 * currentDepth), 40 + (20 * currentDepth), 
                            255 );
    SDL_RenderDrawRect(renderer, &outlet);
    SDL_RenderFillRect(renderer, &outlet);
  }

  /* Lines Connecting Corners */
  SDL_SetRenderDrawColor( renderer, 160, 160, 160, 255 );

  SDL_RenderDrawLine( renderer, outlet.x, outlet.y,
                      outletX, outletY);
  SDL_RenderDrawLine( renderer, outlet.x + outlet.w, outlet.y,
                      outletX + outletWidth, outletY);
  SDL_RenderDrawLine( renderer, outlet.x, outlet.y + outlet.h,
                      outletX, outletY + outletHeight);
  SDL_RenderDrawLine( renderer, outlet.x + outlet.w, outlet.y + outlet.h,
                      outletX + outletWidth, outletY + outletHeight);

  /* Line crossing gap. */ 
  outlet.x = outletX;
  outlet.y = outletY + outletHeight / 2;
  outlet.w = outletWidth;
  outlet.h = 1;

  SDL_SetRenderDrawColor( renderer, 100, 100, 100, 255 );
  SDL_RenderDrawRect(renderer, &outlet);
  SDL_RenderFillRect(renderer, &outlet);
  


  /* Plug holes */
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);

  for( int currentPlug = 0; currentPlug < 2; currentPlug++)
  {
    // Left hole.
    outlet.w = (outletWidth - offSet) / 10;
    outlet.h = (outletHeight - offSet) / 6;
    outlet.x = outletX + outletWidth/3 - 2;
    outlet.y = outletY + outletHeight/8 + ((outletHeight/3 + 12) * currentPlug) + 4;
    
    SDL_RenderDrawRect(renderer, &outlet);
    SDL_RenderFillRect(renderer, &outlet);

    // Right hole.
    outlet.x = outlet.x + (outlet.x - outletX);

    SDL_RenderDrawRect(renderer, &outlet);
    SDL_RenderFillRect(renderer, &outlet);

    // Bottom hole.
    outlet.x = outletX + outletWidth/3 + 2 ;
    outlet.y += 15;
    
    int tempSwap = outlet.w;
    outlet.w = outlet.h + 5;
    outlet.h = tempSwap;

    SDL_RenderDrawRect(renderer, &outlet);
    SDL_RenderFillRect(renderer, &outlet);
  }
}

void drawLamp( SDL_Renderer* renderer,
               const int positionX, const int positionY, 
               const int width, const int height,
               const SDL_Color lightingColor )
{
  

  /* Cord 
  SDL_Rect cord;
  
  cord.x = positionX - width/4;
  cord.y = 0;
  cord.w = width/2;
  cord.h = positionX;

  SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, &cord);
  SDL_RenderDrawRect(renderer, &cord);
  */

  /* console test */
  Console rope(15, height, positionX-7, 0);
  rope.draw(renderer);


  /* Lighting */ 
  SDL_Point lightingCenter = {positionX, positionY};

  Lighting firstLighting(lightingCenter, width, height, lightingColor);
  firstLighting.draw(renderer);

}

void animateScene(SDL_Renderer* renderer,
                  const int brickWidth, const int brickHeight,
                  const int totalBrickW, const int totalBrickH,
                  const int outletX, const int outletY,
                  const int outletWidth, const int outletHeight,
                  const int lightingRadiusW, const int lightingRadiusH,
                  const SDL_Color lightingColor, Trim trimBackground,
                  Window windowBackground, Console firstConsole)
{

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

    fillBrickBackground(renderer, 
                    brickWidth, brickHeight, 
                    totalBrickW, totalBrickH);

    trimBackground.draw(renderer);

    windowBackground.draw(renderer);

    firstConsole.draw(renderer);

    drawOutlet( renderer,
                outletX, outletY,
                outletWidth, outletHeight );

    drawLamp(renderer, 200, 200, 
             lightingRadiusW, lightingRadiusH, 
             lightingColor);

    SDL_RenderPresent(renderer);
}
