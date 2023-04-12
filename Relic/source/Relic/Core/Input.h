#pragma once
#include "KeyCodes.h"
#include "Window.h"
#include "Relic/Entity/Vector2.h"

namespace sf { class Window; }

namespace Relic
{
    class Input
    {
    public:
        static bool IsKeyPressed(int16_t key);

        static bool IsMouseButtonPressed(uint8_t button);
        static float GetMouseX();                               // Pixel mouse x coordinate
        static float GetMouseY();                               // Pixel mouse y coordinate
        static float GetMouseX(const sf::Window& window);       // World mouse x coordinate
        static float GetMouseY(const sf::Window& window);       // World mouse y coordinate
        
        static Vector2 GetMousePosition();
        static Vector2 GetMousePosition(const sf::Window& window);
    };
}
