#pragma once
#include "Drawables.h"
#include "Vector2.h"
#include "Relic/Core/Assets.h"
#include "Relic/Core/Audio.h"

#include <memory>

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
        Polygon shape;

       Shape(float radius = 32.f, int points = 4, uint32_t fill = 0xF1FAEEFF, uint32_t outline = 0xE63946FF, float thickness = 4.f) :
            shape(radius, points) 
        {
            shape.SetFillColor(fill);
            shape.SetOutlineColor(outline);
            shape.SetStrokeThickness(thickness); 
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
        TextDrawable text;

        Text(const Font& font = Assets::defaultFont, const std::string& msg = "default", uint8_t fontSize = 24, uint32_t color = 0xFFFFFFFF) :
            text(font, msg, fontSize) 
            { text.SetFillColor(color); }
    };

    struct SpriteRenderer
    {
        bool has = false;       
        Sprite sprite; 
 
        SpriteRenderer(const Texture& texture = Assets::defaultTexture, 
                        const Vector2& pos = Vector2(), const Vector2& scale = Vector2(1.f, 1.f), 
                        float angle = 0.f) :
            sprite(texture, pos.x, pos.y, angle) 
            { sprite.SetScale(scale.x, scale.y); }
    };

    struct AudioSource
    {
        bool has = false;
        Audio audio; 

        AudioSource(const std::string& path = Assets::defaultMusicPath) :
            audio(path) {}
    };
}
