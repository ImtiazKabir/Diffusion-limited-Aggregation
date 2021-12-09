#ifndef LIB_MEOW_SKETCH_H
#define LIB_MEOW_SKETCH_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#include "particle.h"

static inline void MEOW_Error(char const * const func_name) {
  fprintf(stderr, "~~IM~~ %s did not work\n"
                  "----------------------\n"
                  "%s", func_name, SDL_GetError());
  SDL_ClearError();
}
char * MEOW_GetPath(char const * const child);  /* lib/getpath.c */


/* event.c */
bool event_handler(bool * const show_mover_p);

/* once.c */
void setup(
  SDL_Renderer * renderer,
  SDL_Texture ** const move_texture_p,
  SDL_Texture ** const stuck_texture_p,
  Particle *** const particles_p,
  int const NUM_OF_PARTICLES,
  int const WIDTH,
  int const HEIGHT,
  int ** stuck_indices_p
);
void clean_up(
  SDL_Texture * move_texture,
  SDL_Texture * stuck_texture,
  Particle ** particles,
  int const NUM_OF_PARTICLES,
  int * stuck_indices
);

/* loop.c */
void update(
  Particle ** particles,
  int const NUM_OF_PARTICLES,
  int const WIDTH,
  int const HEIGHT,
  int ** stuck_indices_p
);
void draw(
  SDL_Renderer * renderer,
  Particle ** particles,
  int const NUM_OF_PARTICLES,
  SDL_Texture * move_texture,
  SDL_Texture * stuck_texture,
  bool const show_mover
);

#endif /* LIB_MEOW_SKETCH_H */
