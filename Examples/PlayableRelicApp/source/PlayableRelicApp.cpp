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
    
    m_player = SpawnPlayer();
    m_octogon = SpawnEntity(Relic::Vector2(100.f, 100.f), Relic::Vector2(3.f, 6.f), 32.f, 8, sf::Color::Red, sf::Color::White);
    m_square = SpawnEntity(Relic::Vector2(100.f, 100.f), Relic::Vector2(6.f, 3.f), 64.f, 4, sf::Color::Green, sf::Color::White);
      
}

void PlayableRelicApp::OnUpdate()
{
    // Update the entity manager
    UpdateEntityManager();

    // Handle player movement
    HandleMovement();

    // Move the entities based on their velocity
    m_player->Move(m_player->GetXVel(), m_player->GetYVel());
    m_octogon->Move(m_octogon->GetXVel(), m_octogon->GetYVel());    
    m_square->Move(m_square->GetXVel(), m_square->GetYVel());

    // Constrain the player into the window
    Constrain(m_player, GetWindowWidth(), GetWindowHeight());

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

void PlayableRelicApp::HandleMovement()
{ 
    static float speed = 6.f;
    m_player->transform->velocity = Relic::Vector2(0.f, 0.f);

    // Move the player's x velocity based on the left and right keys
    if (m_player->input->keyLeft)
        m_player->transform->velocity.x = -speed;
    if (m_player->input->keyRight)
        m_player->transform->velocity.x = speed;
    
    // Move the player's y velocity based on the up and down keys
    if (m_player->input->keyUp)
        m_player->transform->velocity.y = -speed;
    if (m_player->input->keyDown)
        m_player->transform->velocity.y = speed;

    // If the user clicks the left mouse button, then shoot a bullet
    if (m_player->input->mouseLeft)
    {
        RL_TRACE("bullet at ({}, {})", m_player->input->clickedPosition.x, m_player->input->clickedPosition.y);
        SpawnBullet(m_player, m_player->input->clickedPosition);
    }
}

std::shared_ptr<Relic::Entity> PlayableRelicApp::SpawnPlayer()
{
    /* 
        Create the player entity and give it a tag of 'player',
        then set the components for the player, and finally return
        the new entity
    */

    std::shared_ptr<Relic::Entity> entity = AddEntity("player");
    entity->transform = std::make_shared<Relic::Transform>(Relic::Vector2(200.f, 500.f), Relic::Vector2(3.f, 3.f), 0.f);
    entity->shape = std::make_shared<Relic::Shape>(32.f, 3, sf::Color::Blue, sf::Color::White, 4.f);
    entity->collision = std::make_shared<Relic::Collision>(32.f);
    entity->input = std::make_shared<Relic::Input>();

    return entity;   
}

std::shared_ptr<Relic::Entity> PlayableRelicApp::SpawnEntity(const Relic::Vector2& position, const Relic::Vector2& velocity, 
                                                            float radius, int points, 
                                                            const sf::Color& fill, const sf::Color& outline)
{
    /* 
        Create an entity and give it a tag of 'object',
        then set the components for the entity, and finally return
        the new entity
    */

    std::shared_ptr<Relic::Entity> entity = AddEntity("object");
    entity->transform = std::make_shared<Relic::Transform>(position, velocity, 0.f);
    entity->shape = std::make_shared<Relic::Shape>(radius, points, fill, outline, 4.f);
    entity->collision = std::make_shared<Relic::Collision>(radius);

    return entity;   
}

void PlayableRelicApp::SpawnBullet(std::shared_ptr<Relic::Entity> entity, const Relic::Vector2& target)
{
    /* 
        Create a bullet entity, which travels towards
        the target parameter; then give the entity
        its components
    */

    std::shared_ptr<Relic::Entity> bullet = AddEntity("bullet");
    bullet->transform = std::make_shared<Relic::Transform>(target, Relic::Vector2(0.f, 0.f), 0.f);
    bullet->shape = std::make_shared<Relic::Shape>(10, 8, sf::Color::White, sf::Color::Blue, 2.f);
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
    properties.width = 1024;
    properties.height = 576;

    PlayableRelicApp* game = new PlayableRelicApp(properties);
    game->OnStart();
    return game; 
}
