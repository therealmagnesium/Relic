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

    int ReplaceByte(int num, int bytePos, uint8_t newByte)
    {
        int shiftAmount = bytePos * 8;
        int mask = ~(0xFF << shiftAmount);
        int clearedNum = num & mask;
        int shiftedByte = newByte << shiftAmount;
        int result = clearedNum | shiftedByte;

        return result;
    }

    Vector2 Normalize(const Vector2& p)
    {
        float magnitude = GetMagnitude(p);
        return (magnitude > 0) ? p / magnitude : Vector2(0.f, 0.f);
    }
}
