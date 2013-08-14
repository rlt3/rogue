#ifndef ROGUE_LOADING_HPP
#define ROGUE_LOADING_HPP

#include <list>
#include "Screen.hpp"

class Loading;

typedef struct Button {
  SDL_Rect size;
  SDL_Rect normal;
  SDL_Rect hover;
  SDL_Rect (*get_frame)(Button *self, int x, int y);
  void (*on)(Button *self, Loading *loading, int x, int y);
} Button;

typedef std::list<Button>::iterator Button_Iterator;
typedef std::list<Button> Button_List;

class Loading : public Screen {
public:
  Loading();

  SDL_Rect location;
  SDL_Rect frame;

  bool on;
  bool game_off;
  bool display();

  Button_List buttons;

  static SDL_Rect get_frame(Button *self, int x, int y);
  static bool mouse_is_on(Button *self, int x, int y);

  static void on_start(Button *self, Loading *loading, int x, int y);
  static void on_quit(Button *self, Loading *loading, int x, int y);
  bool is_on_help(Button *self, int x, int y);
  bool is_on_quit(Button *self, int x, int y);

private:
  SDL_Surface  *spritesheet;
};

#endif
