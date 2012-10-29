#include "Dungeon.h"

Dungeon::Dungeon()
{
   Animation animation;
   this->sprite = animation.loadSprite("floor.bmp");
}

void Dungeon::draw()
{
   for (int x = 0; x < SCREEN_WIDTH / SPRITE_SIZE; x++) {
      for (int y = 0; y < SCREEN_HEIGHT / SPRITE_SIZE; y++) {
         floorLocation.x = x * SPRITE_SIZE;
         floorLocation.y = y * SPRITE_SIZE;
         Render::draw(floor, NULL, &floorLocation);
      }
   }
}

void Dungeon::updateEntities()
{
}

void Dungeon::generate()
{
}
