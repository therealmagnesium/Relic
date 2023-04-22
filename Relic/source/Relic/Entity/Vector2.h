#pragma once

namespace Relic
{
    struct Vector2
    {
        float x;
        float y;

        Vector2();
        Vector2(float xIn, float yIn);

        bool operator == (const Vector2& v) const;
        bool operator != (const Vector2& v) const;

        Vector2 operator + (const Vector2& v) const;
        Vector2 operator - (const Vector2& v) const;
        Vector2 operator * (const Vector2& v) const;
        Vector2 operator / (const Vector2& v) const;

        Vector2 operator * (int s) const;
        Vector2 operator / (int s) const;
        Vector2 operator * (float s) const;
        Vector2 operator / (float s) const;

        float Dist(const Vector2& v) const;
    };
}