#include "pch.h"
#include "Entity.h"

namespace Relic
{
    Entity::Entity(const size_t id, const std::string& tag) :
        m_id(id), m_tag(tag)
    {
        RL_CORE_INFO("New entity created [{}, {}]", id, tag);
    }

    void Entity::Move(float dx, float dy)
    {
        transform->position.x += dx;
        transform->position.y += dy;
    }

    void Entity::Destroy()
    {
       RL_CORE_INFO("Entity destroyed [{}, {}]", m_id, m_tag); 
    }
}
