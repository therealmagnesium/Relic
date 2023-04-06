#include "pch.h"
#include "Entity.h"

namespace Relic
{
    Entity::Entity(const size_t id, const std::string& tag)
    {

    }

    void Entity::Move(float dx, float dy)
    {
        transform->position.x += dx;
        transform->position.y += dy;
    }

    void Entity::Destroy()
    {
        
    }
}
