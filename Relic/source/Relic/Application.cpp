#include "Application.h"
#include "Log.h"
#include "Entity/EntityManager.h"

#include <stdio.h>
#include <stdlib.h>

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
            }

            OnUpdate();

            m_windowHandle->clear(sf::Color(0x0a0a0aFF));
            OnRender();
            m_windowHandle->display();
        }
    }

    void Application::Close()
    {
        m_running = false;
    } 

    void Application::Draw(const sf::Drawable& drawable)
    {
        m_windowHandle->draw(drawable);
    }
}