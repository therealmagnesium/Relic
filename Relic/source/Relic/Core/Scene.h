#pragma once
#include "Relic/Entity/EntityManager.h"
#include <cstdint>

namespace Relic
{
    class Application;

    class Scene
    {
    public:
        Scene(Application* app);
        
        virtual void OnUpdate(float dt) = 0; 
        virtual void OnEnd();

        uint32_t GetCurrentFrame();
        EntityManager& GetEntityManager();
   
        void UpdateEntityManager();
        void CullEntities(uint32_t width, uint32_t height);
        void HandleComponents();

    protected:
        Application* m_app = nullptr;
        
        uint32_t m_currentFrame = 0; 
        EntityManager m_entityManager;
    };
}
