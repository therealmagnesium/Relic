#include "Core/Log.h"
#include "pch.h"
#include "Assets.h"

namespace Relic
{
    sf::Font Assets::defaultFont = sf::Font();
    sf::Texture Assets::defaultTexture = sf::Texture();

    Assets::Assets()
    {
        if (!defaultFont.loadFromFile("assets/fonts/default.ttf"))
        {
            RL_CORE_ERROR("Failed to load default font file!");
            return; 
        }

        if (!defaultTexture.loadFromFile("assets/textures/default.png"))
        {
            RL_CORE_ERROR("Failed to load default texture file!");
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

    void Assets::AddTexture(const std::string &name, const std::string &path)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
        {
            RL_CORE_ERROR("Failed to load texture - {}", path);
            return;
        }

        m_textures[name] = texture;
    }

    void Assets::AddMusic(const std::string &name, const std::string &path)
    {
        m_musics[name] = path; 
    }

    sf::Font& Assets::GetFont(const std::string &name)
    { return m_fonts[name]; } 

    sf::Texture& Assets::GetTexture(const std::string &name)
    { return m_textures[name]; }

    std::string& Assets::GetMusic(const std::string& name)
    { return m_musics[name]; }
}
