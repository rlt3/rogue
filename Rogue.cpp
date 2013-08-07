#include "Game.hpp"

void main_loop(Game &game);
void handle_input(SDLKey key, Game &game);
void move_all_entities(Entity_List &entities);

int main(int argc, char **argv) {
  Game game;

  return EXIT_SUCCESS;
}

void main_loop(Game &game) {
  SDL_Event event;
  Entity *player = (*game.entities.begin());

  while (game.on) {
    game.update((SDL_GetTicks() - game.time));

    if (player->hp <= 0) {
      puts("You lose!");
      game.on = false;
    }

    /* If only the player exists, create next level */
    if (game.entities.size() == 1) {
      game.level++;
      game.create_dungeon();
    }

    Entity_Iterator entity;
    Entity_Iterator end = game.entities.end();
    for (entity = game.entities.begin(); entity != end; ++entity) { 
      if((*entity)->hp <= 0) {
        game.entities.erase(entity);
      }
    }

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          handle_input(event.key.keysym.sym, game);
          break;
        case SDL_KEYUP:
          switch (event.key.keysym.sym) {
          case SDLK_LSHIFT:
            player->speed = 1;
            break;
          default:
            break;
          }
      }
    }

    move_all_entities(game.entities);
    game.render();
  }
}

void handle_input(SDLKey key, Game &game) {
  Entity *player = (*game.entities.begin());
  switch(key) {
  case SDLK_LSHIFT:
    player->speed = 3;
    break;

  case SDLK_ESCAPE: case SDL_QUIT:
    game.on = false;
    break;

  case SDLK_w: case SDLK_UP: case SDLK_k:
    player->update(WALK_UP);
    break;

  case SDLK_a: case SDLK_LEFT: case SDLK_h:
    player->update(WALK_LEFT);
    break;

  case SDLK_s: case SDLK_DOWN: case SDLK_j:
    player->update(WALK_DOWN);
    break;

  case SDLK_d: case SDLK_RIGHT: case SDLK_l:
    player->update(WALK_RIGHT);
    break;

  case SDLK_SPACE:
    player->update(ATTACKING);
    player->attack(game.entities);
    break;

  default:
    break;
  }
}

void move_all_entities(Entity_List &entities) {
  Entity_Iterator entity;
  Entity_Iterator end = entities.end();

  for (entity = entities.begin(); entity != end; ++entity) { 
    if (!(*entity)->location.is_same((*entity)->destination)
        && (*entity)->hp > 0) {
        (*entity)->move(entities);
    }
  }
}
