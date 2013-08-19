#include "Window.h"

static SDL_Surface *window;

void window_load() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Dearth", "Dearth");
  SDL_EnableKeyRepeat(70, 70);
  SDL_SetVideoMode(640, 512, 0, 0);

  //atexit(SDL_Quit);
  atexit(window_quit);

  window = SDL_GetVideoSurface();
}

void window_fill(uint32_t r, uint32_t g, uint32_t b) {
  SDL_FillRect(window, NULL, SDL_MapRGB(window->format, r, g, b));
}

void window_draw(Spritesheet sprite, Area *frame, Area *location) {
  if(SDL_BlitSurface(sprite, frame, window, location) < 0) {
    printf("Error! Drawing Entity: %s\n", SDL_GetError());
  }
}

void window_display() {
  SDL_Flip(window);
}

void window_free(Spritesheet *sheet) {
  SDL_FreeSurface(*sheet);
}

void window_quit() {
  SDL_FreeSurface(window);
  SDL_Quit();
}

Spritesheet load_sheet(const char* file) {
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
