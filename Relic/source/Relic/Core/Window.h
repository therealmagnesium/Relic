#pragma once

namespace sf { class RenderWindow; class Drawable; }

namespace Relic
{
    struct WindowData
    {
        std::string title;
        uint32_t width; 
        uint32_t height;

        bool shouldClose = false;
    };

    class Window
    {
    public:
        Window(const WindowData& props);
        ~Window();

        void Init(const WindowData& props);
        void HandleEvents();
        void Clear(uint32_t color);
        void Display();

        inline const std::string& GetTitle() const { return m_data.title; }
        inline uint32_t GetWidth() const { return m_data.width; }
        inline uint32_t GetHeight() const { return m_data.height; }
        inline bool ShouldClose() const { return m_data.shouldClose; }
        inline sf::RenderWindow* GetHandle() const { return m_windowHandle; }

        void Draw(const sf::Drawable& drawable);
        void Close();

    private:
        WindowData m_data;
        sf::RenderWindow* m_windowHandle;
    };
}