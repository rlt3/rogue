#include "Loading.hpp"

/*
 * Don't do Loading() : Screen() as we don't want to initialize
 * the main window again
 */
Loading::Loading() {
  this->spritesheet = load_sprite("Graphics/loading.png");
  this->on = true;
}

void Loading::load() {
  SDL_Event event;

  while (this->on) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_MOUSEBUTTONDOWN:
        printf("@(%d, %d)\n", event.button.x, event.button.y);
        this->on = false;
        break;
      }
    }

    SDL_Rect location = {0, 0};
    draw(spritesheet, NULL, Screen::surface, &location);
    SDL_Flip(Screen::surface);
  }
}
