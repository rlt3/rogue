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
      
      /* Here is where we would determine direction 
       * also probably update state as well
       *
       * Direction would be determined by looking at
       * the absolute value of the distance between
       * locationNow and destination. Which ever axis
       * is smaller, we move along that axis (in
       * whatever direction) and the other axix is
       * zero'd out.
       */

      //printf("Location:    (%d, %d)\n", location.x, location.y);
      //printf("Desintation: (%d, %d)\n", destination.x, destination.y);
      //printf("Direction:   (%d, %d)\n\n", direction.x, direction.y);

      if(location != destination)
         location.step( destination, direction, speed );

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
   Location distance = this->destination - this->location;
   if( distance == Location(0, 0))
      return Location(0, 0);

   if(this->axis == -1)
   {
      if(this->axis == 0)
         if(distance.x == 0) this->axis = -1;
      else if(this->axis == 1)
         if(distance.y == 0) this->axis = -1;
   }
   else
   {
      if(abs(distance.x) < abs(distance.y) || distance.y == 0)
         this->axis = 0;
      else if(abs(distance.y) < abs(distance.x) || distance.x == 0)
         this->axis = 1;
   }

   if(this->axis == 0)
      printf(" (%d, %d) \n", sgn(distance.x), 0);
   if(this->axis == 1)
      printf(" (%d, %d) \n", 0, sgn(distance.x));

   if(this->axis == 0)
      return Location(sgn(distance.x), 0);
   if(this->axis == 1)
      return Location(0, sgn(distance.y));
}
