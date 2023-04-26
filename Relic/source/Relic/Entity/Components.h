#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>

namespace Relic
{
    struct Transform
    {
        Vector2 position = Vector2(0.f, 0.f);
        Vector2 velocity = Vector2(0.f, 0.f);
        float angle = 0.f;

        Transform(const Vector2& pos, const Vector2& vel, float a) :
            position(pos), velocity(vel), angle(a) {}
    };

    struct Shape
    {
        sf::CircleShape circle;

        Shape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness) :
            circle(radius, points)
        {
            circle.setFillColor(fill);
            circle.setOutlineColor(outline);
            circle.setOutlineThickness(thickness);
            circle.setOrigin(radius, radius);
        }       
    };

    struct Collision
    {
        float radius = 0.f;

        Collision(float radius) :
            radius(radius) {}
    };

    struct Lifetime
    {
        int lifetime = 0;

        Lifetime(int lifetime) :
            lifetime(lifetime) {}
    };
}
