#include "pch.h"
#include "Entity.h"
#include "Relic/Core/Assets.h"

namespace Relic
{
    Entity::Entity(const size_t id, const std::string& tag) :
        m_id(id), m_tag(tag), 
        m_components(Transform(Vector2(), Vector2(), 0.f), Shape(32.f, 8, 0xFFFFFFFF, 0xFFFFFFFF, 4),
                    Collision(32.f), Lifetime(100), Text())
    {
        RL_CORE_INFO("New entity created [{}, {}]", id, tag);
    }

    void Entity::Move(float dx, float dy)
    {
        GetComponent<Transform>().position.x += dx;
        GetComponent<Transform>().position.y += dy;
    }

    void Entity::Destroy()
    {
       RL_CORE_WARN("Entity destroyed [{}, {}]", m_id, m_tag); 
       m_active = false;
    }
}
