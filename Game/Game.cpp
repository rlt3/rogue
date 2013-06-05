#include "Game.h"

Game::Game() {
   t = time(NULL);
   running = true;

   //dungeon = Dungeon(5);
   render  = Render();
   player  = Player();
   monster = Monster();
}

Game::~Game() {
   //
}

void Game::run() {
   loops=0;

   while(time(NULL) > t && loops < MAX_FRAMESKIP) {
      update();
      t += SKIP_TICKS;
      loops++;
   }

   while(SDL_PollEvent(&event))
      handleInput(event);

   move();
   interpolation();
   display();
}

void Game::update() {
   if(monster.nearby(player))
      monster.moveTo(player);
   else
      monster.idle();
}

void Game::move() {
   monster.move();
}

void Game::interpolation() {
   monster.interpolate();
}

void Game::updatePlayer(int state, Location direction) {
   player.move(direction);
   player.update(state);
   player.frame.next();
}

void Game::display() {
   drawDungeon();
   render.drawEntity(monster.type, monster.state, monster.location, monster.frame.value());
   render.drawEntity(player.type, player.state, player.location, player.frame.value());
   render.update();
}

int Game::quit() {
   return render.quit();
}

void Game::handleInput(SDL_Event event) {
   switch (event.type) {
      case SDL_KEYDOWN:
         switch(event.key.keysym.sym) {
            case SDLK_ESCAPE: case SDL_QUIT:
              running=false;
              break;
            case SDLK_w: case SDLK_UP: case SDLK_k:
               updatePlayer(WALK_UP, Location (0,-10));
               break;
            case SDLK_a: case SDLK_LEFT: case SDLK_h:
               updatePlayer(WALK_LEFT, Location (-10,0));
               break;
            case SDLK_s: case SDLK_DOWN: case SDLK_j:
               updatePlayer(WALK_DOWN, Location (0,10));
               break;
            case SDLK_d: case SDLK_RIGHT: case SDLK_l:
               updatePlayer(WALK_RIGHT, Location (10,0));
               break;
            default:
               break;
         }
         break;
      //case SDL_KEYUP:
      //   game.updatePlayer(IDLE, Location (0,0));
      //   break;
   }
}

void Game::drawDungeon() {
   for (int x = 0; x < MAP_WIDTH; x++) {
      for (int y = 0; y < MAP_HEIGHT; y++) {
         render.drawTile("floor", Location (x,y));
      }
   }
}
