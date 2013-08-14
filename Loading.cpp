#include "Loading.hpp"

/*
 * Don't do Loading() : Screen() as we don't want to initialize
 * the main window again
 */
Loading::Loading() {
  spritesheet = load_sprite("Graphics/loading.png");
  on          = true;
  game_off    = true;
  location    = (SDL_Rect){0, 0};
  frame       = (SDL_Rect){0, 0, 640, 512};

  Button start = {
    (SDL_Rect){210, 210, 220, 60},
    (SDL_Rect){0, 572, 220, 60},
    (SDL_Rect){0, 512, 220, 60},
    &Loading::get_frame,
    &Loading::on_start
  };

  Button quit = {
    (SDL_Rect){210, 300, 220, 60},
    (SDL_Rect){220, 572, 220, 60},
    (SDL_Rect){220, 512, 220, 60},
    &Loading::get_frame,
    &Loading::on_quit
  };

  buttons.insert(buttons.begin(), start);
  buttons.insert(buttons.begin(), quit);
}

bool Loading::mouse_is_on(Button *self, int x, int y) {
  return (x >= self->size.x && 
          y >= self->size.y &&
          x <= (self->size.x + self->size.w) && 
          y <= (self->size.y + self->size.h));
}

SDL_Rect Loading::get_frame(Button *self, int x, int y) {
  if (Loading::mouse_is_on(self, x, y)) {
    return self->hover;
  }
  return self->normal;
}

void Loading::on_start(Button *self, Loading *loading, int x, int y) {
  if (Loading::mouse_is_on(self, x, y)) {
    loading->on = false;
  }
}

void Loading::on_quit(Button *self, Loading *loading, int x, int y) {
  if (Loading::mouse_is_on(self, x, y)) {
    loading->on = false;
    loading->game_off = false;
  }
}

bool Loading::display() {
  SDL_Event event;
  int mouse_x, mouse_y;

  while (this->on) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_MOUSEMOTION:
        mouse_x = event.button.x;
        mouse_y = event.button.y;
        break;

      case SDL_MOUSEBUTTONDOWN:
        Button_Iterator button;
        Button_Iterator end = buttons.end();
        for (button = buttons.begin(); button != end; ++button) { 
          button->on(&*button, this, mouse_x, mouse_y);
        }
        break;
      }
    }

    SDL_FillRect(Screen::surface, NULL, 0x000000);
    draw(spritesheet, &this->frame, Screen::surface, &this->location);

    Button_Iterator button;
    Button_Iterator end = buttons.end();
    for (button = buttons.begin(); button != end; ++button) { 
      SDL_Rect frame = button->get_frame(&*button, mouse_x, mouse_y);
      draw(spritesheet, &frame, Screen::surface, &button->size);
    }

    SDL_Flip(Screen::surface);
  }

  return game_off;
}
