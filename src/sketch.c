#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "sketch.h"
#include "particle.h"

#define STB_DS_IMPLEMENTATION
#include "stb/stb_ds.h"

typedef struct MainLoopParam {
  SDL_Renderer * renderer;
  bool quit_flag;
  int const FPS;
  int const WIDTH;
  int const HEIGHT;

  SDL_Texture * move_texture;
  SDL_Texture * stuck_texture;
  int const NUM_OF_PARTICLES;
  Particle ** particles;
  int ** stuck_indices_p;
  bool show_mover;
} MainLoopParam_t;

void main_loop(void *v_param);


void MEOW_Repeat(
  SDL_Renderer * renderer,
  int const WIDTH,
  int const HEIGHT,
  int const FPS,
  int const NUM_OF_PARTICLES
) {
  SDL_Texture * move_texture;
  SDL_Texture * stuck_texture;
  Particle ** particles;
  int * stuck_indices = NULL;
  bool show_mover = true;

  /* Definition and setting variables for sketch */
  setup(
    renderer,
    &move_texture,
    &stuck_texture,
    &particles,
    NUM_OF_PARTICLES,
    WIDTH,
    HEIGHT,
    &stuck_indices
  );

  MainLoopParam_t param = {
    .renderer = renderer,
    .quit_flag = false,
    .FPS = FPS,
    .WIDTH = WIDTH,
    .HEIGHT = HEIGHT,
    .move_texture = move_texture,
    .stuck_texture = stuck_texture,
    .NUM_OF_PARTICLES = NUM_OF_PARTICLES,
    .particles = particles,
    .stuck_indices_p = &stuck_indices,
    .show_mover = show_mover
  };

  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(main_loop, &param, 0, 1);
  #else
  while (!param.quit_flag) {
    main_loop(&param);
  }
  #endif

  /* cleaning up sekcth "things" */
  clean_up(
    move_texture,
    stuck_texture,
    particles,
    NUM_OF_PARTICLES,
    stuck_indices
  );
}


void main_loop(void *v_param) {
  MainLoopParam_t * param = (MainLoopParam_t *) v_param;

  /* handle event */
  if (event_handler(&param->show_mover)) {
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #else
    param->quit_flag = true;
    return;
    #endif /* __EMSCRIPTEN__ */
  }

  /* update and draw */
  update(
    param->particles,
    param->NUM_OF_PARTICLES,
    param->WIDTH,
    param->HEIGHT,
    param->stuck_indices_p
  );

  draw(
    param->renderer,
    param->particles,
    param->NUM_OF_PARTICLES,
    param->move_texture,
    param->stuck_texture,
    param->show_mover
  );
  SDL_Delay(1000 / (unsigned)param->FPS);
  SDL_RenderPresent(param->renderer);
}


