#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include "defs.h"
#include "Player.h"

class Game
{
   public:
      Game() {
         if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
            printf("Could not initialize SDL: %s\n", SDL_GetError());
            exit(1);
         }
         
         this->screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE);
         
         if (this->screen == NULL) {
            printf("Couldn't set screen mode to 640 x 480: %s\n", SDL_GetError());
            exit(1);
         }

         SDL_WM_SetCaption("Rogue", NULL);
         SDL_ShowCursor(SDL_DISABLE);

         this->assignTextures();
         this->generateDungeon();
         this->player = new Player();
      }
      void draw() {
         // clear the screen
         SDL_FillRect(this->screen,NULL,0x000000);

         // redraw the necessary stuff
         this->drawMap();
         this->drawPlayer();

         // apply
         SDL_Flip(this->screen);
      }
      void movePlayer(Location direction)
      {
         this->player->location.first += direction.first;
         this->player->location.second += direction.second;
      }
   protected:
      int Map[MAP_HEIGHT][MAP_WIDTH];
      Player *player;
      SDL_Surface *screen, *brickImage, *backgroundImage, *playerImage;

      void drawMap() {

         for (int y=0;y<MAP_HEIGHT;y++) {
            for (int x=0;x<MAP_WIDTH;x++) {
               if (this->Map[y][x] != 0) {
                  this->drawImage(this->brickImage, x * TILE_SIZE, y * TILE_SIZE);
               }
            }
         }
      }
      void drawPlayer()
      {
         this->drawImage(this->playerImage, this->player->location.first * TILE_SIZE, this->player->location.second * TILE_SIZE);
      }
      void generateDungeon() {
         int array[MAP_HEIGHT][MAP_WIDTH] = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
         };
         memcpy(this->Map,array,sizeof(array));
      }
   private:
      void assignTextures() {

         this->brickImage = this->loadImage("gfx/brick.png");
         if (brickImage == NULL) {
            exit(1);
         }

         this->backgroundImage = this->loadImage("gfx/background.png");
         if (backgroundImage == NULL) {
            exit(1);
         }

         this->playerImage = this->loadImage("gfx/player.png");
         if (playerImage == NULL) {
            exit(1);
         }
      }
      SDL_Surface *loadImage(const char *name) {
         /* Load the image using SDL Image */
         
         SDL_Surface *temp = IMG_Load(name);
         SDL_Surface *image;
         
         if (temp == NULL)
         {
            printf("Failed to load image %s\n", name);
            
            return NULL;
         }
         
         /* Make the background transparent */
         
         SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp->format, 0, 0, 0));
         
         /* Convert the image to the screen's native format */
         
         image = SDL_DisplayFormat(temp);
         
         SDL_FreeSurface(temp);
         
         if (image == NULL)
         {
            printf("Failed to convert image %s to native format\n", name);
            
            return NULL;
         }
         
         /* Return the processed image */
         
         return image;
      }
      void drawImage(SDL_Surface *image, int x, int y)
      {
         SDL_Rect dest;
         
         /* Set the blitting rectangle to the size of the src image */
         
         dest.x = x;
         dest.y = y;
         dest.w = image->w;
         dest.h = image->h;
         
         /* Blit the entire image onto the screen at coordinates x and y */
         
         SDL_BlitSurface(image, NULL, this->screen, &dest);
      }
};

