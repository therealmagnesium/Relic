#include "Application.h"
#include "pch.h"
#include "Input.h"
#include "Util.h"

#include <SFML/Graphics/RenderWindow.hpp>

static bool repeat = false;
namespace Relic
{
    bool Input::IsKeyPressed(int16_t key) 
        { return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key); }

    int Input::GetAxis(const std::string& axis)
    {
        int result = 0;

        if (axis == "horizontal")
            result = IsKeyPressed(Key::D) - IsKeyPressed(Key::A); 
        else if (axis == "vertical")
            result = IsKeyPressed(Key::S) - IsKeyPressed(Key::W);

        return result;
    } 

    bool Input::IsMouseButtonPressed(uint8_t button)
        { return sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }

    float Input::GetMouseX()
        { return sf::Mouse::getPosition().x; }

    float Input::GetMouseY()
        { return sf::Mouse::getPosition().y; }

    float Input::GetMouseX(const sf::RenderWindow& window)
    {
        float pixelX = sf::Mouse::getPosition(window).x;
        float worldCordsX = window.mapPixelToCoords(sf::Vector2i(pixelX, 0)).x;
        return worldCordsX;
    }

    float Input::GetMouseY(const sf::RenderWindow& window)
    { 
        float pixelY = sf::Mouse::getPosition(window).y;
        float worldCordsY = window.mapPixelToCoords(sf::Vector2i(0, pixelY)).y;
        return worldCordsY;
    }


    Vector2 Input::GetMousePosition()
        { return Vector2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y); }

    Vector2 Input::GetMousePosition(const sf::RenderWindow& window)
    { 
        Vector2 pixelPos = Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        auto worldCoords = window.mapPixelToCoords(sf::Vector2i(pixelPos.x, pixelPos.y));
        return Vector2(worldCoords.x, worldCoords.y);
    }
}
