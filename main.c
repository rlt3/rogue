#include <stdlib.h>
#include <stdbool.h>

#include "Game.h"

#define FLOOR             224
#define HEART             240

#define TOTAL_ENTITIES    16

int main(int argc, char **argv) {
  SDL_Surface *surface     = load_window();
  SDL_Surface *spritesheet = load_sprite("Graphics/loz.png");

  struct Entity *entities_head = malloc(sizeof(struct Entity));
  *entities_head = (struct Entity){
    .type        = 0,
    .state       = IDLE,
    .hp          = 10,
    .frame       = 0,
    .idle        = true,
    .location    = ((struct Location){64, 64}),
    .destination = ((struct Location){64, 64}),
    .next        = NULL
  };

  SDL_Event event;
  bool on = true;

  while (on) {

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
          case SDLK_ESCAPE: case SDL_QUIT:
            on = false;
            break;
          case SDLK_LSHIFT: case SDLK_RSHIFT:
            remove_second_entity(&entities_head);
            break;
          case SDLK_SPACE:
            add_entity(&entities_head);
            break;
          default:
            break;
          }
      }
    }

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xCC, 0xCC, 0xCC));

    struct Entity *entity = entities_head;
    while (entity != NULL) {
      draw_entity(entity, spritesheet, surface);
      entity = entity->next;
    }

    SDL_Flip(surface);

  }

  SDL_FreeSurface(spritesheet);
  SDL_FreeSurface(surface);

  struct Entity *prev;
  struct Entity *node = entities_head;

  while (node->next != NULL) {
    prev = node;
    node = node->next;
    free(prev);
  }
  
  return EXIT_SUCCESS;
}
