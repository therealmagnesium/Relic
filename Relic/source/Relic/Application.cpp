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
            RL_ERROR("Failed to make window!");
            return;
        }
        m_windowHandle->setFramerateLimit(60);
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
                        if (event.type == sf::Event::KeyPressed)
                        {
                            switch (event.key.code)
                            {
                                case sf::Keyboard::Left:
                                    e->input->keyLeft = true;
                                    break;
                                
                                case sf::Keyboard::Right:
                                    e->input->keyRight = true;
                                    break;
                                
                                case sf::Keyboard::Up:
                                    e->input->keyUp = true;
                                    break;
                        
                                case sf::Keyboard::Down:
                                    e->input->keyDown = true;
                                    break;
                        
                                case sf::Keyboard::Space:
                                    e->input->keyFire = true;
                                    break;
                            }
                        }
                        
                        if (event.type == sf::Event::KeyReleased)
                        {
                            switch (event.key.code)
                            {
                                case sf::Keyboard::Left:
                                    e->input->keyLeft = false;
                                    break;
                                
                                case sf::Keyboard::Right:
                                    e->input->keyRight = false;
                                    break;
                                
                                case sf::Keyboard::Up:
                                    e->input->keyUp = false;
                                    break;
                        
                                case sf::Keyboard::Down:
                                    e->input->keyDown = false;
                                    break;
                        
                                case sf::Keyboard::Space:
                                    e->input->keyFire = false;
                                    break;
                            }
                        }
                    }
                }
            }

            OnUpdate();

            m_windowHandle->clear(sf::Color(0x0A0A0AFF));
            OnRender();
            m_windowHandle->display();
        }
    }

    void Application::Close() { m_running = false; } 
    void Application::Draw(const sf::Drawable& drawable) { m_windowHandle->draw(drawable); }
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
    
    EntityVec& Application::GetAllEntities() { return m_entityManager->GetEntities(); }
    std::shared_ptr<Entity> Application::AddEntity(const std::string& tag) { return m_entityManager->AddEntity(tag); }


}
