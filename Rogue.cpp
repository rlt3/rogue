#include "Game.hpp"

void handle_input(SDL_Event event, Game &game);

int main(int argc, char **argv) {
  Game game;
  SDL_Event event;

  while (game.on) {
    game.update((SDL_GetTicks() - game.time));

    while (SDL_PollEvent(&event)) {
      handle_input(event, game);
    }

    game.move_all_entities();
    game.render();
  }

  return EXIT_SUCCESS;
}

void handle_input(SDL_Event event, Game &game) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
      case SDLK_LSHIFT:
        game.player->speed = 3;
        break;

      case SDLK_ESCAPE: case SDL_QUIT:
        game.on = false;
        break;

      case SDLK_w: case SDLK_UP: case SDLK_k:
        game.player->update(WALK_UP);
        break;

      case SDLK_a: case SDLK_LEFT: case SDLK_h:
        game.player->update(WALK_LEFT);
        break;

      case SDLK_s: case SDLK_DOWN: case SDLK_j:
        game.player->update(WALK_DOWN);
        break;

      case SDLK_d: case SDLK_RIGHT: case SDLK_l:
        game.player->update(WALK_RIGHT);
        break;

      case SDLK_SPACE:
        game.player->update(ATTACKING);
        game.player->attack(game.entities);
        break;

      default:
        break;
      }
      break;

    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_LSHIFT:
        game.player->speed = 1;
        break;
      default:
        break;
      }
  }
}
