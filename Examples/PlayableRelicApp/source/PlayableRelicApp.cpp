#include "PlayableRelicApp.h"

PlayableRelicApp::PlayableRelicApp(const Relic::ApplicationProperties& props) :
    Relic::Application(props)
{

}

void PlayableRelicApp::OnStart()
{
    // Log the app has started
    RL_INFO("Playable Relic App has started successfully");

    // Initialize the entity manager
    InitEntityManager();
    
    /*
        Initialize the scene's entities, note that
        setting the fill color to 0x00000000 gives transparency
        effect
    */
    
    m_player = SpawnEntity(Relic::Vector2(200.f, 500.f), Relic::Vector2(3.f, 3.f), 32.f, 3, sf::Color(0x00000000), sf::Color::Blue);
    m_octogon = SpawnEntity(Relic::Vector2(100.f, 100.f), Relic::Vector2(3.f, 6.f), 32.f, 8, sf::Color(0x00000000), sf::Color::Red);
    m_square = SpawnEntity(Relic::Vector2(100.f, 100.f), Relic::Vector2(6.f, 3.f), 64.f, 4, sf::Color(0x00000000), sf::Color::Green);
      
}

void PlayableRelicApp::OnUpdate()
{
    // Update the entity manager
    UpdateEntityManager();
    
    // Move the entities based on their velocity
    m_octogon->Move(m_octogon->GetXVel(), m_octogon->GetYVel());    
    m_square->Move(m_square->GetXVel(), m_square->GetYVel());
    
    // Check if any entities are colliding with the borders; If so, flip the velocity
    for (auto& e : GetAllEntities())
    {
        if (e->GetX() + e->GetRadius() > GetWindowWidth() || e->GetX() < e->GetRadius())
            e->transform->velocity.x *= -1;
        if (e->GetY() + e->GetRadius() > GetWindowHeight() || e->GetY() < e->GetRadius())
            e->transform->velocity.y *= -1;
    }
}

void PlayableRelicApp::OnRender()
{
    // For every entitiy in the entity manager...
    for (auto& e : GetAllEntities())
    {
        // Set the entity's actual shape position at its transform's position
        e->shape->circle.setPosition(e->GetX(), e->GetY());

        // Rotate the shape's angle
        e->transform->angle += 1.f;
        
        // If the angle goes above 360, set it back to 0
        if (e->transform->angle > 360.f)
            e->transform->angle = 0.f;
        
        // Set the entity's actual shape rotation at its transform's rotation
        e->shape->circle.setRotation(e->GetAngle());
        
        // Draw every entity's shape
        Draw(e->shape->circle);
    }
}

std::shared_ptr<Relic::Entity> PlayableRelicApp::SpawnEntity(Relic::Vector2 position, Relic::Vector2 velocity, 
                                                            float radius, int points, 
                                                            const sf::Color& fill, const sf::Color& outline)
{
    /* 
        Create an entity and give it a tag ov 'object',
        then set the components for the entity, and finally return
        the new entity
    */

    std::shared_ptr<Relic::Entity> entity = AddEntity("object");
    entity->transform = std::make_shared<Relic::Tranform>(position, velocity, 0.f);
    entity->shape = std::make_shared<Relic::Shape>(radius, points, fill, outline, 4.f);
    return entity;   
}

Relic::Application* Relic::CreateApplication()
{
    /*
        Create an instance of your application,
        call the OnStart() method for it, then
        return the instance to the application
    */

    Relic::ApplicationProperties properties;
    properties.name = "Playable Relic App";
    properties.width = 800;
    properties.height = 600;

    PlayableRelicApp* game = new PlayableRelicApp(properties);
    game->OnStart();
    return game; 
}
