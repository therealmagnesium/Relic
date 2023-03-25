#pragma once
#include "Vector2.h"

namespace Relic
{
    struct Tranform
    {
        Vector2 position = { 0.f, 0.f };
        Vector2 velocity = { 0.f, 0.f };
        float angle = 0.f;

        Tranform(const Vector2& pos, const Vector2& vel, float a) :
            position(pos), velocity(vel), angle(a) {}
    };
}