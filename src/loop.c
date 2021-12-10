#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "sketch.h"
#include "particle.h"
#include "stb/stb_ds.h"

void draw(
  SDL_Renderer * renderer,
  Particle ** particles,
  int const NUM_OF_PARTICLES,
  SDL_Texture * move_texture,
  SDL_Texture * stuck_texture,
  bool const show_mover
) {
  if (SDL_SetRenderDrawColor(renderer, 6, 70, 53, 255) == -1) {
    MEOW_Error("Setting the background color with SDL_SetRenderDrawColor");
  }
  if (SDL_RenderClear(renderer) == -1) {
    MEOW_Error("Clearing the window for background with SDL_RenderClear");
  }

  for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
    if (particles[i]->can_move == true) {
      if (show_mover == true) {
        Particle_Render(particles[i], renderer, move_texture);
      }
    } else {
      Particle_Render(particles[i], renderer, stuck_texture);
    }
  }
}


void update(
  Particle ** particles,
  int const NUM_OF_PARTICLES,
  int const WIDTH,
  int const HEIGHT,
  int ** stuck_indices_p
) {
  for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
    if (particles[i]->can_move == true) {
      Particle_Update(particles[i], WIDTH, HEIGHT);
    }
  }

  /* now update stats */
  int * proxy_stuck = NULL;
  for (int i = 0; i < NUM_OF_PARTICLES; ++i) {
    if (particles[i]->can_move == false) {
      continue;
    }
    for (int j = 0; j < arrlen(*stuck_indices_p); ++j) {
      int const k = (*stuck_indices_p)[j];
      double const r1 = particles[i]->r;
      double const r2 = particles[k]->r;
      double const d = r1 + r2;
      if (Vector_SqDist(particles[i]->loc, particles[k]->loc) <= d*d) {
        particles[i]->can_move = false;
        arrput(proxy_stuck, i);
        break;
      }
    }
  }
  for (int i = 0; i < arrlen(proxy_stuck); ++i) {
    arrput(*stuck_indices_p, proxy_stuck[i]);
  }
  arrfree(proxy_stuck);
}
