#ifndef DIFFUSION_PARTICLE_H
#define DIFFUSION_PARTICLE_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "vector.h"

typedef struct {
  Vector * loc;
  Vector * vel;
  double r;
  bool can_move;
  double speed;
} Particle;

Particle * Particle_Create(double x, double y);
void Particle_Destroy(Particle * self);
void Particle_Update(
  Particle * const self,
  int const WIDTH,
  int const HEIGHT
);

void Particle_Render(
  Particle * const self,
  SDL_Renderer * renderer,
  SDL_Texture * texture
);

#endif    /* DIFFUSION_PARTICLE_H */
