#include "pch.h"
#include "Application.h"
#include "Log.h"
#include "Entity/EntityManager.h"

#include <SFML/Graphics.hpp>

namespace Relic
{
    Application::Application(const WindowData& props) :
        m_properties(props)
    {
        Init();
    }

    Application::~Application()
    {
        Shutdown();
    }

    void Application::Init()
    {
        RL_CORE_TRACE("Application properties: {}, {}, {}", m_properties.title, m_properties.width, m_properties.height);
        m_window = std::make_shared<Window>(m_properties);

        InitEntityManager();
    }

    void Application::InitEntityManager() { m_entityManager = std::make_shared<EntityManager>(); }
    void Application::UpdateEntityManager() { m_entityManager->Update(); }
    void Application::RemoveInactiveEntities() { m_entityManager->RemoveInactiveEntities(m_entityManager->GetEntities()); }

    void Application::Shutdown()
    {
        m_window->Close();
    }

    void Application::Run()
    {        
        while (!m_window->ShouldClose())
        {
            UpdateEntityManager();
                
            m_window->HandleEvents();
            OnUpdate();

            //RemoveInactiveEntities();

            for (auto& entity : GetAllEntities())
                if (IsInWindow(entity))
                    entity->SetInRenderView(true);
                else
                    entity->SetInRenderView(false);

            m_window->Clear(0x0A0A0AFF);
            OnRender();
            m_window->Display();
        }
    }
    
    void Application::Constrain(std::shared_ptr<Entity> entity, uint32_t x, uint32_t y)
    {
        if (entity->transform->position.x < entity->GetRadius()) 
            entity->transform->position.x = entity->GetRadius();
        if (entity->transform->position.x + entity->GetRadius() > x)
            entity->transform->position.x = x - entity->GetRadius();

        if (entity->transform->position.y < entity->GetRadius())
            entity->transform->position.y = entity->GetRadius();
        if (entity->transform->position.y + entity->GetRadius()> y)
            entity->transform->position.y = y - entity->GetRadius();
    }

    bool Application::IsInWindow(std::shared_ptr<Entity> entity)
    {
        return (entity->GetX() + entity->GetRadius() >= 0.f && entity->GetX() - 5 < WINDOW_WIDTH && 
            entity->GetY() + entity->GetRadius() >= 0.f && entity->GetY() - 5 < WINDOW_HEIGHT);
    }

    void Application::Draw(const sf::Drawable& drawable) { m_window->Draw(drawable); }
    
    EntityVec& Application::GetAllEntities() { return m_entityManager->GetEntities(); }
    EntityVec& Application::GetAllEntities(const std::string& tag) { return m_entityManager->GetEntities(tag); }
    std::shared_ptr<Entity> Application::AddEntity(const std::string& tag) { return m_entityManager->AddEntity(tag); }
}
