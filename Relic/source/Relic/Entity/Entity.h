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
        Text,
        SpriteRenderer> ComponentTuple;

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
        bool IsInRenderView(float viewWidth, float viewHeight, float cullMargin = 50.f);
        bool IsInRenderView(float xOffset, float yOffset, float viewWidth, float viewHeight, float cullMargin = 50.f);
        
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

        inline int GetPointCount() { return GetComponent<Shape>().circle.getPointCount(); }
        inline uint32_t GetFillColor() { return GetComponent<Shape>().circle.getFillColor().toInteger(); }
        inline uint32_t GetBorderColor() { return GetComponent<Shape>().circle.getOutlineColor().toInteger(); }

        inline int GetLifetime() { return GetComponent<Lifetime>().lifetime; }

        inline bool IsActive() const { return m_active; };
        inline bool IsEnabled() const { return m_enabled; }
        inline size_t GetId() const { return m_id; };
        inline const std::string& GetTag() const { return m_tag; };

        inline void SetActive(bool active) { m_active = active; }
        inline void Enable() { m_enabled = true; }
        inline void Disable() { m_enabled = false; }

    private:
        Entity(const size_t id, const std::string& tag);

    private:
        friend class EntityManager;

        bool m_active = true;
        bool m_enabled = true;
        size_t m_id = 0;
        std::string m_tag = "default";

        ComponentTuple m_components;
    };
}
