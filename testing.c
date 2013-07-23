#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#include "frames.h"

#define TOTAL_ENTITIES    16
#define TILESIZE          32
#define SPRITESIZE        64

#define WALK_UP           0
#define WALK_RIGHT        1
#define WALK_DOWN         2
#define WALK_LEFT         3

#define ATTACK_UP         4
#define ATTACK_RIGHT      5
#define ATTACK_DOWN       6
#define ATTACK_LEFT       7

#define ATTACKING         8
#define IDLE              2

#define SCREENX           640
#define SCREENY           512

#define FLOOR             0
#define ENTITY            1

#define player            entities[0]

typedef struct Location {
  uint32_t  x;
  uint32_t  y;
} Location;

typedef struct Entity {
  uint8_t   type;
  uint8_t   state;
  uint8_t   hp;
  uint8_t   frames;
  Location  location;
  Location  destination;
  bool      idle;
} Entity;

/* Functions */

void init();
void game_loop();
void render();
void handle_input(SDLKey key);

void draw_tile(uint8_t type, uint32_t x, uint32_t y);
void draw_entity(Entity *entity);
SDL_Surface *load_sprite(const char filename[]);

void update_entity(Entity *entity, uint8_t state);
void entity_attacks(Entity* entity);

/* Variables */

SDL_Surface *screen;
SDL_Event event;

static SDL_Surface *sprites[TOTAL_ENTITIES];
static Entity entities[TOTAL_ENTITIES];

extern SDL_Rect frames[8][2];

unsigned short int frameToDraw;
unsigned int t;
bool running;

int currentFloor = 0;

/*
 * Using this same idea of having the delta time
 * (or current ticks) change the frame for us,
 * I can limit that frame from updating for every
 * .25 seconds or something.
 *
 * So, every .25 seconds (or .5 seconds) change
 * the global `frameToDraw' counter to the next
 */

int main(int argc, char **argv) {
  running = true;

  init();
  load_frames();
  game_loop();

  return EXIT_SUCCESS;
}

void init() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  atexit(SDL_Quit);

  screen = SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);

  sprites[FLOOR]  = load_sprite("graphics/floor.png");
  sprites[ENTITY] = load_sprite("graphics/spritesheet.png"); 

  Location location = {100, 100};
  Entity Player = (Entity){0, IDLE, 10, 0, location, location, true};
  entities[0] = Player;

  int i;
  for (i = 1; i <= currentFloor; i++) {
    Location location = {150, 150};
    entities[i] = (Entity){0, IDLE, 10, 0, location, location, true};
  }

  t = SDL_GetTicks();
  frameToDraw = 0;
}

void game_loop() {

  while (running) {
    
    if((SDL_GetTicks() - t) >= 250) {
      t = SDL_GetTicks();

      frameToDraw = frameToDraw ? 0 : 1;

      if(player.frames > 0) {
        player.frames -= 1;

        if(player.frames == 0) {
          player.state -= player.state > 3 ? 4 : 0;
        }
      } else {
        player.idle = true;
      }

    }

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          handle_input(event.key.keysym.sym);
      }
    }

    render();
  }
}

void handle_input(SDLKey key) {
  switch(key) {
  case SDLK_ESCAPE: case SDL_QUIT:
    running = false;
    break;

  case SDLK_w: case SDLK_UP: case SDLK_k:
    update_entity(&player, WALK_UP);
    break;

  case SDLK_a: case SDLK_LEFT: case SDLK_h:
    update_entity(&player, WALK_LEFT);
    break;

  case SDLK_s: case SDLK_DOWN: case SDLK_j:
    update_entity(&player, WALK_DOWN);
    break;

  case SDLK_d: case SDLK_RIGHT: case SDLK_l:
    update_entity(&player, WALK_RIGHT);
    break;

  case SDLK_SPACE:
    update_entity(&player, ATTACKING);
    break;

  default:
    break;
  }
}

void render() {
  for (int x = 0; x < SCREENX; x++) {
    for (int y = 0; y < SCREENY; y++) {
      draw_tile(FLOOR, x, y);
    }
  }

  for (int i = 0; i <= currentFloor; i++) {
    draw_entity(&entities[i]);
  }

  SDL_Flip(screen);
}

void draw_tile(uint8_t type, uint32_t x, uint32_t y) {
  SDL_Rect location = { x * TILESIZE, y * TILESIZE };
  SDL_Surface *sprite = sprites[type];

  if(SDL_BlitSurface(sprite, NULL, screen, &location) < 0) {
    printf("Error!\n");
  }
}

void draw_entity(Entity *entity) {
  int animation_frame = entity->idle? 0 : frameToDraw;

  SDL_Rect spriteLocationation = { entity->location.x, entity->location.y };
  SDL_Surface *sprite = sprites[ENTITY];
  SDL_Rect frame = frames[entity->state][animation_frame];

  if(SDL_BlitSurface(sprite, &frame, screen, &spriteLocationation) < 0) {
    printf("Error!\n");
  }
}

SDL_Surface *load_sprite(const char filename[]) {
  SDL_Surface *temp = IMG_Load(filename);

  SDL_SetColorKey(temp, 
      (SDL_SRCCOLORKEY|SDL_RLEACCEL), 
      SDL_MapRGB(temp->format, 0, 0, 0));


  if (temp == NULL) {
    printf("Error: %s\n", IMG_GetError());
    exit(1);
  }

  SDL_Surface *sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  if (sprite == NULL) {
    printf("Failed to convert image to native format %s\n", filename);
    exit(1);
  }

  return sprite;
}

void entity_attacks(Entity* entity) {
  puts("Attacked!");
  entity->state += 4;
}

void update_entity(Entity *entity, uint8_t state) {
  entity->idle = false;

  if (state == ATTACKING) {
    entity->state += 4;
    entity->frames = 2;
    return;
  }

  entity->state = state;

  switch(state) {
  case WALK_UP:
    entity->location.y -= 10;
    break;
  case WALK_DOWN:
    entity->location.y += 10;
    break;
  case WALK_LEFT:
    entity->location.x -= 10;
    break;
  case WALK_RIGHT:
    entity->location.x += 10;
    break;
  default:
    break;
  }

}
