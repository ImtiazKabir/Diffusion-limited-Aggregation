#include <SDL2/SDL.h>
#include "MEOW.h"

int main(void) {
  SDL_Window * window;
  SDL_Renderer * renderer;
  int const WIDTH = 300;
  int const HEIGHT = 300;
  char const TITLE[] = "Diffusion Limited Aggregation";

  MEOW_Init(&window, &renderer, WIDTH, HEIGHT, TITLE);

  int const FPS = 60;
  int const NUM_OF_PARTICLES = 5000;
  MEOW_Repeat(renderer, WIDTH, HEIGHT, FPS, NUM_OF_PARTICLES);

  MEOW_Destroy(window, renderer);
  return 0;
}
