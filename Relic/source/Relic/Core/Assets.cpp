#include "pch.h"
#include "Assets.h"

namespace Relic
{
    sf::Font Assets::defaultFont = sf::Font();

    Assets::Assets()
    {
        if (!defaultFont.loadFromFile("assets/fonts/font.ttf"))
        {
            RL_CORE_ERROR("Failed to load default font file!");
            return; 
        }
    }

    void Assets::AddFont(const std::string &name, const std::string &path)
    {
        sf::Font font;
        if (!font.loadFromFile(path))
        {
            RL_CORE_ERROR("Failed to load font file - {}", path);
            return;
        }

        m_fonts[name] = font;
    }

    sf::Font& Assets::GetFont(const std::string &name)
    {
        return m_fonts[name];
    }
}
