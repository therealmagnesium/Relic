#pragma once
#include "Components.h"
#include <tuple>

namespace Relic
{
    typedef std::tuple<
        Transform,
        Shape,
        Collision,
        Lifetime,
        Text
> ComponentTuple;

    class Entity
    {
    public:
        template<typename T>
        bool HasComponent()
            { return GetComponent<T>().has; }

        template<typename T>
        T& GetComponent()
            { return std::get<T>(m_components); }

        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args)
        {
            auto& component = GetComponent<T>();
            component = T(std::forward<TArgs>(args)...);
            component.has = true;
            return component;
        }

    public:
        void Move(float dx, float dy);
        void Destroy();

        inline float GetX() { return GetComponent<Transform>().position.x; }
        inline float GetY() { return GetComponent<Transform>().position.y; }
        inline Vector2 GetPosition() { return GetComponent<Transform>().position; }

        inline float GetXVel() { return GetComponent<Transform>().velocity.x; }
        inline float GetYVel() { return GetComponent<Transform>().velocity.y; }
        inline Vector2 GetVel() { return GetComponent<Transform>().velocity; }
        
        inline float GetAngle() { return GetComponent<Transform>().angle; }
        inline float GetRadius() { return GetComponent<Shape>().circle.getRadius(); }
        inline float GetCollisionRadius() { return GetComponent<Collision>().radius; }

        inline int GetLifetime() { return GetComponent<Lifetime>().lifetime; }

        inline bool IsActive() const { return m_active; };
        inline bool IsInRenderView() const { return m_inRenderView; }
        inline size_t GetId() const { return m_id; };
        inline const std::string& GetTag() const { return m_tag; };

        inline void SetInRenderView(bool inRenderView) { m_inRenderView = inRenderView; }

    private:
        Entity(const size_t id, const std::string& tag);

    private:
        friend class EntityManager;

        bool m_active = true;
        bool m_inRenderView = true;
        size_t m_id = 0;
        std::string m_tag = "default";

        ComponentTuple m_components;
    };
}
