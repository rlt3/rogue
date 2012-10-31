#include "Entity.h"

Entity::Entity(const char* type)
{
   this->type = type;
   this->state = "IDLE";
   this->location = std::make_pair(150,150);
}

void Entity::draw()
{
   Render::animation()->draw(this->type, this->location, this->state);
}

void Entity::update(const char *state)
{
   this->state = state;
}
