#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sketch.h"
#include "particle.h"
#include "stb/stb_ds.h"

void createTexture(
  SDL_Renderer *renderer,
  SDL_Texture ** const texture,
  char const * const dir
);

void setup(
  SDL_Renderer * renderer,
  SDL_Texture ** const move_texture_p,
  SDL_Texture ** const stuck_texture_p,
  Particle *** const particles_p,
  int const NUM_OF_PARTICLES,
  int const WIDTH,
  int const HEIGHT,
  int ** stuck_indices_p
) {

  createTexture(renderer, move_texture_p, "assets/green.png");
  createTexture(renderer, stuck_texture_p, "assets/orange.png");

  /* Inititate the particles array */
  srand((unsigned) time(NULL));

  (*particles_p) = (Particle **) calloc(
    (unsigned long) NUM_OF_PARTICLES,
    sizeof(Particle *)
  );

  (*particles_p)[0] = Particle_Create(WIDTH/2.0, HEIGHT/2.0);
  (*particles_p)[0]->can_move = false;
  arrput(*stuck_indices_p, 0);

  for (int i = 1; i < NUM_OF_PARTICLES; ++i) {
    int const side = rand() % 4;
    double const pos = rand() / (double) RAND_MAX;
    switch(side) {
      case 0:
        (*particles_p)[i] = Particle_Create(pos * WIDTH, 0);
        break;
      case 1:
        (*particles_p)[i] = Particle_Create(WIDTH, pos * HEIGHT);
        break;
      case 2:
        (*particles_p)[i] = Particle_Create(pos * WIDTH, HEIGHT);
        break;
      case 3:
        (*particles_p)[i] = Particle_Create(0, pos * HEIGHT);
        break;
    }
  }
}

void clean_up(
  SDL_Texture * move_texture,
  SDL_Texture * stuck_texture,
  Particle ** particles,
  int const NUM_OF_PARTICLES,
  int * stuck_indices
) {
  SDL_DestroyTexture(move_texture);
  SDL_DestroyTexture(stuck_texture);

  for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
    Particle_Destroy(particles[i]);
  }
  free(particles);

  arrfree(stuck_indices);
}

void createTexture(
  SDL_Renderer *renderer,
  SDL_Texture ** const texture,
  char const * const dir
) {

  char * path = MEOW_GetPath(dir);
  SDL_Surface * surface = IMG_Load(path);
  if (surface == NULL) {
    MEOW_Error("Creating surface for life with IMG_Load");
  }
  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  free(path);
  SDL_FreeSurface(surface);
}
