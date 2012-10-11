#include "Player.h"

Player::Player()
{
   Animation animation;
   this->sprite = animation.loadSprite("player.bmp");
   this->animate.x = 160;
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
         if(this->animate.x == 128)
            this->animate.x = 160; 
         else
            this->animate.x = 128; 
      }
      return;
   }

   this->state = state;

   if(this->state == "WALK_LEFT") {
      if(this->animate.x == 192)
         this->animate.x = 224; 
      else
         this->animate.x = 192; 

      this->location.x -= 5;
   }

   if(this->state == "WALK_RIGHT") {
      if(this->animate.x == 64)
         this->animate.x = 96; 
      else
         this->animate.x = 64; 

      this->location.x += 5;
   }

   if(this->state == "WALK_UP") {
      if(this->animate.x == 0)
         this->animate.x = 32; 
      else
         this->animate.x = 0; 

      this->location.y -= 5;
   }

   if(this->state == "WALK_DOWN") {
      if(this->animate.x == 128)
         this->animate.x = 160; 
      else
         this->animate.x = 128; 

      this->location.y += 5;
   }
}
