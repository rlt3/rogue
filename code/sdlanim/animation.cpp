#include "animation.h"	
#include <string>	

// ================== Declare global variables =======================
// ===================================================================
SDL_Surface* background_image = NULL;	// placed here so that any function can access them

// this contains the FULL set of frames for our sprite even though we only display one of them
SDL_Surface* Sprite = NULL;
// our poiter to the screen surface
SDL_Surface* screen = NULL;

// screen display rectangle
SDL_Rect background_position;
SDL_Rect Sprite_position;

// set screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

animation Sprite_animation;

// ================== Functions ======================================
// ===================================================================

void animation::Init( int number_of_frames )
{
	// create a new array of SDL_Rects to tell where on the Sprite surface(s)
	// the individual frames are
	rectangles = new SDL_Rect[ number_of_frames ];

	// record how many frames we have in total
	NumberOfFrames = number_of_frames - 1;  // -1 because arrays start counting from 0 not 1
	
	// set the current frame
	CurrentFrame = 0;
}

SDL_Rect* animation::GetFrame(void)
{
	// return a pointer to the current frame
	return &rectangles[ CurrentFrame ];
}

void animation::SetFrame( int frame_number, int x, int y, int w, int h)
{
	// setup the location and dimensions of a frame
	rectangles[ frame_number ].x = x;
	rectangles[ frame_number ].y = y;
	rectangles[ frame_number ].w = w;
	rectangles[ frame_number ].h = h;
}

void animation::NextFrame(void)
{
	CurrentFrame++; // advance one frame
	if(CurrentFrame > NumberOfFrames) CurrentFrame = 0; // if we go over the top set to zero
}

void animation::LastFrame(void)
{
	CurrentFrame--; // step back one frame
	if(CurrentFrame < 0) CurrentFrame = NumberOfFrames; // if we underrun the list set to top
}

SDL_Surface *Load_image( std::string filename )
{
	SDL_Surface* loaded_image = NULL;
	SDL_Surface* compatible_image = NULL;

	if(filename.c_str() == NULL) { // check to see if a filename was provided
		// if not exit the function
		return NULL;
	}

	// load the image using our new IMG_Load function from sdl-Image1.2
	loaded_image = IMG_Load( filename.c_str() );

	if( loaded_image == NULL ){ // check to see if it loaded properly
		// if not exit the function
		return NULL;
	}	

	// the image loaded fine so we can now convert it to the current display depth
	compatible_image = SDL_DisplayFormat( loaded_image );

	if( compatible_image != NULL ) {
		// specify a colour that will be used to signify 'transparent' pixels
		Uint32 colorkey = SDL_MapRGB( compatible_image->format, 0, 0, 0); // choose black
		// now tell SDL to remeber our choice
		SDL_SetColorKey( compatible_image, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
		// SDL_RLEACCEL is run lenght encoding acceleration to speed up the colorkeying
		// SDL_SRCCOLORKEY tells SDL that this color key applies to the source image
	}

	// Destroy the old copy
	SDL_FreeSurface( loaded_image );

	// return a pointer to the newly created display compatible image
	return compatible_image;
}

bool Init()
{
	background_position.x = 0; 			// initialize position rectangle
	background_position.y = 0;

	Sprite_position.x = 350; // we still need this to indicate where to put the sprite
	Sprite_position.y = 250; // onto the screen

	// create a new animation and setup its frames
	
	Sprite_animation.Init(7); // just seven frames please
	Sprite_animation.SetFrame(0, 0, 70, 40, 62);
	Sprite_animation.SetFrame(1, 137, 70, 40, 62);
	Sprite_animation.SetFrame(2, 267, 70, 40, 62);
	Sprite_animation.SetFrame(3, 397, 70, 40, 62);
	Sprite_animation.SetFrame(4, 0, 204, 40, 62);
	Sprite_animation.SetFrame(5, 137, 204, 40, 62);
	Sprite_animation.SetFrame(6, 267, 204, 40, 62);

	//Initialize SDL video subsystems
    	if( SDL_Init( SDL_INIT_VIDEO ) == -1 )    {
		return false;    
	}
	// create screen 800x600x32bpp in software rendering mode.
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE ); 
	
	background_image = Load_image("background.jpg"); // load our background Surface
	if( background_image == NULL ){ 
		printf("unable to load Background Image\n");
		return false;
	}

	Sprite = Load_image("sprite.bmp"); // load our sprite images on a surface
	if( Sprite == NULL ){
		printf("unable to load Sprite Images\n");
		return false;
	}
	return true;
	
}

void shutdown(void)
{
	// Destroy image surface
	SDL_FreeSurface( background_image );	
	SDL_FreeSurface( Sprite );
		
	SDL_Quit();
	
}	

void ChangeFrames(void)
{
	// advance one frame
	Sprite_animation.NextFrame();
}

void RenderTheScene(void)
{
	// put the image on the screen surface
	SDL_BlitSurface( background_image, NULL, screen, &background_position ); // put the background on
	// now place the sprite over the top
	SDL_BlitSurface( Sprite, Sprite_animation.GetFrame(), screen, &Sprite_position ); 	
	// now change the position back to 0,0 for the background
	
	// waite 0.5 seconds
	SDL_Delay( 500 );  // I put this here so you will be able to see the animation change!
			    // without it all you would see is a blur!

	SDL_Flip( screen ); // send the screen surface to be displayed
}

// ====================== main ===========================================
// =======================================================================

int main( int argc, char* argv[] )
{
	bool done = false;
	SDL_Event event;	
	
	if(Init() == false) {
		// use SDL_Error() to tell us what went wrong
		printf("Unable to Intialise Program error is: %s\n\n", SDL_GetError() ); 
	}
	// make sure SDL shuts down in the event of a crash
	atexit( shutdown );

	while(done != true)	{		// new input processing loop based on the input 
		while(SDL_PollEvent(&event)){		// HOWTO by seethru
			switch(event.type)	{
				case SDL_QUIT:	// did anyone click the close button on my window?
					done = true;	// oh! how rude!
			}
		}
		ChangeFrames();			// change to next frame or reset to the begining
		RenderTheScene();		// moved to a function of its own
	}

	return 0; // program completed successfully
}
