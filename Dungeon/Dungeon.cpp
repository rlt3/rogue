#include "Dungeon.h"

Dungeon::Dungeon(int level)
{
   this->level = level;
   this->generate();
}

void Dungeon::draw()
{
   for (int x = 0; x < SCREEN_WIDTH / SPRITE_SIZE; x++) {
      for (int y = 0; y < SCREEN_HEIGHT / SPRITE_SIZE; y++) {
         Location location = std::make_pair(x*SPRITE_SIZE,y*SPRITE_SIZE);
         Render::animation()->draw("floor", location, NULL);
      }
   }
}

void Dungeon::update()
{
   // update the monsters
}

void Dungeon::generate()
{
   /**
    * There would be an algorithm determining the
    * number of monsters based on the floor level
    *
    * There would also be an algorithm drawing 
    * the actual dungeon
    */
   this->monster = new Entity("monster");
}
