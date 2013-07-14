#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

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

#define IDLE              2

#define SCREENX           640
#define SCREENY           512

#define FLOOR             0
#define ENTITY            1

typedef struct Location {
  uint32_t x, y;
} Location;

typedef struct Entity {
  uint8_t type;
  uint8_t state;
  uint8_t hp;
  uint8_t frame;
  Location location;
  Location direction;
  bool idle;
} Entity;

void init();
void game_loop();
void render();
void handle_input(SDLKey key);

void draw_tile(uint8_t type, uint32_t x, uint32_t y);
void draw_entity();
SDL_Surface * load_sprite(const char filename[]);

void entity_attacks(Entity* entity);

SDL_Surface *screen;
SDL_Event event;

static SDL_Surface *sprites[TOTAL_ENTITIES];
static SDL_Rect frames[8][2];
static Entity player;

unsigned short int frameToDraw;
unsigned int dt;
unsigned int t;
unsigned int future;
bool running;

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
  game_loop();

  return EXIT_SUCCESS;
}

void init() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  atexit(SDL_Quit);

  screen = SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);

  sprites[FLOOR] = load_sprite("graphics/floor.png");
  sprites[ENTITY] = load_sprite("graphics/spritesheet.png"); 

  Location location = {100, 100};
  Location direction = {1, 0};
  player = (Entity){0, IDLE, 10, 0, location, direction, true};

  /* Regular movement frames */
  frames[0][0] = (SDL_Rect){  0,  0, 64, 64};
  frames[0][1] = (SDL_Rect){ 64,  0, 64, 64};

  frames[1][0] = (SDL_Rect){128,  0, 64, 64};
  frames[1][1] = (SDL_Rect){192,  0, 64, 64};

  frames[2][0] = (SDL_Rect){256,  0, 64, 64};
  frames[2][1] = (SDL_Rect){320,  0, 64, 64};

  frames[3][0] = (SDL_Rect){384,  0, 64, 64};
  frames[3][1] = (SDL_Rect){448,  0, 64, 64};

  /* Attacking frames */
  frames[4][0] = (SDL_Rect){  0, 64, 64, 64};
  frames[4][1] = (SDL_Rect){ 64, 64, 64, 64};

  frames[5][0] = (SDL_Rect){128, 64, 64, 64};
  frames[5][1] = (SDL_Rect){192, 64, 64, 64};

  frames[6][0] = (SDL_Rect){256, 64, 64, 64};
  frames[6][1] = (SDL_Rect){320, 64, 64, 64};

  frames[7][0] = (SDL_Rect){384, 64, 64, 64};
  frames[7][1] = (SDL_Rect){448, 64, 64, 64};

  t = SDL_GetTicks();
  frameToDraw = 0;
}

void game_loop() {
  int count = 0;

  while (running) {

    /*
     * Every .25 seconds, change the frame to be drawn.
     * This is the master frame that makes it so we
     * can decouple game logic and rendering logic as
     * much as I can.
     */
    if((SDL_GetTicks() - t) >= 250) {
      dt = SDL_GetTicks() - t;
      t = SDL_GetTicks();

      frameToDraw = frameToDraw ? 0 : 1;
      player.idle = true;

    }

    if(SDL_GetTicks() <= future) {
      unsigned int diff = future - SDL_GetTicks();
      printf("%u :: %u => %u\n", SDL_GetTicks(), future, diff);

      if(diff <= 250) {
        count++;

        if(count == 3) {
          player.state -= player.state > 3 ? 4 : 0;
          count = 0;
        }
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
    player.location.y -= 10;
    player.direction = (Location){0, -1};
    player.state = WALK_UP;
    player.idle = false;
    break;

  case SDLK_a: case SDLK_LEFT: case SDLK_h:
    player.location.x -= 10;
    player.direction = (Location){-1, 0};
    player.state = WALK_LEFT;
    player.idle = false;
    break;

  case SDLK_s: case SDLK_DOWN: case SDLK_j:
    player.location.y += 10;
    player.direction = (Location){0, 1};
    player.state = WALK_DOWN;
    player.idle = false;
    break;

  case SDLK_d: case SDLK_RIGHT: case SDLK_l:
    player.location.x += 10;
    player.direction = (Location){1, 0};
    player.state = WALK_RIGHT;
    player.idle = false;
    break;

  case SDLK_SPACE:
    player.idle = false;
    player.state += 4;
    future = SDL_GetTicks() + 500;
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

  draw_entity();
  SDL_Flip(screen);
}

void draw_tile(uint8_t type, uint32_t x, uint32_t y) {
  SDL_Rect location = { x * TILESIZE, y * TILESIZE };
  SDL_Surface *sprite = sprites[type];

  if(SDL_BlitSurface(sprite, NULL, screen, &location) < 0) {
    printf("Error!\n");
  }
}

void draw_entity() {
  int animation_frame = player.idle? 0 : frameToDraw;

  SDL_Rect spriteLocationation = { player.location.x, player.location.y };
  SDL_Surface *sprite = sprites[ENTITY];
  SDL_Rect frame = frames[player.state][animation_frame];

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
  //switch(entity.state) {
  //  case WALK_RIGHT:
  //  case WALK_LEFT:
  //  case WALK_UP:
  //  case WALK_DOWN:
  //}
}
