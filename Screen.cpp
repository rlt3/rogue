#include "Screen.hpp"

SDL_Surface *Screen::surface;

Screen::Screen() {
  Screen::surface = Screen::load_window();
}

void Screen::draw(SDL_Surface *sprite, SDL_Rect *frame, 
                SDL_Surface *screen, SDL_Rect *location) {
  if(SDL_BlitSurface(sprite, frame, Screen::surface, location) < 0) {
    printf("Error! Drawing Entity: %s\n", SDL_GetError());
  }
}

/* static */
SDL_Surface * Screen::load_sprite(const char* file) {
  SDL_Surface *temp = IMG_Load(file);

  SDL_SetColorKey(temp, 
      (SDL_SRCCOLORKEY|SDL_RLEACCEL), 
      SDL_MapRGB(temp->format, 0, 0, 0));

  if (temp == NULL) {
    printf("Error: %s\n", IMG_GetError());
    exit(1);
  }

  SDL_Surface *sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  if (sprite == NULL) {
    printf("Failed to convert image to native format\n");
    exit(1);
  }

  return sprite;
}

SDL_Surface * Screen::load_window() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  SDL_SetVideoMode(640, 512, 0, 0);

  atexit(SDL_Quit);

  return SDL_GetVideoSurface();
}
