#include "Entity.h"

std::map<const char *state, animationQueue> Entity::keyframes;

Entity::Entity(const char* type)
{
   this->type = type;
   this->state = "IDLE";
   this->location = std::make_pair(150,150);
}

void Entity::draw()
{
   //Render::draw(this->sprite, &this->animate, &this->location);
}

void Entity::update(const char *state)
{
   this->state = state;
}
