#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>

#include <unordered_map>
#include <memory>

namespace Relic
{
    class Assets
    {
    public:
        Assets();

        void AddFont(const std::string& name, const std::string& path);
        void AddTexture(const std::string& name, const std::string& path);
        void AddMusic(const std::string& name, const std::string& path);

        sf::Font& GetFont(const std::string& name);
        sf::Texture& GetTexture(const std::string& name);
        sf::Music& GetMusic(const std::string& name);

    public:
        static sf::Font defaultFont;
        static sf::Texture defaultTexture;
        static sf::Music defaultMusic;

    private:
        std::unordered_map<std::string, sf::Font> m_fonts;
        std::unordered_map<std::string, sf::Texture> m_textures;
        std::unordered_map<std::string, sf::Music> m_musics;
    };
}
