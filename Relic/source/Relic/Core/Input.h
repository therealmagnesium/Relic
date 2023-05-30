#pragma once
#include "KeyCodes.h"
#include "Window.h"
#include "Relic/Entity/Vector2.h"

namespace Relic
{
    class Input
    {
    public:
        static bool IsKeyPressed(int16_t key);
        static int GetAxis(const std::string& axis);

        static bool IsMouseButtonPressed(uint8_t button);
        static float GetMouseX();                               // Pixel mouse x coordinate
        static float GetMouseY();                               // Pixel mouse y coordinate
        static float GetMouseX(const RenderWindow& window);       // World mouse x coordinate
        static float GetMouseY(const RenderWindow& window);       // World mouse y coordinate


        static Vector2 GetMousePosition();
        static Vector2 GetMousePosition(const RenderWindow& window);
    };
}
