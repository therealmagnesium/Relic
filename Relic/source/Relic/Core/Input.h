#pragma once
#include "KeyCodes.h"
#include "Relic/Entity/Vector2.h"

namespace Relic
{
    class Input
    {
    public:
        static bool IsKeyPressed(int16_t key);

        static bool IsMouseButtonPressed(uint8_t button);
        static float GetMouseX();
        static float GetMouseY();
        static Vector2 GetMousePosition();
    };
}
