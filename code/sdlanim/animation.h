// animation.h

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


class animation {
	int NumberOfFrames;
	int CurrentFrame;
	SDL_Rect* rectangles;
public:
	void Init( int number_of_frames );
	SDL_Rect* GetFrame(void);
	void SetFrame( int frame_number, int x, int y, int w, int h);
	void NextFrame(void);
	void LastFrame(void);
};
