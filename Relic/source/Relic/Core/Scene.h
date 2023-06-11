#pragma once
#include "LayerStack.h"
#include "Relic/Entity/EntityManager.h"
#include <cstdint>

namespace Relic
{
    class Application;
    class Entity;

    class Scene
    {
    public:
        friend class Entity;

        Scene(Application* app);
        virtual ~Scene();

        virtual void OnUpdate() = 0; 
        virtual void OnEnd();

        uint32_t GetCurrentFrame();
        EntityManager& GetEntityManager();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        void UpdateEntityManager();
        void CullEntities(uint32_t width, uint32_t height);
        void HandleComponents();

    protected:
        Application* m_app = nullptr;
        
        uint32_t m_currentFrame = 0;
        EntityManager m_entityManager;
        LayerStack m_layerStack;
    };
}
