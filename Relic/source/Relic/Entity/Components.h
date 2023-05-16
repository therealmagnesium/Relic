#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include "Relic/Core/Assets.h"
#include "Relic/Core/Log.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Relic
{
    struct Transform
    {
        bool has = false;

        Vector2 position = Vector2(0.f, 0.f);
        Vector2 velocity = Vector2(0.f, 0.f);
        float angle = 0.f;

        Transform(const Vector2& pos = Vector2(), const Vector2& vel = Vector2(), float a = 0.f) :
            position(pos), velocity(vel), angle(a) {}
    };

    struct Shape
    {
        bool has = false;
        sf::CircleShape circle;

        Shape(float radius = 32.f, int points = 4, uint32_t fill = 0x00FF00FF, uint32_t outline = 0x00FF00FF, float thickness = 4.f) :
            circle(radius, points)
        {
            circle.setFillColor(sf::Color(fill));
            circle.setOutlineColor(sf::Color(outline));
            circle.setOutlineThickness(thickness);
            circle.setOrigin(radius, radius);
        } 
    };

    struct Collision
    {
        bool has = false;
        float radius = 0.f;

        Collision(float radius) :
            radius(radius) {}
    };

    struct Lifetime
    {
        bool has = false;
        int lifetime = 0;

        Lifetime(int lifetime) :
            lifetime(lifetime) {}
    };

    struct Text
    {
        bool has = false;
        sf::Text text;

        Text(const sf::Font& font = Assets::defaultFont, const std::string& msg = "default", uint8_t fontSize = 24, uint32_t color = 0xFFFFFFFF) :
            text(msg, font, fontSize) 
            { text.setFillColor(sf::Color(color)); }
    };

    struct SpriteRenderer
    {
        bool has = false;       
        Sprite sprite; 

        SpriteRenderer(const sf::Texture& texture = Assets::defaultTexture, 
                        const Vector2& pos = Vector2(), const Vector2& scale = Vector2(1.f, 1.f), 
                        float angle = 0.f) :
            sprite(texture, pos.x, pos.y, angle) { sprite.SetScale(scale.x, scale.y); }
    };

    struct MusicSource
    {
        bool has = false;
        sf::Music music;

        MusicSource(const sf::Music& musicIn = Assets::defaultMusic)
            {}
    };
}
