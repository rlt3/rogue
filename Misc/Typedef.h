#ifndef TYPEDEF_H
#define TYPEDEF_H
#include <SDL/SDL.h>
#include <utility>
#include <time.h>
#include "Queue.h"

//typedef std::pair<int, int> Location;
typedef Queue<SDL_Rect> animationQueue;
typedef std::pair<int, int> Frame;

#define WALK_UP    0
#define WALK_RIGHT 1
#define WALK_DOWN  2
#define WALK_LEFT  3
#define IDLE       2

#define PLAYER     0
#define MONSTER    64

#endif
