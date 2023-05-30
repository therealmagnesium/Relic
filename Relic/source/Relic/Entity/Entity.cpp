#include "pch.h"
#include "Entity.h"
#include "Relic/Core/Assets.h"

namespace Relic
{
    Entity::Entity(const size_t id, const std::string& tag) :
        m_id(id), m_tag(tag), 
        m_components(Transform(), Shape(),
                    Collision(32.f), Lifetime(100), 
                    Text(), SpriteRenderer(),
                    AudioSource())
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

    float Entity::GetX()
    { return GetComponent<Transform>().position.x; }

    float Entity::GetY()
    { return GetComponent<Transform>().position.y; }

    Vector2& Entity::GetPosition()
    { return GetComponent<Transform>().position; }
 
    float Entity::GetXVel()
    { return GetComponent<Transform>().velocity.x; }

    float Entity::GetYVel()
    { return GetComponent<Transform>().velocity.y; }

    Vector2& Entity::GetVel()
    { return GetComponent<Transform>().velocity; }
 
    float Entity::GetAngle()
    { return GetComponent<Transform>().angle; }

    float Entity::GetRadius()
    { return GetComponent<Shape>().shape.GetRadius(); }

    int Entity::GetPointCount()
    { return GetComponent<Shape>().shape.GetPointCount(); }

    uint32_t Entity::GetFillColor()
    { return GetComponent<Shape>().shape.GetFillColor(); }

    uint32_t Entity::GetBorderColor()
    { return GetComponent<Shape>().shape.GetOutlineColor(); }

    float Entity::GetCollisionRadius()
    { return GetComponent<Collision>().radius; }

    int Entity::GetLifetime()
    { return GetComponent<Lifetime>().lifetime; }
}
