#include "Player.h"

Player::Player()
{
   Animation animation;
   this->sprite = animation.loadSprite("graphics/monster.png");
   this->animate.x = 256;
   this->animate.y = 0;
   this->animate.w = SPRITE_SIZE;
   this->animate.h = SPRITE_SIZE;
   this->location.x = 250;
   this->location.y = 250;
   this->state = "IDLE";
   this->count = 1;
}

void Player::draw()
{
   Render::draw(this->sprite, &this->animate, &this->location);
}

void Player::update(const char *state)
{
   this->count++;
   if(state == NULL && this->state == "IDLE") {
      if(this->count%2 == 0) {
         if(this->animate.x == 256)
            this->animate.x = 320; 
         else
            this->animate.x = 256; 
      }
      return;
   }

   this->state = state;

   if(this->state == "WALK_LEFT") {
      if(this->animate.x == 384)
         this->animate.x = 448; 
      else
         this->animate.x = 384; 

      this->location.x -= 10;
   }

   if(this->state == "WALK_RIGHT") {
      if(this->animate.x == 128)
         this->animate.x = 192; 
      else
         this->animate.x = 128; 

      this->location.x += 10;
   }

   if(this->state == "WALK_UP") {
      if(this->animate.x == 0)
         this->animate.x = 64; 
      else
         this->animate.x = 0; 

      this->location.y -= 10;
   }

   if(this->state == "WALK_DOWN") {
      if(this->animate.x == 256)
         this->animate.x = 320; 
      else
         this->animate.x = 256; 

      this->location.y += 10;
   }
}
