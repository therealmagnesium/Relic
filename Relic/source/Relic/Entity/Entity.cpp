#include "pch.h"
#include "Entity.h"
#include "Relic/Core/Assets.h"

namespace Relic
{
    Entity::Entity(const size_t id, const std::string& tag) :
        m_id(id), m_tag(tag), 
        m_components(Transform(Vector2(), Vector2(), 0.f), Shape(32.f, 8, 0xFFFFFFFF, 0xFFFFFFFF, 4),
                    Collision(32.f), Lifetime(100), Text(), SpriteRenderer())
    {
        RL_CORE_INFO("New entity created [{}, {}]", id, tag);
    }

    bool Entity::IsInRenderView(float viewWidth, float viewHeight, float cullMargin)
    {
        if (HasComponent<Shape>())
            return (GetX() - GetRadius() <= viewWidth + cullMargin && GetX() + GetRadius() >= 0.f - cullMargin &&
                    GetY() - GetRadius() <= viewHeight + cullMargin && GetY() + GetRadius() >= 0.f - cullMargin);
        else
            return (GetX() < viewWidth + cullMargin && GetX() > 0.f - cullMargin &&
                    GetY() < viewHeight + cullMargin && GetY() > 0.f - cullMargin);
    }

    bool Entity::IsInRenderView(float xOffset, float yOffset, float viewWidth, float viewHeight, float cullMargin)
    {
        if (HasComponent<Shape>())
            return (GetX() - GetRadius() <= xOffset + viewWidth + cullMargin && GetX() + GetRadius() >= xOffset - cullMargin &&
                    GetY() - GetRadius() <= yOffset + viewHeight + cullMargin && GetY() + GetRadius() >= yOffset - cullMargin);
        else 
            return (GetX() < xOffset + viewWidth + cullMargin && GetX() > xOffset - cullMargin &&
                    GetY() < yOffset + viewHeight + cullMargin && GetY() > yOffset - cullMargin);
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
