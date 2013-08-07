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

  SDL_FreeSurface(this->spritesheet);
  SDL_FreeSurface(this->screen);
}

void Game::create_dungeon() {
  Entity_Iterator entity;
  Entity_Iterator end = this->entities.end();

  /* If we don't do this, the player multiplies */
  if (this->entities.size() > 0) {
    this->entities.clear();
  }

  int i;
  for (i = 0; i < this->level; i++) {
    this->entities.insert(
        this->entities.begin(), 
        new Entity(TYPE_MONSTER, Location(i*128, i*128))
    );
  }

  /* 
   * We have a pointer just to the player so that we can manipulate the 
   * list of entities in any fashion and not lose track of the most
   * important entity
   */

  this->player = (Entity*)malloc(sizeof(Entity));
  this->player = new Entity(TYPE_PLAYER, Location(64, 170));
  this->entities.insert(this->entities.begin(), player);
}

void Game::update_all_entities() {
  Entity_Iterator entity = this->entities.begin();
  Entity_Iterator end = this->entities.end();

  /* The player updates itself based on input, no need to update */
  for (entity = ++entity; entity != end; ++entity) { 
      
    if ((*entity)->location.is_nearby(this->player->location)) {
      if ((*entity)->location.is_adjacent(this->player->location)) {
        (*entity)->update(ATTACKING);
        (*entity)->attack(this->entities);
      } else {
        (*entity)->destination = this->player->location;
      }
      continue;
    }

    if ((*entity)->location.is_same((*entity)->destination)) {
      Location dest = (*entity)->location.new_destination((*entity)->speed);
      if (IN_WORLD(dest.x, dest.y)) {
        (*entity)->destination = dest;
      }
    }
  }
}
void Game::update(unsigned dt) {
  Entity_Iterator entity;
  Entity_Iterator end = this->entities.end();

  if(dt >= 250) {
    update_all_entities();
    this->time = SDL_GetTicks();

    end = this->entities.end();
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

  if (this->player->hp <= 0) {
    puts("You lose!");
    this->on = false;
  }

  /* If only the player exists, create next level */
  if (this->entities.size() == 1) {
    this->level++;
    this->create_dungeon();
  }

  end = this->entities.end();
  for (entity = this->entities.begin(); entity != end; ++entity) { 
    if((*entity)->hp <= 0) {
      this->entities.erase(entity);
    }
  }

}

void Game::move_all_entities() {
  Entity_Iterator entity;
  Entity_Iterator end = this->entities.end();

  for (entity = this->entities.begin(); entity != end; ++entity) { 
    if (!(*entity)->location.is_same((*entity)->destination)
        && (*entity)->hp > 0) {
        (*entity)->move(entities);
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
  SDL_Rect location     = {entity->location.x, entity->location.y};
  SDL_Surface *sprite   = this->spritesheet;

  /* 
   * So, we don't have to load a large amount of SDL_Surfaces, we use math 
   * based on an Entity's state/type/frame to see where on the sprite sheet 
   * we are getting the image.
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
  int health = this->player->hp;
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

void Game::draw(SDL_Surface *sprite, SDL_Rect *frame, 
                SDL_Surface *screen, SDL_Rect *location) {
  if(SDL_BlitSurface(sprite, frame, screen, location) < 0) {
    printf("Error! Drawing Entity: %s\n", SDL_GetError());
  }
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

