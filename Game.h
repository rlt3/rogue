#ifndef DEARTH_GAME_HPP
#define DEARTH_GAME_HPP

#include "Window.h"
#include "Entity.h"

#define FLOOR             224
#define HEART             240

#define TOTAL_ENTITIES    16

struct Game {
  bool      on;
  uint8_t   level;
  uint32_t  last_time;
  uint32_t  update_rate;

  Spritesheet spritesheet;

  //struct Item   *items_head;
  struct Entity *entities_head;
  struct Entity *player;

  void (*update)(struct Game*, unsigned time);
  void (*handle)(struct Game*);
  void (*render)(struct Game*);
};

struct Game* new_game();
void delete_game(struct Game*);

#endif
