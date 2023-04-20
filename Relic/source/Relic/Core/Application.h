#pragma once
#include "Window.h"

#define WINDOW_WIDTH GetWindowWidth()
#define WINDOW_HEIGHT GetWindowHeight()

namespace sf { class Drawable; }

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
        Application(const WindowData& props = WindowData());
        virtual ~Application();

        virtual void OnStart() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;

        void Run();

        void Constrain(std::shared_ptr<Entity> entity, uint32_t x, uint32_t y);
        void Draw(const sf::Drawable& drawable);

        inline const std::string& GetTitle() const { return m_window->GetTitle(); }
        inline uint32_t GetWindowWidth() const { return m_window->GetWidth(); }
        inline uint32_t GetWindowHeight() const { return m_window->GetHeight(); }

        inline std::shared_ptr<Window> GetWindow() const { return m_window; }
        inline sf::RenderWindow& GetNativeWindow() const { return *m_window->GetHandle(); }

    protected:
        EntityVec& GetAllEntities();
        EntityVec& GetAllEntities(const std::string& tag);
        std::shared_ptr<Entity> AddEntity(const std::string& tag);

    private:
        void Init();
        void Shutdown();

        void InitEntityManager();
        void UpdateEntityManager();
        void RemoveInactiveEntities();

        bool IsInWindow(std::shared_ptr<Entity> entity);

    private:
        WindowData m_properties;

        std::shared_ptr<Window> m_window;
        std::shared_ptr<EntityManager> m_entityManager;
    };

    Application* CreateApplication();
}
