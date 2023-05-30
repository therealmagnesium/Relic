#pragma once
#include "Window.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

namespace Relic
{
    class Assets;
    class Entity;
    class EntityManager;
    class Scene;

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

        void LoadAssetsFile(const std::string& path);
        void LoadConfigFile(const std::string& path);
        
        void Run();
        void Close();
        
        void ChangeScene(const std::string& name, std::shared_ptr<Scene> newScene, bool onEnd);
        void Render();

        uint32_t GetWindowWidth() const; 
        uint32_t GetWindowHeight() const; 
        const std::string& GetTitle() const; 
        RenderWindow& GetNativeWindow() const; 

        inline std::string& GetCurrentScene() { return m_currentScene; }
        inline std::shared_ptr<Assets> GetAssets() const { return m_assets; }
        inline std::shared_ptr<Window> GetWindow() const { return m_window; }

    public:
        static int frameLimit;

    protected:
        void Init();
        void Shutdown();

    protected:
        std::string m_currentScene;
        std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;

    private:
        WindowData m_properties;

        std::shared_ptr<Assets> m_assets;
        std::shared_ptr<Window> m_window;
    };

    Application* CreateApplication();
}
