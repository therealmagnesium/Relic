#pragma once
#include "Components.h"
#include "Vector2.h"

namespace Relic
{
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

        float GetX(); 
        float GetY(); 
        Vector2& GetPosition(); 
        float GetXVel(); 
        float GetYVel();
        Vector2& GetVel(); 
        float GetAngle(); 

        float GetRadius();
        int GetPointCount(); 
        uint32_t GetFillColor(); 
        uint32_t GetBorderColor(); 

        float GetCollisionRadius();

        int GetLifetime(); 

        bool IsActive() const { return m_active; };
        bool IsEnabled() const { return m_enabled; }
        bool HasCullEnabled() const { return m_cullEnabled; } 
        size_t GetId() const { return m_id; };
        const std::string& GetTag() const { return m_tag; };

        inline void SetActive(bool active) { m_active = active; }
        inline void Enable() { m_enabled = true; }
        inline void Disable() { m_enabled = false; }
        inline void EnableCulling() { m_cullEnabled = true; }
        inline void DisableCulling() { m_cullEnabled = false; }

        inline void SetX(float x) { GetComponent<Transform>().position.x = x; } 
        inline void SetY(float y) { GetComponent<Transform>().position.y = y; } 
        inline void SetPosition(float x, float y) { GetComponent<Transform>().position.x = x; GetComponent<Transform>().position.y = y; } 
        inline void SetPosition(const Vector2& pos) { GetComponent<Transform>().position = pos; } 
        inline void SetXVel(float x) { GetComponent<Transform>().velocity.x = x; } 
        inline void SetYVel(float y) { GetComponent<Transform>().velocity.y = y; } 
        inline void SetVelocity(float x, float y) { GetComponent<Transform>().velocity.x = x; GetComponent<Transform>().velocity.y = y; } 
        inline void SetRotation(float angle) { GetComponent<Transform>().angle = angle; }

        void SetFillColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a); 

    private:
        Entity(const size_t id, const std::string& tag);

    private:
        friend class EntityManager;

        bool m_active = true;
        bool m_enabled = true;
        bool m_cullEnabled = true;
        size_t m_id = 0;
        std::string m_tag = "default";

        std::tuple<
        Transform,
        Shape,
        Collision,
        Lifetime,
        Text,
        SpriteRenderer,
        AudioSource> m_components;
    };
}
