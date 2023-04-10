#pragma once
#include <SFML/Graphics.hpp>

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
        Application(const ApplicationProperties& props = ApplicationProperties());
        virtual ~Application();

        virtual void OnStart() = 0;
        virtual void OnEvent() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;

        void Run();
        void HandleEvents();
        void Close();

        void Constrain(const std::shared_ptr<Entity>&  entity, uint32_t  x, uint32_t  y);
        void Draw(const sf::Drawable& drawable);

        inline const std::string& GetTitle() const { return m_properties.name; }
        inline uint32_t GetWindowWidth() const { return m_properties.width; }
        inline uint32_t GetWindowHeight() const { return m_properties.height; }

    protected:
        EntityVec& GetAllEntities();
        std::shared_ptr<Entity> AddEntity(const std::string& tag);

        void InitEntityManager();
        void UpdateEntityManager();
        
    private:
        void Init();
        void Shutdown();

    private:
        ApplicationProperties m_properties;
        bool m_running = false;

        sf::RenderWindow* m_windowHandle;
        std::shared_ptr<EntityManager> m_entityManager;
    };

    Application* CreateApplication();
}
