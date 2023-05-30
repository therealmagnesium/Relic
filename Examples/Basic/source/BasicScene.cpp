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

    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("object");
    entity->AddComponent<SpriteRenderer>(); 
    auto& sr = entity->GetComponent<SpriteRenderer>().sprite;
    sr.SetOrigin(sr.GetSize().x / 2.f, sr.GetSize().y / 2.f);
    sr.SetScale(2.f, 2.f); 
    entity->AddComponent<Transform>(Vector2(m_app->GetWindowWidth() / 2.f, m_app->GetWindowHeight() / 2.f));
}

void BasicScene::OnUpdate() 
{
     
}
