#include "Game.hpp"

void handle_input(SDL_Event event, Game &game);

int main(int argc, char **argv) {
  Game game;
  SDL_Event event;

  Loading loading_screen;
  bool off = loading_screen.display();

  while (game.on && off) {
    game.update(SDL_GetTicks());

    while (SDL_PollEvent(&event)) {
      //printf("%d: (%d, %d)\n", game.player->state,
      //                         game.player->destination.x,
      //                         game.player->destination.y);
      handle_input(event, game);
    }

    game.move_all_entities();
    game.render();
  }

  return EXIT_SUCCESS;
}

/* Union types of Game for the loading screens, etc */
void handle_input(SDL_Event event, Game &game) {
  switch (event.type) {
    case SDL_MOUSEMOTION:
      //printf(">(%d, %d)\n", event.motion.xrel, event.motion.yrel);
      break;

    case SDL_MOUSEBUTTONDOWN:
      //printf("@(%d, %d)\n", event.button.x, event.button.y);
      break;

    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
      case SDLK_LSHIFT: case SDLK_RSHIFT:
        game.player->framerate = 125;
        game.player->speed = 3;
        break;

      case SDLK_ESCAPE: case SDL_QUIT:
        //loading_screen.on = true;
        //loading_screen.splash_loop();
        game.on = false;
        break;

      case SDLK_w: case SDLK_UP: case SDLK_k:
        game.player->set_state(WALK_UP);
        break;

      case SDLK_a: case SDLK_LEFT: case SDLK_h:
        game.player->set_state(WALK_LEFT);
        break;

      case SDLK_s: case SDLK_DOWN: case SDLK_j:
        game.player->set_state(WALK_DOWN);
        break;

      case SDLK_d: case SDLK_RIGHT: case SDLK_l:
        game.player->set_state(WALK_RIGHT);
        break;

      case SDLK_SPACE:
        game.player->set_state(ATTACKING);
        game.player->attack(game.entities);
        break;

      default:
        break;
      }
      break;

    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_LSHIFT:
        game.player->framerate = 250;
        game.player->speed = 1;
        break;
      default:
        break;
      }
  }
}
