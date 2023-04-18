#pragma once
#include "Relic/Entity/Entity.h"
#include "Relic/Entity/Vector2.h"

namespace Relic
{
    float GetMagnitude(const Vector2& p);
    float GetDistance(const Vector2& a, const Vector2& b);

    Vector2 Normalize(const Vector2& p);
}