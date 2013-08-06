#include "Entity.hpp" 
Entity::Entity(uint8_t type, Location location) {
  this->type      = type;
  this->location  = location;

  this->hp        = 10;
  this->strength  = 1;
  this->speed     = 3;

  this->state     = IDLE;
  this->frame     = 0;
  this->do_frames = 0;
  this->idle      = true;

  this->destination = this->location;
}

void Entity::set_destination(uint32_t x, uint32_t y) {
  this->destination.x = this->location.x + x;
  this->destination.y = this->location.y + y;
}

void Entity::update(uint8_t state) {
  this->idle = false;

  if (state == ATTACKING && this->state < 4) {
    this->state += 4;
    this->do_frames = 2;
    return;
  }

  this->state = state;

  switch(state) {
  case WALK_UP:
    this->set_destination(0, (-10 * this->speed));
    break;
  case WALK_DOWN:
    this->set_destination(0, (10 * this->speed));
    break;
  case WALK_LEFT:
    this->set_destination((-10 * this->speed), 0);
    break;
  case WALK_RIGHT:
    this->set_destination((10 * this->speed), 0);
    break;
  default:
    break;
  }
}

void Entity::move(std::list<Entity*> entities) {
  Location diff = Location::subtract(this->destination, this->location);
  Location direction = diff.get_direction_to(); 

  Area next_step(Location(
      this->location.x + direction.x * this->speed,
      this->location.y + direction.y * this->speed),
      Location(0, 0)
  );
  
  std::list<Entity*>::const_iterator entity;
  std::list<Entity*>::const_iterator end = entities.end();
  for (entity = entities.begin(); entity != end; ++entity) {
    if (next_step.collides_with((*entity)->location)
        && (*entity) != this) {
      return;
    }
  }

  this->location = next_step.p1;
  this->state = get_state(direction);
  this->idle = false;
}

void Entity::attack(std::list<Entity *> &entities) {
  int state = (this->state > 3 ? this->state - 4 : this->state);
  Location direction = Entity::get_direction(state);

  Area attack_box;
  Area hit_box;

  attack_box.p1 = Location(
    (this->location.x + (direction.x != 0 ? direction.x * 48 : 32)),
    (this->location.y + (direction.y != 0 ? direction.y * 48 : 32))
  );

  attack_box.p2 = Location(
    attack_box.p1.x + (direction.x == 0 ? 16 : 48),
    attack_box.p1.y + (direction.y == 0 ? 16 : 48)
  );
  
  std::list<Entity*>::iterator entity;
  std::list<Entity*>::iterator end = entities.end();
  for (entity = entities.begin(); entity != end; ++entity) {
    hit_box.p1 = Location((*entity)->location.x + 16, 
                          (*entity)->location.y + 16);
    hit_box.p2 = Location(hit_box.p1.x + 48, hit_box.p1.y + 48);

    if (attack_box.intersects(hit_box) && (*entity) != this) {
      (*entity)->hp -= this->strength;
    }
  }
}

/* static */
int get_state(Location direction) {
  int state = IDLE;

  if (direction.x == 0 && direction.y == 1) {
    state = WALK_DOWN;
  } else if (direction.x == 0 && direction.y == -1) {
    state = WALK_UP;
  } else if (direction.x == 1 && direction.y == 0) {
    state = WALK_RIGHT;
  } else if (direction.x == -1 && direction.y == 0) {
    state = WALK_LEFT;
  }

  return state;
}

/* static */
Location get_direction(uint8_t state) {
  Location direction;

  if (state == WALK_DOWN) {
    direction = Location(0,1);
  } else if (state == WALK_UP) {
    direction = Location(0,-1);
  } else if (state == WALK_RIGHT) {
    direction = Location(1,0);
  } else if (state == WALK_LEFT) {
    direction = Location(-1,0);
  } else {
    direction = Location(0,0);
  }

  return direction;
}
