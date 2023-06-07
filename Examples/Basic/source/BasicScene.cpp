#include "BasicScene.h"

BasicScene::BasicScene(Application* app) :
    Scene(app)
{
    // Log example texts to the console (will not show in dist build)
    RL_TRACE("Relic trace example");
    RL_INFO("Relic info example");
    RL_WARN("Relic warn example");
    RL_ERROR("Relic error example");
    RL_CRITICAL("Relic critical example");

    // Create 3 vectors
    Relic::Vector2 v1(100.f, 100.f);
    Relic::Vector2 v2(200.f, 200.f);
    Relic::Vector2 v3 = v1 + v2;

    // Log the vectors to the console
    RL_TRACE("v1: {}, {}", v1.x, v1.y);        
    RL_TRACE("v2: {}, {}", v2.x, v2.y);        
    RL_TRACE("v1 + v2 = {}, {}", v3.x, v3.y);

    m_blueHex = SpawnEntity(Vector2(400.f, 0.f), 0x0000FFFF, 0xFFFFFFFF);
    m_greenHex = SpawnEntity(Vector2(0.f, m_app->GetWindowHeight()-200.f), 0x00FF00FF, 0xFFFFFFFF);
    m_redHex = SpawnEntity(Vector2(), 0xFF0000FF, 0xFFFFFFFF);
}

void BasicScene::OnUpdate(float dt) 
{
    float amplitude = 200.f;
    float frequency = 3.f;

    Vector2 blueHexOffset = Vector2(400.f, m_app->GetWindowHeight()/2.f);
    Vector2 greenHexOffset = Vector2(m_app->GetWindowWidth()/2.f, m_app->GetWindowHeight()-200.f);
    Vector2 redHexOffset = Vector2(m_app->GetWindowWidth()-400.f, m_app->GetWindowHeight()/2.f);

    m_blueHex->GetComponent<Transform>().position.y = std::sin(m_app->GetTime() * frequency) * amplitude + blueHexOffset.y; 
    m_greenHex->GetComponent<Transform>().position.x = std::sin(m_app->GetTime() * frequency) * amplitude + greenHexOffset.x; 

    m_redHex->GetComponent<Transform>().position.x = std::sin(m_app->GetTime() * frequency) * amplitude + redHexOffset.x; 
    m_redHex->GetComponent<Transform>().position.y = std::sin(m_app->GetTime() * frequency) * amplitude + redHexOffset.y; 
    
    m_currentFrame++;
}

std::shared_ptr<Entity> BasicScene::SpawnEntity(const Vector2& pos, uint32_t fill, uint32_t outline)
{ 
    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("entity");
    entity->AddComponent<Transform>(pos);   
    entity->AddComponent<Shape>(32.f, 6, fill, outline); 
    auto& sp = entity->GetComponent<Shape>().shape;
    sp.SetOrigin(sp.GetRadius(), sp.GetRadius()); 

    return entity;
}
