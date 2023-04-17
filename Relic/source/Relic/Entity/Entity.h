#pragma once
#include "Components.h"

namespace Relic
{
    class Entity
    {
    public:
        std::shared_ptr<Transform> transform;
        std::shared_ptr<Shape> shape;      
        std::shared_ptr<Collision> collision;

    public:
        void Move(float dx, float dy);
        void Destroy();

        inline float GetX() const { return transform->position.x; }
        inline float GetY() const { return transform->position.y; }
        inline Vector2& GetPosition() { return transform->position; }

        inline float GetXVel() const { return transform->velocity.x; }
        inline float GetYVel() const { return transform->velocity.y; }
        
        inline float GetAngle() const { return transform->angle; }
        inline float GetRadius() const { return shape->circle.getRadius(); }
        inline float GetCollisionRadius() const { return collision->radius; }

        inline bool IsActive() const { return m_active; };
        inline bool IsInRenderView() const { return m_inRenderView; }
        inline size_t GetId() const { return m_id; };
        inline const std::string& GetTag() const { return m_tag; };

        inline void SetActive(bool active) { m_active = active; }
        inline void SetInRenderView(bool inRenderView) { m_inRenderView = inRenderView; }

    private:
        Entity(const size_t id, const std::string& tag);

    private:
        friend class EntityManager;

        bool m_active = true;
        bool m_inRenderView = true;
        size_t m_id = 0;
        std::string m_tag = "default";
    };
}
