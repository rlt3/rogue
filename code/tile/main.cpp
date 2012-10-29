#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#define WIDTH 640
#define HEIGHT 480
#define BPP 4
#define DEPTH 32

#define MAX_MAP_X 20
#define MAX_MAP_Y 15

#define TILE_SIZE 32

SDL_Surface *screen, *brickImage, *backgroundImage;

SDL_Surface *loadImage(const char *name)
{
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
	
	SDL_BlitSurface(image, NULL, screen, &dest);
}

void drawMap()
{
   int tile[MAX_MAP_Y][MAX_MAP_X] =
   {
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
	int x, y;
	
	drawImage(backgroundImage, 0, 0);

	for (y=0;y<MAX_MAP_Y;y++)
	{
		for (x=0;x<MAX_MAP_X;x++)
		{
			if (tile[y][x] != 0)
			{
				drawImage(brickImage, x * TILE_SIZE, y * TILE_SIZE);
			}
		}
	}
}

void draw()
{
   drawMap();
   SDL_Flip(screen);
   //SDL_Delay(1);
}

int main(int argc, char* argv[])
{
   SDL_Event event;

   int keypress = 0;
   int h=0; 

   if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;

   //if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_FULLSCREEN|SDL_HWSURFACE)))
   if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE)))
   {
     SDL_Quit();
     return 1;
   }

	SDL_ShowCursor(SDL_DISABLE);

	brickImage = loadImage("gfx/brick.png");
	if (brickImage == NULL)
	{
		exit(1);
	}

	backgroundImage = loadImage("gfx/background.png");
	if (backgroundImage == NULL)
	{
		exit(1);
	}

   while(!keypress) 
   {
      draw();
      while(SDL_PollEvent(&event)) 
      {      
           switch (event.type) 
           {
               case SDL_QUIT:
              keypress = 1;
              break;
               case SDL_KEYDOWN:
                    keypress = 1;
                    break;
           }
      }
   }

   SDL_Quit();

   return 0;
}
