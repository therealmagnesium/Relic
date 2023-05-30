#include "Drawables.h"

namespace Relic
{
    Polygon::Polygon(float radius, uint8_t points) :
        m_shape(radius, points) {}

    uint8_t Polygon::GetPointCount() const 
    { return m_shape.getPointCount(); }

    uint32_t Polygon::GetFillColor() const
    { return m_shape.getFillColor().toInteger(); }

    uint32_t Polygon::GetOutlineColor() const
    { return m_shape.getOutlineColor().toInteger(); } 

    float Polygon::GetRadius() const
    { return m_shape.getRadius(); }

    void Polygon::SetRadius(float radius)
    { m_shape.setRadius(radius); }

    void Polygon::SetRotation(float rotation)
    { m_shape.setRotation(rotation); }

    void Polygon::SetFillColor(uint32_t color)
    { m_shape.setFillColor(sf::Color(color)); }

    void Polygon::SetOutlineColor(uint32_t color)
    { m_shape.setOutlineColor(sf::Color(color)); }

    void Polygon::SetStrokeThickness(uint16_t thickness)
    { m_shape.setOutlineThickness(thickness); }

    void Polygon::SetPosition(float x, float y)
    { m_shape.setPosition(x, y); }

    void Polygon::SetOrigin(float xOffset, float yOffset)
    { m_shape.setOrigin(xOffset, yOffset); }

    void Polygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
    { target.draw(m_shape); }

    TextDrawable::TextDrawable(const Font& font, const std::string& msg, uint8_t fontSize) :
        m_text(msg, font.font, fontSize) {}

    float TextDrawable::GetWidth() const
    { return m_text.getGlobalBounds().width; }

    float TextDrawable::GetHeight() const
    { return m_text.getGlobalBounds().height; }

    void TextDrawable::SetFillColor(uint32_t color)
    { m_text.setFillColor(sf::Color(color)); }

    void TextDrawable::SetMessage(const std::string& msg)
    { m_text.setString(msg); }

    void TextDrawable::SetFont(const Font& font)
    { m_text.setFont(font.font); } 

    void TextDrawable::SetPosition(float x, float y)
    { m_text.setPosition(x, y); }

    void TextDrawable::SetOrigin(float xOffset, float yOffset)
    { m_text.setOrigin(xOffset, yOffset); }

    void TextDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
    { target.draw(m_text); }

    Sprite::Sprite(const Texture& texture, float x, float y, float a) :
        m_sprite(texture.texture)
    {
        m_sprite.setPosition(x, y);
        m_sprite.setRotation(a);
        m_sprite.scale(1.f, 1.f);
    }

    Vector2 Sprite::GetSize() 
    { return Vector2(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height); }

    void Sprite::SetPosition(float x, float y)
    { m_sprite.setPosition(x, y); }

    void Sprite::SetRotation(float a)
    { m_sprite.setRotation(a); }

    void Sprite::SetScale(float xScale, float yScale)
    { m_sprite.scale(xScale, yScale); }

    void Sprite::SetOrigin(float xOffset, float yOffset)
    { m_sprite.setOrigin(xOffset, yOffset); }

    void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
    { target.draw(m_sprite); }
}
