#include "pch.h"
#include "Window.h"
#include "Application.h"
#include "Graphics.h"

#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>

namespace Relic
{
    Window::Window(const WindowData& props) :
        m_data(props)
    {
        Init(props);
    }

    Window::~Window()
    {
        m_windowHandle->handle->close();
        delete m_windowHandle->handle;
    }

    void Window::Init(const WindowData& props)
    {
        m_windowHandle = std::make_shared<RenderWindow>(); 
        m_windowHandle->handle = new sf::RenderWindow(sf::VideoMode(m_data.width, m_data.height), m_data.title, m_data.style);
        m_windowHandle->baseClock.restart();
        m_windowHandle->deltaClock.restart();

        if (!m_windowHandle->handle)
        {
            RL_CORE_ERROR("Failed to make window!");
            return;
        }
        m_windowHandle->handle->setFramerateLimit(Application::frameLimit);
        
        sf::FloatRect visibleArea(0, 0, m_data.width, m_data.height);
        m_windowHandle->handle->setView(sf::View(visibleArea));
    }

    void Window::HandleEvents()
    {
        sf::Event event;
        while (m_windowHandle->handle->pollEvent(event))
        {  
            ImGui::SFML::ProcessEvent(event);
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    m_data.shouldClose = true;
                    m_windowHandle->handle->close();
                    break;
                }
            }
        }
    }

    void Window::Clear(uint32_t color)
    { m_windowHandle->handle->clear(sf::Color(color)); }

    void Window::Display()
    { m_windowHandle->handle->display(); }

    void Window::Draw(const Drawable& drawable)
    { m_windowHandle->handle->draw(drawable); }

    void Window::Close()
    { m_windowHandle->handle->close(); }

    std::shared_ptr<RenderWindow> Window::GetHandle() const
        { return m_windowHandle; }
}
