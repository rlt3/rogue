#include <time.h>
#include "SDL/SDL.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE    32

int gameover;

/**
 * States should only last 2 turns.
 *
 * So, idleing should only last for two turns.
 *
 * States can be interrupted. These rules don't
 * apply for the player. Meaning attack animations
 * can last longer than 2 key frames.
 */

/* source and destination rectangles */
SDL_Rect rcSrc, rcSprite, MonsterAnim, MonsterRect;

class MonsterFrame
{
   public:
      int count;
      int currentFrame;
      SDL_Surface *sprite;
      SDL_Rect frame[], rcSprite;

      MonsterFrame(int frames, SDL_Surface *screen)   
      {
         this->count=frames;
         this->currentFrame=0;

         SDL_Surface *temp;

         printf("Made it past *temp\n");

         temp   = SDL_LoadBMP("monster.bmp");
         this->sprite = SDL_DisplayFormat(temp);
         SDL_FreeSurface(temp);

         printf("Made it past loading monster.bmp\n");

         int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
         SDL_SetColorKey(this->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
   
         printf("Set the color key\n");

         this->rcSprite.x = 180;
         this->rcSprite.y = 180;

         printf("Set location\n");

         this->SetFrame(0, 0, 0);
         this->SetFrame(1, 33, 0);
         this->SetFrame(2, 65, 0);
         this->SetFrame(3, 33, 0);
         this->SetFrame(4, 0, 0);

         printf("Set all the frames\n");
      }
      ~MonsterFrame()
      {
         SDL_FreeSurface(this->sprite);
      }
      void SetFrame( int frameNum, int x, int y)
      {
         this->frame[ frameNum ].x = x;
         this->frame[ frameNum ].y = y;
         this->frame[ frameNum ].w = SPRITE_SIZE;
         this->frame[ frameNum ].h = SPRITE_SIZE;
      }
      SDL_Rect *getFrame()
      {
         return &this->frame[this->currentFrame];
      }
};

void HandleEvent(SDL_Event event)
{
	switch (event.type) {
		/* close button clicked */
		case SDL_QUIT:
			gameover = 1;
			break;
			
		/* handle the keyboard */
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
				case SDLK_q:
					gameover = 1;
					break;
				case SDLK_a:
					if ( rcSrc.x == 192 )
						rcSrc.x = 224;
					else
						rcSrc.x = 192;
					rcSprite.x -= 5;
					break;
				case SDLK_d:
					if ( rcSrc.x == 64 )
						rcSrc.x = 96;
					else
						rcSrc.x = 64;
					rcSprite.x += 5;
					break;
				case SDLK_w:
					if ( rcSrc.x == 0 )
						rcSrc.x = 32;
					else
						rcSrc.x = 0;
					rcSprite.y -= 5;
					break;
				case SDLK_s:
					if ( rcSrc.x == 128 )
						rcSrc.x = 160;
					else
						rcSrc.x = 128;
					rcSprite.y += 5;
					break;
				case SDLK_1:
					if ( rcSrc.x == 256 )
						rcSrc.x = 288;
					else
						rcSrc.x = 256;
               break;
			}
			break;
	}
}

int main(int argc, char* argv[])
{
	SDL_Surface *screen, *temp, *sprite, *grass, *monster;
	SDL_Rect rcGrass;
	int colorkey;

	/* initialize SDL */
	SDL_Init(SDL_INIT_VIDEO);

	/* set the title bar */
	SDL_WM_SetCaption("SDL Animation", "SDL Animation");

	/* create window */
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	/* set keyboard repeat */
	SDL_EnableKeyRepeat(70, 70);

	/* load sprite */
	temp   = SDL_LoadBMP("animate.bmp");
	sprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	/* setup sprite colorkey and turn on RLE */
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

	/* load grass */
	temp  = SDL_LoadBMP("floor.bmp");
	grass = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	temp   = SDL_LoadBMP("monster.bmp");
	monster = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(monster, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
   
   MonsterRect.x = 180;
   MonsterRect.y = 180;

	MonsterAnim.x = 0;
	MonsterAnim.y = 0;
	MonsterAnim.w = SPRITE_SIZE;
	MonsterAnim.h = SPRITE_SIZE;

	/* set sprite position */
	rcSprite.x = 150;
	rcSprite.y = 150;

	/* set animation frame */
	rcSrc.x = 128;
	rcSrc.y = 0;
	rcSrc.w = SPRITE_SIZE;
	rcSrc.h = SPRITE_SIZE;

	gameover = 0;
   
   //MonsterFrame monster(5, screen);

   const int TICKS_PER_SECOND = 60;
   const int SKIP_TICKS = 60 / TICKS_PER_SECOND;
   const int MAX_FRAMESKIP = 10;

   long next_game_tick = time(NULL);
   int loops, count=0;
   int signage = 32;

   printf("Just before loop\n");

	/* message pump */
	while (!gameover)
	{
		SDL_Event event;

      loops=0;
      while(time(NULL) > next_game_tick && loops < MAX_FRAMESKIP)
      {
         if(rcSrc.x == 128)
            rcSrc.x = 160;
         else
            rcSrc.x = 128;

         if(count%3 == 0 && count!=0)
            signage = -signage;

         MonsterAnim.x += signage;

         next_game_tick += SKIP_TICKS;
         loops++;
         count++;
      }
		
		/* look for an event */
		if (SDL_PollEvent(&event)) {
			HandleEvent(event);
		}

		/* collide with edges of screen */
		if (rcSprite.x <= 0)
			rcSprite.x = 0;
		if (rcSprite.x >= SCREEN_WIDTH - SPRITE_SIZE) 
			rcSprite.x = SCREEN_WIDTH - SPRITE_SIZE;

		if (rcSprite.y <= 0)
			rcSprite.y = 0;
		if (rcSprite.y >= SCREEN_HEIGHT - SPRITE_SIZE) 
			rcSprite.y = SCREEN_HEIGHT - SPRITE_SIZE;

		/* draw the grass */
		for (int x = 0; x < SCREEN_WIDTH / SPRITE_SIZE; x++) {
			for (int y = 0; y < SCREEN_HEIGHT / SPRITE_SIZE; y++) {
				rcGrass.x = x * SPRITE_SIZE;
				rcGrass.y = y * SPRITE_SIZE;
				SDL_BlitSurface(grass, NULL, screen, &rcGrass);
			}
		}

		/* draw the sprite */
		SDL_BlitSurface(sprite, &rcSrc, screen, &rcSprite);
		SDL_BlitSurface(monster, &MonsterAnim, screen, &MonsterRect);
		//SDL_BlitSurface(monster.sprite, monster.getFrame(), screen, &monster.rcSprite);

		/* update the screen */
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}

	/* clean up */
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(grass);
	SDL_Quit();

	return 0;
}
