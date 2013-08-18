#include "Game.hpp"

Game::Game() {
  load_window();
  //spritesheet = load_sprite("Graphics/spritesheet.png");
  spritesheet = load_sprite("Graphics/loz.png");

  level       = 1;
  on          = true;

  last_time   = SDL_GetTicks();
  update_rate = 500;

  create_dungeon();
}

Game::~Game() {
  //Entity_Iterator entity;
  //Entity_Iterator end = this->entities.end();

  //for (entity = this->entities.begin(); entity != end; ++entity) { 
  //  //deleteentity;
  //  this->entities.erase(entity);
  //}
  //
  //Item_Iterator item;
  //Item_Iterator item_end = this->items.end();
  //for (item = this->items.begin(); item != item_end; ++item) { 
  //  //delete (*item);
  //  this->items.erase(item);
  //}

  SDL_FreeSurface(this->spritesheet);
  SDL_FreeSurface(Screen::surface);
}

void Game::create_dungeon() {
  /* If we don't do this, the player multiplies */
  if (this->entities.size() > 0) {
    //Entity_Iterator entity;
    //Entity_Iterator end = this->entities.end();

    //for (entity = this->entities.begin(); entity != end; ++entity) { 
    //  deleteentity;
    //  this->entities.erase(entity);
    //}
    this->entities.clear();
  }

  int i;
  for (i = 1; i <= this->level; i++) {
    this->entities.insert(
        this->entities.begin(), 
        Entity(TYPE_MONSTER, Location(i*128, i*128))
    );
  }

  /* 
   * We have a pointer just to the player so that we can manipulate the 
   * list of entities in any fashion and not lose track of the most
   * important entity
   */

  //this->player = new Entity(TYPE_PLAYER, Location(144, 144));
  this->entities.insert(this->entities.begin(), Entity(TYPE_PLAYER, Location(144, 144)));
  this->player = this->entities.begin();
}

void Game::check_all_entities(unsigned now) {
  //Item_Iterator item;
  //Item_Iterator item_end = this->items.end();
  //for (item = this->items.begin(); item != item_end; ++item) { 
  //  Area item_area   = (*item)->get_world_area();
  //  Area entity_area = this->player->get_world_area();

  //  if (item_area.intersects(entity_area)) {
  //    (*item)->apply_effect(&*player);
  //    //delete (*item);
  //    this->items.remove(item);
  //  }
  //}
  
  Entity_Iterator entity;
  Entity_Iterator end = this->entities.end();

  for (entity = this->entities.begin(); entity != end; ++entity) { 

    /* The player updates itself based on input, no need to update */
    if (this->player ==entity) { continue; }

    /* Display the entire attack animation */
    if (entity->state > 3)      { continue; }

    if (entity->hp <= 0) {
      this->items.insert(this->items.begin(), new Heart(entity->location));
      //deleteentity;
      this->entities.remove(*entity);
    }

    if (entity->location.is_same(entity->destination)) {
      Location dest =entity->location.new_destination(entity->speed);
      if (IN_WORLD(dest.x, dest.y)) {
       entity->destination = dest;
      }
    }
      
    if ((now - last_time) < update_rate) { continue; }
    last_time = now;

    /* Sort entity locations so entities get drawn the right way: top to down */
    //entities.sort(Entity::sort_entities);

    /* If we're here, then we're attacing/moving towards the player, etc */
    if (entity->location.is_nearby(this->player->location)) {
      if (entity->location.is_adjacent(this->player->location)) {
       entity->set_state(ATTACKING);
       entity->attack(this->entities);
      } else {
       entity->destination = this->player->location;
      }
    }
  }
}

/*
 * Update the frames and state for every entity and item. Also check bounds of
 * these entities/items for collisions, etc. 
 *
 * The game updates every half second while the entities frame rates are set to
 * every quarter second.
 */
void Game::update(unsigned now) {
  Entity_Iterator entity;
  Entity_Iterator end = this->entities.end();

  for (entity = this->entities.begin(); entity != end; ++entity) { 
   entity->update(now);
  }

  check_all_entities(now);

  if (this->player->hp <= 0) {
    this->player->hp = 10;
    puts("You lose!");
    this->on = false;
  }

  /* If only the player exists, create next level */
  if (this->entities.size() == 1) {
    this->level++;
    this->create_dungeon();
  }
}

void Game::move_all_entities() {
  Entity_Iterator entity;
  Entity_Iterator end = this->entities.end();

  for (entity = this->entities.begin(); entity != end; ++entity) { 
    if (!entity->location.is_same(entity->destination)) {
     entity->move(entities);
    }
  }
}

void Game::draw_tile(uint8_t type, uint32_t x, uint32_t y) {
  //int size = (type > 128 ? 32 : 20);
  int size = 32;

  SDL_Rect location     = {x, y};
  SDL_Rect mask         = {0, type, size, size};
  SDL_Surface *sprite   = this->spritesheet;

  draw(sprite, &mask, Screen::surface, &location);
}

void Game::draw_entity(Entity *entity) {
  //SDL_Rect location     = {entity->location.x, entity->location.y};
  SDL_Rect location;

  if (entity->state > 3) {
    location = (SDL_Rect){
          entity->location.x + entity->offsets[entity->state].x, 
          entity->location.y + entity->offsets[entity->state].y
    };
  } else {
    location = (SDL_Rect){entity->location.x, entity->location.y};
  }

  SDL_Surface *sprite   = spritesheet;

  /* 
   * So, we don't have to load a large amount of SDL_Rects, we use math based 
   * on an Entity's state/type/frame to see where on the sprite sheet we are 
   * getting the image.
   */

  //SDL_Rect frame = { 
  //  (128 * entity->state) + (64 * entity->frame),
  //  entity->type, SPRITESIZE, SPRITESIZE 
  //};
  
  SDL_Rect frame;
      //(entity->type + 16) + (16 * entity->frame),

  if (entity->state > 3) {
    frame = (SDL_Rect){ 
      (32 * (entity->state % 4)),
      (entity->type + 16) + (32 * entity->frame),
      SPRITESIZE*2, SPRITESIZE*2
    };
  } else {
    frame = (SDL_Rect){ 
      (32 * entity->state) + (16 * entity->frame),
      entity->type, SPRITESIZE, SPRITESIZE
    };
  }
  draw(sprite, &frame, Screen::surface, &location); 
}

void Game::render() {
  /* Draw the Floor */
  for (int x = 0; x < SCREENX; x++) {
    for (int y = 0; y < SCREENY; y++) {
      draw_tile(FLOOR, x * TILESIZE, y * TILESIZE);
    }
  }

  /* Draw the health bar */
  int health = this->player->hp;
  for (int i = 1; i <= health; i++) {
    draw_tile(HEART, (i*24), (SCREENY - 24));
    //draw_tile(HEART, (i*20), (SCREENY - 20));
  }
  
  //Item_Iterator item;
  //Item_Iterator item_end = this->items.end();
  //for (item = this->items.begin(); item != item_end; ++item) { 
  //  draw_tile((*item)->type, (*item)->location.x, (*item)->location.y);
  //}

  /* Draw each entity */
  Entity_Iterator entity;
  Entity_Iterator entity_end = this->entities.end();
  for (entity = this->entities.begin(); entity != entity_end; ++entity) { 
    draw_entity(&*entity);
  }

  SDL_Flip(Screen::surface);
}
