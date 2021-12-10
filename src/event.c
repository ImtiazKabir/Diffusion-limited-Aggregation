#include <SDL2/SDL.h>
#include <stdbool.h>

#include "sketch.h"

bool event_handler(bool * show_mover_p) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return true;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE) {
          *show_mover_p = !(*show_mover_p);
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          *show_mover_p = !(*show_mover_p);
        }
        break;
    }
  }
  return false;
}
