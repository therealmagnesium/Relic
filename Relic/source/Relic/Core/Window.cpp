#include "pch.h"
#include "Window.h"

#include <SFML/Graphics.hpp>

namespace Relic
{
    Window::Window(const WindowData& props) :
        m_data(props)
    {
        Init(props);
    }

    Window::~Window()
    {
        m_windowHandle->close();
        delete m_windowHandle;
    }

    void Window::Init(const WindowData& props)
    {
        m_windowHandle = new sf::RenderWindow(sf::VideoMode(m_data.width, m_data.height), m_data.title, m_data.style);
        if (!m_windowHandle)
        {
            RL_CORE_ERROR("Failed to make window!");
            return;
        }
        m_windowHandle->setFramerateLimit(60);
        
        sf::FloatRect visibleArea(0, 0, m_data.width, m_data.height);
        m_windowHandle->setView(sf::View(visibleArea));
    }

    void Window::HandleEvents()
    {
        sf::Event event;
        while (m_windowHandle->pollEvent(event))
        {   
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    m_data.shouldClose = true;
                    m_windowHandle->close();
                    break;
                }
            }
        }
    }

    void Window::Clear(uint32_t color)
        { m_windowHandle->clear(sf::Color(color)); }

    void Window::Display()
        { m_windowHandle->display(); }

    void Window::Draw(const sf::Drawable& drawable)
        { m_windowHandle->draw(drawable); }

    void Window::Close()
        { m_windowHandle->close(); }
}