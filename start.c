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

SDL_Surface* load_window();
void load_animations(SDL_Surface *sprites[], SDL_Rect frames[8][2]);
SDL_Surface *load_sprite(const char filename[]);

void create_dungeon(Entity entities[], int dungeonFloor);
void game_loop(SDL_Surface *screen, 
               SDL_Surface *sprites[], 
               SDL_Rect frames[8][2],
               Entity entities[],
               int dungeonFloor);

void handle_input(SDLKey key, Entity *Player, bool *running);
void update_entity(Entity entity[], uint8_t state);


void render(SDL_Surface *screen, 
            Entity *entities, 
            SDL_Surface *sprites[], 
            SDL_Rect frames[8][2],
            int frameToDraw);

void draw_tile(SDL_Surface *screen, SDL_Rect frames[8][2], 
               SDL_Surface *sprites[], uint8_t type,
               Location loc);

void draw_entity(SDL_Surface *screen, SDL_Rect frames[8][2],
                 SDL_Surface *sprites[], Entity *entity, 
                 int frameToDraw);

void draw(SDL_Surface *sprite, SDL_Rect *frame, 
          SDL_Surface *screen, SDL_Rect *location);

int main(int argc, char **argv) {
  static SDL_Surface *screen;
  
  static SDL_Surface *sprites[TOTAL_ENTITIES];
  static Entity entities[TOTAL_ENTITIES];

  static SDL_Rect frames[8][2];

  int dungeonLevel = 0;
    
  screen = load_window();
  load_animations(sprites, frames);
  create_dungeon(entities, dungeonLevel);
  game_loop(screen, sprites, frames, entities, dungeonLevel);

  return EXIT_SUCCESS;
}

SDL_Surface* load_window() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  atexit(SDL_Quit);

  SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);

  return SDL_GetVideoSurface();
}

void load_animations(SDL_Surface *sprites[], SDL_Rect frames[8][2]) {
  sprites[FLOOR]  = load_sprite("graphics/floor.png");
  sprites[ENTITY] = load_sprite("graphics/spritesheet.png"); 

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
}

SDL_Surface *load_sprite(const char filename[]) {
  SDL_Surface *temp = IMG_Load(filename);
  SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), 
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

void create_dungeon(Entity entities[], int dungeonFloor) {
  Location location = {100, 100};
  Entity Player = (Entity){0, IDLE, 10, 0, location, location, true};
  entities[0] = Player;
}

void game_loop(SDL_Surface *screen, 
               SDL_Surface *sprites[], 
               SDL_Rect frames[8][2],
               Entity entities[],
               int dungeonFloor) {

  SDL_Event event;

  unsigned short int frameToDraw = 0;
  unsigned t = SDL_GetTicks();
  bool running = true;

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
        handle_input(event.key.keysym.sym, &player, &running);
      }
    }

    render(screen, entities, sprites, frames, frameToDraw);
  }
}

void handle_input(SDLKey key, Entity *Player, bool *running) {
  switch(key) {
  case SDLK_ESCAPE: case SDL_QUIT:
    *running = false;
    break;

  case SDLK_w: case SDLK_UP: case SDLK_k:
    update_entity(Player, WALK_UP);
    break;

  case SDLK_a: case SDLK_LEFT: case SDLK_h:
    update_entity(Player, WALK_LEFT);
    break;

  case SDLK_s: case SDLK_DOWN: case SDLK_j:
    update_entity(Player, WALK_DOWN);
    break;

  case SDLK_d: case SDLK_RIGHT: case SDLK_l:
    update_entity(Player, WALK_RIGHT);
    break;

  case SDLK_SPACE:
    update_entity(Player, ATTACKING);
    break;

  default:
    break;
  }
}

void update_entity(Entity entity[], uint8_t state) {
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

void render(SDL_Surface *screen, 
            Entity *entities, 
            SDL_Surface *sprites[], 
            SDL_Rect frames[8][2],
            int frameToDraw) {
  for (int x = 0; x < SCREENX; x++) {
    for (int y = 0; y < SCREENY; y++) {
      Location location = { x * TILESIZE, y * TILESIZE };
      draw_tile(screen, frames, sprites, FLOOR, location);
    }
  }

  for (int i = 0; i <=0; i++) {
    draw_entity(screen, frames, sprites, &entities[i], frameToDraw);
  }

  SDL_Flip(screen);
}

void draw_tile(SDL_Surface *screen, SDL_Rect frames[8][2], 
               SDL_Surface *sprites[], uint8_t type,
               Location loc) { 
  SDL_Rect location = {loc.x, loc.y};
  SDL_Surface *sprite = sprites[type];
  draw(sprite, NULL, screen, &location);
}

void draw_entity(SDL_Surface *screen, SDL_Rect frames[8][2],
                 SDL_Surface *sprites[], Entity *entity, 
                 int frameToDraw) {
  int animation_frame = entity->idle? 0 : frameToDraw;

  SDL_Rect location = {entity->location.x, entity->location.y};
  SDL_Surface *sprite = sprites[ENTITY];
  SDL_Rect frame = frames[entity->state][animation_frame];

  draw(sprite, &frame, screen, &location);
}

void draw(SDL_Surface *sprite, SDL_Rect *frame, 
          SDL_Surface *screen, SDL_Rect *location) {
  if(SDL_BlitSurface(sprite, frame, screen, location) < 0) {
    printf("Error! Drawing Tile: %s\n", SDL_GetError());
  }
}
