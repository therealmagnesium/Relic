#include "Entity/Components.h"
#include "pch.h"
#include "Application.h"
#include "Log.h"
#include "Entity/EntityManager.h"

#include <fstream>
#include <SFML/Graphics.hpp>

namespace Relic
{
    int Application::currentFrame = 0;

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
        LoadConfigFile("data/settings.cfg");
        m_window = std::make_shared<Window>(m_properties);

        m_assets = std::make_shared<Assets>();
        LoadAssetsFile("data/assets.cfg");

        m_entityManager = std::make_shared<EntityManager>();
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
            m_entityManager->Update();

            m_window->HandleEvents();
            OnUpdate();
            currentFrame++;

            m_entityManager->CullEntities(WINDOW_WIDTH, WINDOW_HEIGHT); 
            m_entityManager->HandleComponents();

            m_window->Clear(0x0A0A0AFF);
            Render();
            m_window->Display();

        }
    }

    void Application::Render()
    {
        for (auto& e : GetAllEntities())
        { 
            if (e->IsInRenderView(WINDOW_WIDTH, WINDOW_HEIGHT) && e->IsEnabled())
            {
                if (e->HasComponent<Text>())
                    Draw(e->GetComponent<Text>().text);
                
                if (e->HasComponent<Shape>())
                    Draw(e->GetComponent<Shape>().circle);

                if (e->HasComponent<SpriteRenderer>())
                    Draw(e->GetComponent<SpriteRenderer>().sprite);

            }
        }
    }

    void Application::Close() 
        { m_window->EnableShouldClose(); }
    
    void Application::Constrain(std::shared_ptr<Entity> entity, float x, float y)
    {
        if (entity->GetComponent<Transform>().position.x < entity->GetRadius()) 
            entity->GetComponent<Transform>().position.x = entity->GetRadius();
        if (entity->GetComponent<Transform>().position.x + entity->GetRadius() > x)
            entity->GetComponent<Transform>().position.x = x - entity->GetRadius();

        if (entity->GetComponent<Transform>().position.y < entity->GetRadius())
            entity->GetComponent<Transform>().position.y = entity->GetRadius();
        if (entity->GetComponent<Transform>().position.y + entity->GetRadius() > y)
            entity->GetComponent<Transform>().position.y = y - entity->GetRadius();
    }

    bool Application::IsInWindow(std::shared_ptr<Entity> entity)
    {
        return (entity->GetX() + entity->GetRadius() >= 0.f && entity->GetX() - entity->GetRadius() < WINDOW_WIDTH && 
            entity->GetY() + entity->GetRadius() >= 0.f && entity->GetY() - entity->GetRadius() < WINDOW_HEIGHT);
    }

    void Application::Draw(const sf::Drawable& drawable) { m_window->Draw(drawable); }

    EntityVec& Application::GetAllEntities() 
        { return m_entityManager->GetEntities(); }
    
    EntityVec& Application::GetAllEntities(const std::string& tag) 
        { return m_entityManager->GetEntities(tag); }
    
    std::shared_ptr<Entity> Application::AddEntity(const std::string& tag) 
        { return m_entityManager->AddEntity(tag); }
}
