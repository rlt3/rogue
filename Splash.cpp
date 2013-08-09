#include "Splash.hpp"

Splash::Splash(const char* splash) {
  this->spritesheet = Game::load_sprite(splash);
  this->on = true;
}

void Splash::splash_loop() {
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
    Game::draw(spritesheet, NULL, Game::screen, &location);
    SDL_Flip(Game::screen);
  }
}
