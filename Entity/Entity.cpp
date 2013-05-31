#include "Entity.h"

Entity::Entity(int type)
{ this->type = type;
   this->state = IDLE;
   this->speed = 40;

   this->location = Location(150,150);
   this->destination = Location();

   this->frame.push(0);
   this->frame.push(1);
}

void Entity::nextFrame()
{
   frame.next();
}

void Entity::update(int state)
{
   if (this->state != state)
      this->state = state;
}

void Entity::move()
{
   if(destination.empty())
   {
      this->direction = randomDirection();
      this->state = getState(this->direction);
      this->destination = Location ( ( location + Location( direction.x*speed, direction.y*speed) ) );
   }
}

void Entity::interpolate()
{
   if(!this->destination.empty())
   {
      if(this->destination == this->location)
         this->destination = Location();

      Location difference = destination - location;

      if(location != destination)
         location.nextLocation( destination, direction, speed );

      int walking_direction = 0;

      if (difference.x == 0)
         walking_direction = difference.y;
      else if (difference.y == 0)
         walking_direction = difference.x;

      if( !(walking_direction % 10) && walking_direction != 0 )
         nextFrame();
   }
}

Location Entity::randomDirection()
{
   unsigned short int i = rand() % 5;
   int coord[5][2] = { {0,1}, {-1,0}, {0,0}, {1,0}, {0,-1} };

   return Location(coord[i][0], coord[i][1]);
}

int Entity::getState(Location direction)
{
   if(direction.x == 0 && direction.y == 1)
      return WALK_DOWN;
   else if(direction.x == 0 && direction.y == -1)
      return WALK_UP;
   else if(direction.x == 1 && direction.y == 0)
      return WALK_RIGHT;
   else if(direction.x == -1 && direction.y == 0)
      return WALK_LEFT;
   
   return IDLE;
}
