#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"

class Monster : public Entity
{
   public:
      Monster(Location location)
      {
         this->health = 10;
         this->level  = 1;
         this->floor  = 1;
         this->location  = location;
         this->previous = this->location;
      }
      void draw(void)
      {
         mvaddch(this->previous.second,this->previous.first,Map::getTile(this->previous));
         init_pair(2, COLOR_RED, COLOR_BLACK);
         attron(COLOR_PAIR(2)); 
         mvaddch(location.second,location.first,103);
         attroff(COLOR_PAIR(2));
      }
};
#endif
