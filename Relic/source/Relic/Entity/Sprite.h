#pragma once
#include "SFML/Graphics/RenderStates.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace Relic
{
    class Sprite : public sf::Drawable
    {
    public:
        Sprite(const sf::Texture& texture, float x = 0.f, float y = 0.f, float a = 0.f);
        
        void SetPosition(float x, float y);
        void SetRotation(float a);
        void SetScale(float xScale, float yScale);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite m_sprite;
    };
}
