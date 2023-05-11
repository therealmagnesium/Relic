#include "Sprite.h"

namespace Relic
{
    Sprite::Sprite(const sf::Texture& texture, float x, float y, float a) :
        m_sprite(texture)
    {
        m_sprite.setPosition(x, y);
        m_sprite.setRotation(a);
        m_sprite.scale(1.f, 1.f);
    }

    void Sprite::SetPosition(float x, float y)
        { m_sprite.setPosition(x, y); }

    void Sprite::SetRotation(float a)
        { m_sprite.setRotation(a); }

    void Sprite::SetScale(float xScale, float yScale)
        { m_sprite.scale(xScale, yScale); }

    void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
        { target.draw(m_sprite); }
}
