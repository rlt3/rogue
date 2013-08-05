#ifndef ROGUE_RENDER_H
#define ROGUE_RENDER_H

#define TILESIZE          32
#define SPRITESIZE        64

#define FLOOR             0
#define ENTITY            1

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#include "Entity.h"
#include "Game.h"

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

void load_sprites(SDL_Surface *sprites[]) {
  sprites[FLOOR]  = load_sprite("graphics/floor.png");
  sprites[ENTITY] = load_sprite("graphics/spritesheet.png"); 
}

void draw(SDL_Surface *sprite, SDL_Rect *frame, 
          SDL_Surface *screen, SDL_Rect *location) {
  if(SDL_BlitSurface(sprite, frame, screen, location) < 0) {
    printf("Error! Drawing Entity: %s\n", SDL_GetError());
  }
}

void draw_tile(Game *game, uint8_t type, uint32_t x, uint32_t y) {
  SDL_Rect location     = {x * TILESIZE, y * TILESIZE};
  SDL_Surface *sprite   = game->sprites[type];

  draw(sprite, NULL, game->screen, &location);
}

void draw_entity(Entity *entity, Game *game) {
  int animation_frame   = entity->idle? 0 : game->frame;
  SDL_Rect location     = {entity->location.x, entity->location.y};
  SDL_Surface *sprite   = game->sprites[ENTITY];
  SDL_Rect frame        = game->frames[entity->state][animation_frame];

  draw(sprite, &frame, game->screen, &location); 

  //SDL_Rect first  = {entity->location.x + 16, entity->location.y + 16, 32, 32};

  //SDL_FillRect(game->screen, &first, SDL_MapRGB((game->screen)->format, 0xFF, 0xFF, 0xFF));

}

void render(Game *game) {
  /* Draw the Floor */
  for (int x = 0; x < SCREENX; x++) {
    for (int y = 0; y < SCREENY; y++) {
      draw_tile(game, FLOOR, x, y);
    }
  }

  /* Draw the health bar */
  int health = PLAYER.hp;
  for (int i = 0; i < health; i++) {
    SDL_Rect location    = {(i*20), SCREENY - 20};
    SDL_Surface *sprite  = game->sprites[ENTITY];
    SDL_Rect frame       = game->frames[8][0];

    draw(sprite, &frame, game->screen, &location);
  }

  /* Draw each entity */
  Entity *entity = &game->entities;
  while (entity != NULL) {
    if(entity->hp > 0) {
      draw_entity(entity, game);
    }
    entity = entity->next;
  }

  SDL_Flip(game->screen);
}


#endif
