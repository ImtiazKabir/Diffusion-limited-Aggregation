#include <SDL2/SDL.h>
#include <stdbool.h>

#include "sketch.h"

bool event_handler(bool * show_mover_p) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return true;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_SPACE) {
        *show_mover_p = !(*show_mover_p);
      }
    }
  }
  return false;
}
