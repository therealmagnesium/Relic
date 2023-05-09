#pragma once
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <memory>

namespace Relic
{
    class Assets
    {
    public:
        Assets();

        void AddFont(const std::string& name, const std::string& path);
        sf::Font& GetFont(const std::string& name);

    public:
        static sf::Font defaultFont;

    private:
        std::unordered_map<std::string, sf::Font> m_fonts;
    };
}
