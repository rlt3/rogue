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
//#define TILESIZE          32
//#define SPRITESIZE        64

#define TILESIZE          16
#define SPRITESIZE        16

//#define FLOOR             148
//#define HEART             128

#define FLOOR             224
#define HEART             240

#define TOTAL_ENTITIES    16

#define IN_WORLD(x, y) \
  (x >= 0 && y >= 0 && x < SCREENX && y < SCREENY)

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <list>

#include "Screen.hpp"
#include "Loading.hpp"
#include "Heart.hpp"
#include "Entity.hpp"
#include "Location.hpp"

class Game : public Screen {
public:
  uint8_t   level;
  bool      on;

  uint32_t  last_time;
  uint32_t  update_rate;

  Item_List       items;
  Entity_List     entities;
  Entity_Iterator player;
  //Entity     *player;

  Game();
  ~Game();

  void create_dungeon();
  void check_all_entities(unsigned time);
  void update(unsigned time);

  void move_all_entities();

  void draw_tile(uint8_t type, uint32_t x, uint32_t y);
  void draw_entity(Entity *entity);

  void render();

private:
  SDL_Surface  *spritesheet;
};

#endif
