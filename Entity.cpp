#include "Entity.hpp" 

Entity::Entity(uint8_t type, Location location) {
  this->type      = type;
  this->state     = IDLE;

  this->hp        = 10;
  this->strength  = (type == TYPE_PLAYER ? 5 : 1);
  this->speed     = 1;
  this->idle      = true;

  this->frame     = 0;
  this->do_frames = 0;
  this->framerate = 250;
  this->last_time = 0;

  this->location  = location;
  this->destination = this->location;

  this->offsets[0] = Location(0, 0);
  this->offsets[1] = Location(0, 0);
  this->offsets[2] = Location(0, 0);
  this->offsets[3] = Location(0, 0);
  this->offsets[4] = Location(0, -16);
  this->offsets[5] = Location(0, -16);
  this->offsets[6] = Location(-16, 0);
  this->offsets[7] = Location(-16,-16);
}

void Entity::update(unsigned current_time) {
  if ((current_time - last_time) < framerate) { return; }

  last_time = current_time;

  if (do_frames == 0) {
    framerate = 250;
    do_frames = -1;
    state -= state > 3 ? 4 : 0;
    idle = true;
  }

  if (do_frames > 0) {
    frame = ++frame % 3;
    do_frames -= 1;
  } else if (idle == false && do_frames == -1) {
    frame = frame ? 0 : 1;
  }

  idle = true;
}

void Entity::set_destination(uint32_t x, uint32_t y) {
  this->destination.x = this->location.x + x;
  this->destination.y = this->location.y + y;
}

void Entity::set_state(uint8_t state) {
  this->idle = false;

  /* If they are already attacking return, so they can spam space */
  if (this->state > 3 && state > 3) { return; }

  /* Set state to +4 so it corresponds to their walking direction */
  if (state == ATTACKING) {
    this->framerate = 50;
    this->state    += 4;
    this->do_frames = 3;
    this->frame     = 0;
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

  Location next_step(
      this->location.x + direction.x * this->speed,
      this->location.y + direction.y * this->speed);

  Entity_Iterator entity;
  Entity_Iterator end = entities.end();
  for (entity = entities.begin(); entity != end; ++entity) {
    if (next_step.collides_with(entity->location)
        && !entity->is_equal(*this)) {
      return;
    }
  }

  this->location = next_step;
  this->state = get_state(direction);
  this->idle = false;
}

void Entity::attack(Entity_List &entities) {
  /* Stop moving and attack */
  this->destination = this->location;
  
  Location direction = Entity::get_direction(state);

  Area attack_box;
  Area hit_box;

  /* Make the length of the attack face the direction of the entity */
  //attack_box.p1 = Location(
  //  (this->location.x + (direction.x != 0 ? direction.x * 48 : 32)),
  //  (this->location.y + (direction.y != 0 ? direction.y * 48 : 32))
  //);
  
  attack_box.p1 = Location(
    (this->location.x + (offsets[state].x)),
    (this->location.y + (offsets[state].y))
  );

  /* Set the end points of the rectangle the same way as above */
  //attack_box.p2 = Location(
  //  attack_box.p1.x + (direction.x == 0 ? 16 : 48),
  //  attack_box.p1.y + (direction.y == 0 ? 16 : 48)
  //);
  
  attack_box.p2 = Location(
    attack_box.p1.x + 32,
    attack_box.p1.y + 32
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

    hit_box = entity->location.get_world_area(16);

    if (attack_box.intersects(hit_box) && !entity->is_equal(*this)) {
      entity->hp -= this->strength;
      entity->location = Location::add(
                            entity->location,
                            Location::multiply(direction, Location(10,10)));
    }
  }
}

bool Entity::is_equal(Entity other) {
  return (this->location.is_same(other.location) &&
          this->destination.is_same(other.destination));
}

bool Entity::operator==(const Entity& rhs) {
  return (location.is_same(rhs.location) &&
          destination.is_same(rhs.destination));
}

Area Entity::get_world_area() {
  return this->location.get_world_area(64);
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

/* static */
bool Entity::sort_entities(const Entity * const & first, 
                    const Entity * const & second){
  if ((*first).location.x > (*second).location.x &&
      (*first).location.y > (*second).location.y) {
    return false;
  }
  return true;
}

