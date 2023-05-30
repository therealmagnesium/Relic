#pragma once

#include <unordered_map>
#include <memory>

namespace Relic
{
    struct Font;
    struct Texture;

    class Assets
    {
    public:
        Assets();

        void AddFont(const std::string& name, const std::string& path);
        void AddTexture(const std::string& name, const std::string& path);
        void AddMusic(const std::string& name, const std::string& path);

        Font& GetFont(const std::string& name);
        Texture& GetTexture(const std::string& name);
        std::string& GetMusicPath(const std::string& name);

    public:
        static Font defaultFont;
        static Texture defaultTexture;
        static std::string defaultMusicPath;

    private:
        std::unordered_map<std::string, Font> m_fonts;
        std::unordered_map<std::string, Texture> m_textures;
        std::unordered_map<std::string, std::string> m_musics;
    };

}
