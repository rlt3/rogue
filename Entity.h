#ifndef ENTITY_H
#define ENTITY_H
#include "Map.h"
#include "typedef.h"

class Entity
{
   public:
      int health;
      int level;
      int floor;
      Location location;
      void move(Location destination);
      void attack(Entity* enemy);
      void damage(int damage);
      void draw(void);
   protected:
      Location previous;
      bool canMove(Location destination);
      int getDamage();
};

void Entity::move(Location destination)
{
   if(this->canMove(destination))
   {
      this->previous = this->location;
      this->location.first  = this->location.first+destination.first;
      this->location.second = this->location.second+destination.second;
   }
}
void Entity::attack(Entity* enemy)
{
   enemy->damage(this->getDamage());
}
void Entity::damage(int damage)
{
   this->health = health-damage;
}
void Entity::draw(void)
{
   mvaddch(this->previous.second,this->previous.first,Map::getTile(this->previous));
   init_pair(1, COLOR_GREEN, COLOR_BLACK);
   attron(COLOR_PAIR(1)); 
   mvaddch(location.second,location.first,64);
   attroff(COLOR_PAIR(1));
}
bool Entity::canMove(Location destination)
{
   int x = this->location.first+destination.first;
   int y = this->location.second+destination.second;

   if(x < 1 || y < 1  || x > MAP_WIDTH || y > MAP_HEIGHT)
      return false;

   int nTileValue = Map::array[y-OFFSET][x-OFFSET];

   if(nTileValue == TILE_FLOOR || nTileValue == TILE_GRASS || nTileValue == TILE_OPENDOOR)
      return true;

   //if(nTileValue == DRAGON_CHAR)
   //{
   //   this->attack(x-OFFSET, y-OFFSET);
   //   return false;
   //}

   return false;
}
int Entity::getDamage()
{
   return this->level*3;
}
#endif
