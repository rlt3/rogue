#include <Entity/Entity.h>

Entity::Entity(int type) { 
   this->type = type;
   this->state = IDLE;
   this->speed = 40;

   this->location = Location(150,150);
   this->destination = this->location;

   this->frame.push(0);
   this->frame.push(1);
}

void Entity::update(int state) {
   if (this->state != state) this->state = state;
}

void Entity::idle() {
   if(destination == location) this->destination = randomDestinationFrom(this->location);
}

void Entity::moveTo(Entity &entity) {
   this->destination = entity.location;
}

void Entity::interpolate() {
   this->state = getState(this->direction);

   if(location.difference(destination))
      frame.next();
}

void Entity::move() {
   this->direction = getDirection();
   location.step(destination, direction, speed);
}

bool Entity::nearby(Entity &entity) {
   return location.world().nearby(entity.location.world(), 2);
}

Location Entity::getDirection() {
   Location distance = this->destination - this->location;

   if(distance.x != 0)
      return Location(sgn(distance.x), 0);
   else
      return Location(0, sgn(distance.y));
}

Location Entity::randomDestinationFrom(Location now) {
   unsigned short int i = rand() % 5;

   int direction[5][2] = { {0,1}, {-1,0}, {0,0}, {1,0}, {0,-1} };
   int magnitude[5][2] = { {35,30}, {30,-35}, {0,0}, {-30,35}, {35,30} };

   return Location ((now + Location(direction[i][0]*magnitude[i][0], direction[i][1]*magnitude[i][1])));
}

int Entity::getState(Location direction) {
   int state = IDLE;

   if(direction.x == 0 && direction.y == 1)
      state = WALK_DOWN;
   else if(direction.x == 0 && direction.y == -1)
      state = WALK_UP;
   else if(direction.x == 1 && direction.y == 0)
      state = WALK_RIGHT;
   else if(direction.x == -1 && direction.y == 0)
      state = WALK_LEFT;
   
   return state;
}
