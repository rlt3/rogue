#ifndef ROGUE_GAME_HPP
#define ROGUE_GAME_HPP

#define SCREENX           640
#define SCREENY           512

#define TOTAL_ENTITIES    16
#define PLAYER            this->entities.first()

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <list>

#include "Entity.hpp"

class Game {
public:
  uint8_t   level;
  uint32_t  time;
  bool      on;

  std::list<Entity> entities;

  void create_dungeon(int dungeon_floor);
  void update_all_entities();
  void update_game(unsigned dt);

  void draw_tile(uint8_t type, uint32_t x, uint32_t y);
  void draw_entity(Entity &entity);

protected:
  SDL_Surface  *screen;
  SDL_Surface  *spritesheet

  void load_window();

private:
  SDL_Surface *load_sprite(const char filename[]);

  void draw(SDL_Surface *sprite, SDL_Rect *frame, 
            SDL_Surface *screen, SDL_Rect *location);
};

#endif
