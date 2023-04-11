#include "pch.h"
#include "Input.h"
#include <SFML/Window.hpp>

namespace Relic
{
    bool Input::IsKeyPressed(int16_t key) 
        { return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key); }

    bool Input::IsMouseButtonPressed(uint8_t button)
        { return sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }

    float Input::GetMouseX()
        { return sf::Mouse::getPosition().x; }

    float Input::GetMouseY()
        { return sf::Mouse::getPosition().y; }

    Vector2 Input::GetMousePosition()
        { return Vector2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y); }
}
