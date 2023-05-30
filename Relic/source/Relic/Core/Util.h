#pragma once
#include "Relic/Entity/Vector2.h"
#include <cstdint>

namespace Relic
{
    float GetMagnitude(const Vector2& p);
    float GetDistance(const Vector2& a, const Vector2& b);

    int ReplaceByte(int num, int bytePos, uint8_t newByte);

    Vector2 Normalize(const Vector2& p);
}
