#include "Entity.hpp" 

Entity::Entity(uint8_t type, Location location) {
  this->type      = type;
  this->location  = location;

  this->hp        = 10;
  this->strength  = (type == TYPE_PLAYER ? 5 : 1);
  this->speed     = 1;

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

  /* If they are already attacking! */
  if (this->state > 3) {
    return;
  }

  if (state == ATTACKING) {
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

void Entity::move(Entity_List entities) {
  Location diff = Location::subtract(this->destination, this->location);
  Location direction = diff.get_direction_to(); 

  Area next_step(Location(
      this->location.x + direction.x * this->speed,
      this->location.y + direction.y * this->speed),
      Location(0, 0)
  );
  
  Entity_Iterator entity;
  Entity_Iterator end = entities.end();
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

void Entity::attack(Entity_List &entities) {
  Location direction = Entity::get_direction(state);

  Area attack_box;
  Area hit_box;

  /* Make the length of the attack face the direction of the entity */
  attack_box.p1 = Location(
    (this->location.x + (direction.x != 0 ? direction.x * 48 : 32)),
    (this->location.y + (direction.y != 0 ? direction.y * 48 : 32))
  );

  /* Set the end points of the rectangle the same as above */
  attack_box.p2 = Location(
    attack_box.p1.x + (direction.x == 0 ? 16 : 48),
    attack_box.p1.y + (direction.y == 0 ? 16 : 48)
  );
  
  Entity_Iterator entity;
  Entity_Iterator end = entities.end();
  for (entity = entities.begin(); entity != end; ++entity) {

    /*
     * Sprites are technically 64x64, but we reduce its hitbox by a 
     * fourth to ensure that if the attack_box and hit_box are
     * intersecting, the player won't think: 
     *          ``Man, that totally didn't hit me"
     */

    hit_box.p1 = Location(
        (*entity)->location.x + 16, 
        (*entity)->location.y + 16
    );

    hit_box.p2 = Location(hit_box.p1.x + 48, hit_box.p1.y + 48);

    if (attack_box.intersects(hit_box) && (*entity) != this) {
      (*entity)->hp -= this->strength;
    }
  }
}

Area Entity::get_world_area() {
  return this->location.get_world_area(64);
}

/* static */
bool Entity::sort_locations(Entity *first, Entity *second) {
  if (first->location.x > second->location.x &&
      first->location.y > second->location.y) {
    return false;
  }

  return true;
}

/* static */
int Entity::get_state(Location direction) {
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
Location Entity::get_direction(uint8_t state) {

  switch(state) {
  case WALK_DOWN:  case ATTACK_DOWN:
    return Location(0,1);

  case WALK_UP:    case ATTACK_UP:
    return Location(0,-1);

  case WALK_RIGHT: case ATTACK_RIGHT:
    return Location(1,0);

  case WALK_LEFT:  case ATTACK_LEFT:
    return Location(-1,0);

  default:
    return Location(0,0);
  }
}
