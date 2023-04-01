#pragma once
#include "Components.h"

#include <string>
#include <memory>

namespace Relic
{
    class Entity
    {
    public:
        std::shared_ptr<Tranform> transform;
        std::shared_ptr<Shape> shape;      

    public:
        void Move(float dx, float dy);
        void Destroy();

        inline float GetX() const { return transform->position.x; }
        inline float GetY() const { return transform->position.y; }
        inline float GetXVel() const { return transform->velocity.x; }
        inline float GetYVel() const { return transform->velocity.y; }
        
        inline float GetRadius() const { return shape->circle.getRadius(); }

        inline bool IsActive() const { return m_active; };
        inline size_t GetId() const { return m_id; };
        inline const std::string& GetTag() const { return m_tag; };

    private:
        Entity(const size_t id, const std::string& tag);

    private:
        friend class EntityManager;

        bool m_active = true;
        size_t m_id = 0;
        std::string m_tag = "default";
    };
}