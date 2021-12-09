#include "particle.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "sketch.h"

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

Particle * Particle_Create(double x, double y) {
  Particle * p = (Particle *) malloc(sizeof(*p));

  p->loc = Vector_CreateXY(x, y);
  p->vel = Vector_Create();
  p->r = 2.0;
  p->speed = 3.0;
  p->can_move = true;

  return p;
}

void Particle_Destroy(Particle * self) {
  Vector_Destroy(self->loc);
  Vector_Destroy(self->vel);
  free(self);
}

void Particle_Update(
  Particle * const self,
  int const WIDTH,
  int const HEIGHT
) {
  double const theta = (2 *  M_PI *  rand()) / RAND_MAX;
  self->vel->x = self->speed * cos(theta);
  self->vel->y = self->speed * sin(theta);
  Vector_Add(self->loc, self->loc, self->vel);

  if (self->loc->x < 0) {
    self->loc->x = 0;
  } else if (self->loc->x > WIDTH) {
    self->loc->x = WIDTH;
  }

  if (self->loc->y < 0) {
    self->loc->y = 0;
  } else if (self->loc->y > HEIGHT) {
    self->loc->y = HEIGHT;
  }
}

void Particle_Render(
  Particle * const self,
  SDL_Renderer * renderer,
  SDL_Texture * texture
) {
  SDL_Rect dstrect = {
    .x = (int) (self->loc->x - self->r),
    .y = (int) (self->loc->y - self->r),
    .w = (int) (2 * self->r),
    .h = (int) (2 * self->r)
  };

  if (SDL_RenderCopy(renderer, texture, NULL, &dstrect)) {
    MEOW_Error("Rendering particle with SDL_RenderCopy");
  }
}
