#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Relic
{
    struct Drawable : public sf::Drawable
    {  
    };

    struct Font
    {
        sf::Font font;
        std::string path;
    };

    struct Texture
    {
        sf::Texture texture;
        std::string path; 
    }; 

    enum WindowStyle
    {
        None = sf::Style::None,
        Unresizable = sf::Style::Close | sf::Style::Titlebar,
        Default = sf::Style::Default,
        Fullscreen = sf::Style::Fullscreen       
    };

    struct RenderWindow
    {
        sf::Clock baseClock;
        sf::Clock deltaClock;
        sf::RenderWindow* handle = nullptr;
        RenderWindow() {}
    };
}
