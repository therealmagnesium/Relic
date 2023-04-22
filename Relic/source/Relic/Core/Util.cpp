#include "pch.h"
#include "Util.h"

namespace Relic
{
    float GetMagnitude(const Vector2& p)
    {
        return sqrt((p.x*p.x) + (p.y*p.y));
    }

    float GetDistance(const Vector2& a, const Vector2& b)
    {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return sqrt((dx*dx) + (dy*dy));
    }

    Vector2 Normalize(const Vector2& p)
    {
        float magnitude = GetMagnitude(p);
        return (magnitude > 0) ? p / magnitude : Vector2(0.f, 0.f);
    }
}