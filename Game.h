#ifndef DEARTH_GAME_HPP
#define DEARTH_GAME_HPP

#include "Render.h"
#include "Entity.h"

#define TOTAL_ENTITIES    16

struct Game {
  bool      on;
  uint8_t   level;
  uint32_t  last_time;
  uint32_t  update_rate;

  SDL_Surface  *spritesheet;

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
