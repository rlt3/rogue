#include "Dungeon.h"
#include <SDL_image/SDL_image.h>
#include "defs.h"

Dungeon::Dungeon()
{
   //for (int y=OFFSET;y<=MAP_HEIGHT;y++)
   //   for (int x=OFFSET;x<=MAP_WIDTH;x++)
   //      this->Monsters[y-OFFSET][x-OFFSET] = NULL;
   
   this->floor=0;
   this->generateMap();
   this->generateEntities();
}
void Dungeon::draw(SDL_Surface *screen)
{
   SDL_FillRect(this->screen,NULL,0x000000);

   // redraw the necessary stuff
   this->drawMap(screen);
   this->drawEntities(screen);

   // apply
   SDL_Flip(screen);
}
void Dungeon::drawMap(SDL_Surface *screen)
{
   for (int y=0;y<MAP_HEIGHT;y++) {
      for (int x=0;x<MAP_WIDTH;x++) {
         if (this->Map[y][x] != 0) {
            this->drawImage(this->brickImage, x * TILE_SIZE, y * TILE_SIZE);
         }
      }
   }
}
