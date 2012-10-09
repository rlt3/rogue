#ifndef ENTITY_H
#define ENTITY_H
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
void Entity::attack(Entity* enemy)
{
   enemy->damage(this->getDamage());
}

void Entity::damage(int damage)
{
   this->health = health-damage;
}
int Entity::getDamage()
{
   return this->level*3;
}
#endif
