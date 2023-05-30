#pragma once
#include <string>
#include <memory>

namespace Relic
{
    struct Drawable;
    struct RenderWindow;

    struct WindowData
    {
        std::string title;
        uint32_t width; 
        uint32_t height;
        uint8_t style;

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
        std::shared_ptr<RenderWindow> GetHandle() const; 

        inline void EnableShouldClose() { m_data.shouldClose = true; }

        void Draw(const Drawable& drawable);
        void Close();

    private:
        WindowData m_data;
        std::shared_ptr<RenderWindow> m_windowHandle;
    };
}
