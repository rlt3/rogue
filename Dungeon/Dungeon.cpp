#include "Dungeon.h"

Dungeon::Dungeon(int difficulty)
{
   /* Difficulty is number of spawning monsters! */
   generate();
}

void Dungeon::update()
{
   /* Update entities existing within dungeon */
}

void Dungeon::generate()
{
   for (int x = 0; x < MAP_WIDTH; x++) {
      for (int y = 0; y < MAP_HEIGHT; y++) {
         map[y][x] = TILE_FLOOR;
      }
   }
}
