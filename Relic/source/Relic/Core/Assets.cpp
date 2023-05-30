#include "pch.h"
#include "Assets.h"
#include "Log.h"
#include "Graphics.h"

namespace Relic
{
    Font Assets::defaultFont = Font();
    Texture Assets::defaultTexture = Texture();
    std::string Assets::defaultMusicPath = "assets/preload/sounds/default.wav";

    Assets::Assets()
    {
        if (!defaultFont.font.loadFromFile("assets/preload/fonts/default.ttf"))
        {
            RL_CORE_ERROR("Failed to load default font file!");
            return; 
        }

        if (!defaultTexture.texture.loadFromFile("assets/preload/textures/default.png"))
        {
            RL_CORE_ERROR("Failed to load default texture file!");
            return;
        } 
   }

    void Assets::AddFont(const std::string& name, const std::string& path)
    {
        sf::Font font;
        if (!font.loadFromFile(path))
        {
            RL_CORE_ERROR("Failed to load font file - {}", path);
            return;
        }

        m_fonts[name].font = font;
        m_fonts[name].path = path; 
    }

    void Assets::AddTexture(const std::string& name, const std::string& path)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
        {
            RL_CORE_ERROR("Failed to load texture - {}", path);
            return;
        }

        m_textures[name].texture = texture;
        m_textures[name].path = path;
    }

    void Assets::AddMusic(const std::string& name, const std::string& path)
        { m_musics[name] = path; }

    Font& Assets::GetFont(const std::string&name)
        { return m_fonts[name]; } 

    Texture& Assets::GetTexture(const std::string&name)
        { return m_textures[name]; }

    std::string& Assets::GetMusicPath(const std::string& name)
        { return m_musics[name]; }
}
