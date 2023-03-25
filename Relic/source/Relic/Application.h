#pragma once
#include <string>
#include <memory>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;

namespace Relic
{
    struct ApplicationProperties
    {
        std::string name = "Relic App";
        uint32_t width = 1600;
        uint32_t height = 900;
    };

    class Application
    {
    public:
        Application(const ApplicationProperties& props = ApplicationProperties());
        virtual ~Application();

        void Run();
        void Close();

        SDL_Window* GetWindowHandle() const { return m_windowHandle; }

    private:
        void Init();
        void Shutdown();

    private:
        ApplicationProperties m_properties;
        bool m_running = false;

        SDL_Window* m_windowHandle = nullptr;
        SDL_Renderer* m_renderer = nullptr;
    };

    Application* CreateApplication();
}