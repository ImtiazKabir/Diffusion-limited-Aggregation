#ifndef ENGINE_FOR_EMS_SDL
#define ENGINE_FOR_EMS_SDL

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#define TITLE_OF_WINDOW "TITLE OF WINDOW"
#define WIDTH (int)500
#define HEIGHT (int)500
#define FPS (uint32_t)60

static inline void __PRINT_ERROR__(char const * const func_name) {
  fprintf(stderr, "%s did not work\n---------------\n%s\n\n\n\n",
                    func_name, SDL_GetError());
  SDL_ClearError();
}
char *__get_path__(char const * const child);  /* lib/getpath.c */

/* engine.c */
void main_loop(void * v_renderer);



/* event.c */
bool event_handler(void);

/* once.c */
void setup(void);
void clean_up(void);

/* loop.c */
void update(void);
void draw(SDL_Renderer * renderer);

#endif /* ENGINE_FOR_EMS_SDL */