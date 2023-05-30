#include "pch.h"
#include "Application.h"
#include "Log.h"
#include "Scene.h"
#include "Window.h"

#include "Relic/Entity/Components.h"
#include "Relic/Entity/Entity.h"
#include "Relic/Entity/EntityManager.h"

#include <fstream>
#include <SFML/Graphics.hpp>

namespace Relic
{
    int Application::frameLimit = 60;

    Application::Application()
    {
        Init();
    }

    Application::~Application()
    {
        Shutdown();
    }

    void Application::Init()
    {
        LoadConfigFile("data/preload/settings.cfg");
        m_window = std::make_shared<Window>(m_properties);

        m_assets = std::make_shared<Assets>(); 
        LoadAssetsFile("data/preload/assets.cfg");
    }

    void Application::LoadAssetsFile(const std::string& path)
    {
        std::ifstream in(path);
        std::string temp;

        std::string fontName;
        std::string fontPath;

        std::string textureName;
        std::string texturePath;

        std::string musicName;
        std::string musicPath;

        if (!in.is_open())
        {
            RL_CORE_CRITICAL("Failed to open assets file - {}!", path);
            return;
        }

        while (in >> temp)
        {
            if (temp == "Font")
            {
                in >> fontName >> fontPath;
                m_assets->AddFont(fontName, fontPath);
            }
            if (temp == "Texture")
            {
                in >> textureName >> texturePath;
                m_assets->AddTexture(textureName, texturePath);
            }
            if (temp == "Music")
            {
                in >> musicName >> musicPath;
                m_assets->AddMusic(musicName, musicPath);
            }
        }
    }

    void Application::LoadConfigFile(const std::string& path)
    {
        std::ifstream in(path);
        std::string temp;

        if (!in.is_open())
        {
            RL_CORE_CRITICAL("Failed to open config file - '{}'", path);
            return;
        }

        while (in >> temp)
        {
            if (temp == "Window")
                in >> m_properties.width >> m_properties.height >> m_properties.title >> m_properties.style;
            
            if (temp == "FPS")
                in >> frameLimit;
       
            if (temp == "StartScene")
                in >> m_currentScene;
        }

        RL_CORE_TRACE("Application properties: {}, {}, {}", m_properties.title, m_properties.width, m_properties.height);
    }

    void Application::Shutdown()
    {
        RL_CORE_INFO("Successfully shutdown application!");
        m_window->Close();
    }

    void Application::Run()
    {        
        while (!m_window->ShouldClose())
        {
            m_scenes[m_currentScene]->UpdateEntityManager();

            m_window->HandleEvents();
            m_scenes[m_currentScene]->OnUpdate(); 

            m_scenes[m_currentScene]->CullEntities(GetWindowWidth(), GetWindowHeight());
            m_scenes[m_currentScene]->HandleComponents();

            m_window->Clear(0x0A0A0AFF);
            Render();
            m_window->Display();
        }
    }

    void Application::ChangeScene(const std::string& name, std::shared_ptr<Scene> newScene, bool onEnd)
    { 
        if (onEnd)
            m_scenes[m_currentScene]->OnEnd();

        m_currentScene = name;
        m_scenes[m_currentScene] = newScene;
    }

    void Application::Render()
    {
        for (auto& e : m_scenes[m_currentScene]->GetEntityManager().GetEntities())
        { 
            if (e->IsInRenderView(GetWindowWidth(), GetWindowHeight()) && e->IsEnabled())
            {
                if (e->HasComponent<Text>())
                    m_window->Draw(e->GetComponent<Text>().text);
                
                if (e->HasComponent<Shape>())
                    m_window->Draw(e->GetComponent<Shape>().shape);

                if (e->HasComponent<SpriteRenderer>())
                    m_window->Draw(e->GetComponent<SpriteRenderer>().sprite);
            }
        }
    }

    void Application::Close() 
    { m_window->EnableShouldClose(); }  

    uint32_t Application::GetWindowWidth() const
    { return m_window->GetWidth(); }

    uint32_t Application::GetWindowHeight() const
    { return m_window->GetHeight(); } 

    const std::string& Application::GetTitle() const
    { return m_window->GetTitle(); }    

    RenderWindow& Application::GetNativeWindow() const
    { return *m_window->GetHandle(); }

}
