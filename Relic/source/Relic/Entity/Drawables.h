#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Vector2.h"
#include "Relic/Core/Graphics.h"
#include "Relic/Core/Assets.h"

#include <cstdint>

namespace Relic
{
    class Polygon : public Drawable 
    {
    public:
        Polygon(float radius, uint8_t points); 

        uint8_t GetPointCount() const; 
        uint32_t GetFillColor() const; 
        uint32_t GetOutlineColor() const;
        float GetRadius() const;
        
        void SetRadius(float radius);  
        void SetRotation(float rotation); 
        void SetFillColor(uint32_t color);
        void SetOutlineColor(uint32_t color);
        void SetStrokeThickness(uint16_t thickness);
        void SetPosition(float x, float y);
        void SetOrigin(float xOffset, float yOffset);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::CircleShape m_shape;
    };

    class TextDrawable : public Drawable
    {
    public:
        TextDrawable(const Font& font, const std::string& msg, uint8_t fontSize);

        float GetWidth() const; 
        float GetHeight() const;

        void SetFillColor(uint32_t color);
        void SetMessage(const std::string& msg);
        void SetFont(const Font& font);
        void SetPosition(float x, float y);
        void SetOrigin(float xOffset, float yOffset);
   
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Text m_text;
    };

    class Sprite : public Drawable
    {
    public:
        Sprite(const Texture& texture, float x, float y, float a);

        Vector2 GetSize();

        void SetPosition(float x, float y);
        void SetRotation(float a);
        void SetScale(float xScale, float yScale);
        void SetOrigin(float xOffset, float yOffset);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite m_sprite;
    };
}
