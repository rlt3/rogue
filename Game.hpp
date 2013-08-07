#ifndef ROGUE_GAME_HPP
#define ROGUE_GAME_HPP

#define SCREENX           640
#define SCREENY           512
#define TILESIZE          32
#define SPRITESIZE        64

#define FLOOR             0

#define TOTAL_ENTITIES    16
#define PLAYER            (*this->entities.begin())

#define IN_WORLD(x, y) \
  (x >= 0 && y >= 0 && x < SCREENX && y < SCREENY)

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <list>

#include "Entity.hpp"
#include "Location.hpp"

class Game {
public:
  uint8_t   level;
  uint32_t  time;
  bool      on;

  Entity_List entities;

  Game();
  ~Game();

  void create_dungeon();
  void update_all_entities();
  void update(unsigned dt);

  void draw_tile(uint8_t type, uint32_t x, uint32_t y);
  void draw_entity(Entity *entity);

  void render();

protected:
  SDL_Surface  *screen;
  SDL_Surface  *spritesheet;

  void load_window();

private:
  void load_spritesheet();
  void draw(SDL_Surface *sprite, SDL_Rect *frame, 
            SDL_Surface *screen, SDL_Rect *location);
};

#endif
