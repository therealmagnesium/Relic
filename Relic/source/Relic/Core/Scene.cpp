#include "pch.h"
#include "Layer.h"
#include "Scene.h"
#include "Application.h"

namespace Relic
{
    Scene::Scene(Application* app) :
        m_app(app)
    {
    
    }

    Scene::~Scene()
    {

    }

    void Scene::OnEnd()
    {
        RL_CORE_INFO("Ending scene [{}]", m_app->GetCurrentScene());
    }

    void Scene::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Scene::PopLayer(Layer* layer)
    {
        m_layerStack.PopLayer(layer);
        layer->OnDetach();
    }

    uint32_t Scene::GetCurrentFrame() 
        { return m_currentFrame; }

    EntityManager& Scene::GetEntityManager() 
        { return m_entityManager; }

    void Scene::UpdateEntityManager()
        { m_entityManager.Update(); }
    
    void Scene::CullEntities(uint32_t width, uint32_t height)
        { m_entityManager.CullEntities(width, height); }

    void Scene::HandleComponents()
        { m_entityManager.HandleComponents(); }
}
