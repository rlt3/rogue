#include "Entity.h"

Entity::Entity(int type)
{ 
   this->type = type;
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
   if (this->state != state) this->state = state;
}

void Entity::move()
{
   /**
    * If Entity is IDLE and doesn't have any objective,
    * then that Entity simply walks around randomly.
    *
    * If a player comes within 3 squares of the entity,
    * then the entity gains the destination of the player
    * (which updates as the player moves) and the entity
    * moves towards that player.
    *
    * If the entity has moved X distance and hasn't reached
    * its goal, then stop chasing the player.
    */
   
   if(destination.empty())
   {
      Location dir = randomDirection();
      this->destination = Location ( ( location + Location( dir.x*speed, dir.y*speed) ) );
      //this->state = getState(this->direction);
   }
}

void Entity::moveTowards(Location destination)
{
   //monster.direction = (playerWorld - monsterWorld);
   //this->destination = destination;
}

void Entity::interpolate()
{
   /**
    * Animate the entity on-screen. Entities move in straight 
    * lines (not diagonals). Every nTh movement toward the
    * destination, update the frame.
    *
    * For any given destination, move along the shortest axis
    * first, and then along the longest second. So, if a distance
    * between two points is (15, -16), an entity would move 
    * along the X first (because moving 16 units is still 16)
    * until that is 0. Then do it for y until that distance
    * between is (0, 0).
    */

   if(!this->destination.empty())
   {
      if(this->destination == this->location)
         this->destination = Location();

      this->direction = getDirection();
      this->state = getState(this->direction);

      Location difference = destination - location;

      if(location != destination)
         location.step( destination, direction, speed );

      int walking_direction = 0;

      if (direction.x == 0)
         walking_direction = difference.y;
      else if (direction.y == 0)
         walking_direction = difference.x;

      if( !(walking_direction % 10) && walking_direction != 0 )
         nextFrame();
   }
}

Location Entity::randomDirection()
{
   unsigned short int i = rand() % 5;
   //int coord[5][2] = { {0,1}, {-1,0}, {0,0}, {1,0}, {0,-1} };
   int coord[5][2] = { {1,1}, {-1,-1}, {0,0}, {1,-1}, {-1,1} };

   return Location(coord[i][0], coord[i][1]);
}

int Entity::getState(Location direction)
{
   /**
    * Using an ordered pair (x, y), determine which state
    * an entity should be in after getting the direction
    * of an entity
    */

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

Location Entity::getDirection()
{
   /**
    *  Get the distance between the destination and the 
    *  current location. If the distance between those
    *  two points is 0, then return 0.
    *
    *  Walk along the x axis first until at X destination.
    *  Then walk along y axis.
    */

   Location distance = this->destination - this->location;

   if( distance == Location(0, 0))
      return Location(0, 0);

   if(distance.x != 0)
      return Location(sgn(distance.x), 0);
   else
      return Location(0, sgn(distance.y));
}
