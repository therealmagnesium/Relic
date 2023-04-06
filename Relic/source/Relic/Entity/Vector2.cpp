#include "pch.h"
#include "Vector2.h"

namespace Relic
{
    Vector2::Vector2() : x(0.f), y(0.f) {}
    Vector2::Vector2(float xIn, float yIn) : x(xIn), y(yIn) {}

    bool Vector2::operator == (const Vector2& v) const { return (x == v.x && y == v.y); }
    bool Vector2::operator != (const Vector2& v) const { return (x != v.x && y != v.y); }
    
    Vector2 Vector2::operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
    Vector2 Vector2::operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
    Vector2 Vector2::operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
    Vector2 Vector2::operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }
}
