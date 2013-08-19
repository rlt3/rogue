#ifndef DEARTH_GAME_HPP
#define DEARTH_GAME_HPP

//#include "Render.h"
#include "Window.h"
#include "Entity.h"

#define TOTAL_ENTITIES    16

/*
 * Here, there is no reason to have a C++ style object full of methods. We only
 * need front-facing methods (function pointers) and then declare static 
 * functions as a kind of `private method.' So, this object would only have 
 * update, move_all_entities, render, and it's other non-function members.
 *
 * The functions like draw_tile would be static and just part of the game and
 * not for other use outside Game.c
 */

struct Game {
  bool      on;
  uint8_t   level;
  uint32_t  last_time;
  uint32_t  update_rate;

  Spritesheet spritesheet;

  //struct Item   *items_head;
  struct Entity *entities_head;
  struct Entity *player;
  
  void (*check_all_entities)(struct Game*, unsigned time);
  void (*move_all_entities)(struct Game*);
  void (*create_dungeon)(struct Game*);

  void (*update)(struct Game*, unsigned time);

  void (*draw_tile)(struct Game*, uint8_t type, uint32_t x, uint32_t y);
  //void (*draw_entity)(struct Game*, struct Entity *entity);
  void (*render)(struct Game*);
};

struct Game* new_game();

void check_all_entities(struct Game*, unsigned time);
void move_all_entities(struct Game*);
void create_dungeon(struct Game*);

void update(struct Game*, unsigned time);

void draw_tile(struct Game*, uint8_t type, uint32_t x, uint32_t y);
//void draw_entity(struct Game*, Entity *entity);
void render(struct Game*);

#endif
