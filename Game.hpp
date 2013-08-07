/*
 * The Game object is not decoupled from rendering. It doesn't necessarily draw
 * itself, but it does draw the objects which it controls (the entities). 
 *
 * The Game object handles most of the checks about the game (collision, HP, 
 * etc) and handles these things each tick.
 *
 * Every .25 seconds (1/4th of the second), the Game object updates frames and
 * gives Entities new destinations, or tells them to attack if they can.
 */

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
  Entity     *player;

  Game();
  ~Game();

  void create_dungeon();
  void update_all_entities();
  void update(unsigned dt);

  void move_all_entities();

  void draw_tile(uint8_t type, uint32_t x, uint32_t y);
  void draw_entity(Entity *entity);

  void render();

protected:
  SDL_Surface  *screen;
  SDL_Surface  *spritesheet;

  void draw(SDL_Surface *sprite, SDL_Rect *frame, 
            SDL_Surface *screen, SDL_Rect *location);

private:
  void load_window();
  void load_spritesheet();
};

#endif
