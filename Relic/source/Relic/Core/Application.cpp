#include "pch.h"
#include "Application.h"
#include "Log.h"
#include "Entity/EntityManager.h"

namespace Relic
{
    Application::Application(const ApplicationProperties& props) :
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
        RL_CORE_TRACE("{}, {}, {}", m_properties.name, m_properties.width, m_properties.height);
        m_windowHandle = new sf::RenderWindow(sf::VideoMode(m_properties.width, m_properties.height), m_properties.name);
        if (!m_windowHandle)
        {
            RL_CORE_ERROR("Failed to make window!");
            return;
        }
        m_windowHandle->setFramerateLimit(60);

        InitEntityManager();
    }

    void Application::InitEntityManager() { m_entityManager = std::make_shared<EntityManager>(); }
    void Application::UpdateEntityManager() { m_entityManager->Update(); }

    void Application::Shutdown()
    {
        m_windowHandle->close();
        delete m_windowHandle;
    }

    void Application::Run()
    {
        m_running = m_windowHandle->isOpen();
        
        while (m_running)
        {
            HandleEvents();

            UpdateEntityManager();
            OnUpdate();

            m_windowHandle->clear(sf::Color(0x0A0A0AFF));
            OnRender();
            m_windowHandle->display();
        }
    }

    void Application::HandleEvents()
    {
        sf::Event event;
        while (m_windowHandle->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_windowHandle->close();
                Close();
            }

            for (auto& e : GetAllEntities())
            {
                if (e->input)
                {
                    e->input->mousePosition.x = sf::Mouse::getPosition().x;
                    e->input->mousePosition.y = sf::Mouse::getPosition().y;

                    switch (event.type)
                    {
                        case sf::Event::KeyPressed:
                            e->input->keys[event.key.code] = true;
                            break;
                        
                        case sf::Event::KeyReleased:
                            e->input->keys[event.key.code] = false;
                            break;

                        case sf::Event::MouseButtonPressed:
                            e->input->mouse[event.mouseButton.button] = true;
                            e->input->clickedPosition = Vector2(event.mouseButton.x, event.mouseButton.y);
                            break;
                        
                        case sf::Event::MouseButtonReleased:
                            e->input->mouse[event.mouseButton.button] = false;
                            e->input->releasedPosition = Vector2(event.mouseButton.x, event.mouseButton.y);
                            break;
                    }
                }
            }
            OnEvent();
            for (auto& e : GetAllEntities())
            {
                if (e->input)
                {
                    e->input->mouse[sf::Mouse::Left] = false;
                    e->input->mouse[sf::Mouse::Right] = false;
                }
            }
        }
    }

    void Application::Constrain(const std::shared_ptr<Entity>&  entity, uint32_t x, uint32_t y)
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
    void Application::Close() { m_running = false; } 
    void Application::Draw(const sf::Drawable& drawable) { m_windowHandle->draw(drawable); }
    
    EntityVec& Application::GetAllEntities() { return m_entityManager->GetEntities(); }
    std::shared_ptr<Entity> Application::AddEntity(const std::string& tag) { return m_entityManager->AddEntity(tag); }
}
