#include "Game.hpp"

Game::Game() {
  load_window();
  load_spritesheet();

  level = 1;
  time  = SDL_GetTicks();
  on    = true;

  create_dungeon();
}

Game::~Game() {
  Entity_Iterator entity;
  Entity_Iterator end = this->entities.end();
  for (entity = this->entities.begin(); entity != end; ++entity) { 
    delete (*entity);
    this->entities.erase(entity);
  }
}

void Game::create_dungeon() {
  Entity_Iterator entity;
  Entity_Iterator end = this->entities.end();

  int i = 1;
  for (entity = this->entities.begin(); entity != end; ++entity) { 
    this->entities.insert(this->entities.begin(), 
                          new Entity(TYPE_MONSTER, Location(i*128, i*128)));
    i++;
  }   

  /* Player is always at the start of the list */
  this->entities.insert(this->entities.begin(), 
                        new Entity(TYPE_PLAYER, Location(20, 20)));
}

void Game::update_all_entities() {
  Entity_Iterator entity = this->entities.begin();
  Entity_Iterator end = this->entities.end();

  /* The player updates itself based on input, no need to update */
  for (entity = ++entity; entity != end; ++entity) { 
      
    //if (entity->location.is_adjacent(player->location)) {
    //  entity_attacks(entity, start, currentFloor);

    //  entity = entity->next;
    //  continue;
    //}

    if ((*entity)->location.is_nearby(PLAYER->location)) {
      (*entity)->destination = PLAYER->location;

      continue;
    }

    if ((*entity)->location.is_same((*entity)->destination)) {
      Location destination = (*entity)->location.new_destination();
      if (IN_WORLD(destination.x, destination.y)) {
        (*entity)->destination = destination;
      }
    }
  }
}

void Game::update(unsigned dt) {
  if(dt >= 250) {
    update_all_entities();
    this->time = SDL_GetTicks();

    Entity_Iterator entity;
    Entity_Iterator end = this->entities.end();

    for (entity = this->entities.begin(); entity != end; ++entity) { 
      /* Cycle through an entity's frames while walking */
      if ((*entity)->idle == false) {
        (*entity)->frame = (*entity)->frame ? 0 : 1;
      }

      if((*entity)->do_frames > 0) {
        (*entity)->do_frames -= 1;

        if((*entity)->do_frames == 0) {
          (*entity)->state -= (*entity)->state > 3 ? 4 : 0;
        }
      } else {
        (*entity)->idle = true;
      }
    }
  }
}

void Game::draw_tile(uint8_t type, uint32_t x, uint32_t y) {
  SDL_Rect location     = {x * TILESIZE, y * TILESIZE};
  SDL_Rect mask         = {0, 148, 32, 32};
  SDL_Surface *sprite   = this->spritesheet;

  draw(sprite, &mask, this->screen, &location);
}

void Game::draw_entity(Entity *entity) {
  int animation_frame   = entity->idle? 0 : entity->frame;
  SDL_Rect location     = {entity->location.x, entity->location.y};
  SDL_Surface *sprite   = this->spritesheet;

  /* 
   * So, we don't have to load a large amount of SDL_Surfaces,
   * we use math based on an Entity's state/type/frame to see
   * where on the sprite sheet we are getting the image.
   */

  SDL_Rect frame = { 
    (128 * entity->state) + (64 * entity->frame),
    entity->type, SPRITESIZE, SPRITESIZE 
  };

  draw(sprite, &frame, this->screen, &location); 
}

void Game::render() {
  /* Draw the Floor */
  for (int x = 0; x < SCREENX; x++) {
    for (int y = 0; y < SCREENY; y++) {
      draw_tile(FLOOR, x, y);
    }
  }

  /* Draw the health bar */
  int health = PLAYER->hp;
  for (int i = 0; i < health; i++) {
    SDL_Rect location    = {(i*20), SCREENY - 20};
    SDL_Surface *sprite  = this->spritesheet;
    SDL_Rect frame       = {0, 128, 20, 20};

    draw(sprite, &frame, this->screen, &location);
  }

  /* Draw each entity */
  Entity_Iterator entity;
  Entity_Iterator end = this->entities.end();
  for (entity = this->entities.begin(); entity != end; ++entity) { 
    if((*entity)->hp > 0) {
      draw_entity(*entity);
    }
  }

  SDL_Flip(this->screen);
}


void Game::load_window() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);
  atexit(SDL_Quit);

  this->screen = SDL_GetVideoSurface();
}

void Game::load_spritesheet() {
  SDL_Surface *temp = IMG_Load("Graphics/spritesheet.png");

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
    printf("Failed to convert image to native format\n");
    exit(1);
  }

  this->spritesheet = sprite;
}

void Game::draw(SDL_Surface *sprite, SDL_Rect *frame, 
                SDL_Surface *screen, SDL_Rect *location) {
  if(SDL_BlitSurface(sprite, frame, screen, location) < 0) {
    printf("Error! Drawing Entity: %s\n", SDL_GetError());
  }
}
