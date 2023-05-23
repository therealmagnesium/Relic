#pragma once
#include "Assets.h"
#include "Window.h"

#include <memory>

#define WINDOW_WIDTH GetWindowWidth()
#define WINDOW_HEIGHT GetWindowHeight()

namespace Relic
{
    class Entity;
    class EntityManager;

    typedef std::vector<std::shared_ptr<Entity>> EntityVec;

    struct ApplicationProperties
    {
        std::string name = "Relic App";
        uint32_t width = 1600;
        uint32_t height = 900;
    };

    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void OnStart() = 0;
        virtual void OnUpdate() = 0;

        void LoadAssetsFile(const std::string& path);
        void LoadConfigFile(const std::string& path);
        
        void Run();
        void Close();

        void Constrain(std::shared_ptr<Entity> entity, float x, float y);
        void Draw(const sf::Drawable& drawable);
        void Render();

        inline const std::string& GetTitle() const { return m_window->GetTitle(); }
        inline uint32_t GetWindowWidth() const { return m_window->GetWidth(); }
        inline uint32_t GetWindowHeight() const { return m_window->GetHeight(); }

        inline std::shared_ptr<Assets> GetAssets() const { return m_assets; }
        inline std::shared_ptr<Window> GetWindow() const { return m_window; }
        inline sf::RenderWindow& GetNativeWindow() const { return *m_window->GetHandle(); }

    public:
        static int currentFrame;
        static int frameLimit;

    protected:
        EntityVec& GetAllEntities();
        EntityVec& GetAllEntities(const std::string& tag);
        std::shared_ptr<Entity> AddEntity(const std::string& tag);

    private:
        void Init();
        void Shutdown();

        bool IsInWindow(std::shared_ptr<Entity> entity);

    private:
        WindowData m_properties;

        std::shared_ptr<Assets> m_assets;
        std::shared_ptr<Window> m_window;
        std::shared_ptr<EntityManager> m_entityManager;
    };

    Application* CreateApplication();
}
