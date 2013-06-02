#include "Game.h"

Game::Game()
{
   t = time(NULL);
   running = true;

   //dungeon = Dungeon(5);
   render  = Render();
   player  = Player();
   monster = Monster();
}

Game::~Game()
{
   //
}

void Game::run()
{
   loops=0;

   /**
    * Update things every nth second in this loop, but still draw
    * and render animations without limits to the framerate. Interpolation
    * will handle the animations between point X to point Y and the
    * game can still update at a regular interval.
    */

   while(time(NULL) > t && loops < MAX_FRAMESKIP) {
      update();
      t += SKIP_TICKS;
      loops++;
   }

   while(SDL_PollEvent(&event))
      handleInput(event);

   interpolation();
   display();
}

void Game::update()
{
   Location monsterWorld = worldLoc(monster.location);
   Location playerWorld = worldLoc(player.location);
   if(monsterWorld.nearby(playerWorld, 1))
   {
      //printf("monster (%d, %d) is near player (%d, %d) \n", monsterWorld.x, monsterWorld.y, playerWorld.x, playerWorld.y);
      Location dir = (playerWorld - monsterWorld);
      monster.direction = Location(sgn(dir.x), sgn(dir.y));
      monster.state = monster.getState(monster.direction);
      monster.destination = player.location;
      //printf("monster destination (%d, %d) and direction (%d, %d)\n", monster.destination.x, monster.destination.y, monster.direction.x, monster.direction.y);
   }
   monster.move();
}

void Game::interpolation()
{
   monster.interpolate();
}

void Game::updatePlayer(int state, Location direction)
{
   player.move(direction);
   player.update(state);
   player.nextFrame();
}

void Game::display()
{
   drawDungeon();
   render.drawEntity(monster.type, monster.state, monster.location, monster.frame.value());
   render.drawEntity(player.type, player.state, player.location, player.frame.value());
   render.update();
}

void Game::quit()
{
   render.quit();
}

void Game::handleInput(SDL_Event event)
{
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

void Game::drawDungeon()
{
   for (int x = 0; x < MAP_WIDTH; x++) {
      for (int y = 0; y < MAP_HEIGHT; y++) {
         render.drawTile("floor", Location (x,y));
      }
   }
}

Location Game::worldLoc(Location screenLoc)
{
   return Location( ((screenLoc.x+(SPRITE_SIZE/2))/SPRITE_SIZE), ((screenLoc.y+(SPRITE_SIZE/2))/SPRITE_SIZE) );
}
