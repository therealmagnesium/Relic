#include "PlayableRelicApp.h"

PlayableRelicApp::PlayableRelicApp(const WindowData& props) :
    Application(props)
{

}

void PlayableRelicApp::OnStart()
{
    // Log the app has started
    RL_TRACE("Playable Relic App has started!");
    
    /*
        Initialize the scene's entities, note that
        setting the fill color to 0x00000000 gives transparency
        effect
    */
    
    m_player = SpawnPlayer();
    m_octogon = SpawnEntity(Vector2(100.f, 100.f), Vector2(3.f, 6.f), 32.f, 8, sf::Color::Red, sf::Color::White);
    m_square = SpawnEntity(Vector2(100.f, 100.f), Vector2(6.f, 3.f), 64.f, 4, sf::Color::Green, sf::Color::White);
      
}

void PlayableRelicApp::OnUpdate()
{
    static float playerAccel = 1.f;
    static float maxPlayerSpeed = 8.f;

    // Handle player movement
    if (Input::IsKeyPressed(Key::A))
        m_player->transform->velocity.x -= playerAccel;
    if (Input::IsKeyPressed(Key::D))
        m_player->transform->velocity.x += playerAccel;
    if (Input::IsKeyPressed(Key::W))
        m_player->transform->velocity.y -= playerAccel;
    if (Input::IsKeyPressed(Key::S))
        m_player->transform->velocity.y += playerAccel;

    // If the user clicks, spawn a bullet
    if (Input::IsMouseButtonPressed(sf::Mouse::Button::Left))
        SpawnBullet(m_player, Input::GetMousePosition(*GetNativeWindow()));

    // If the user isn't pressing any keys, slow the player down to stop
    if (!Input::IsKeyPressed(Key::W) && !Input::IsKeyPressed(Key::A) && !Input::IsKeyPressed(Key::S) && !Input::IsKeyPressed(Key::D))
    {
        if (m_player->GetXVel() > 0.f)
            m_player->transform->velocity.x -= 1.f;
        else if (m_player->GetXVel() < 0.f)
            m_player->transform->velocity.x += 1.f;
    
        if (m_player->GetYVel() > 0.f)
            m_player->transform->velocity.y -= 1.f;
        else if (m_player->GetYVel() < 0.f)
            m_player->transform->velocity.y += 1.f; 
    }

    // Cap the player's X velocity
    if (abs(m_player->GetXVel()) > maxPlayerSpeed)
    {
        if (m_player->GetXVel() > 0.f)
            m_player->transform->velocity.x = maxPlayerSpeed;
        else if (m_player->GetXVel() < 0.f)
            m_player->transform->velocity.x = -maxPlayerSpeed;
    }
    
    // Cap the player's Y velocity
    if (abs(m_player->GetYVel()) > maxPlayerSpeed)
    {
        if (m_player->GetYVel() > 0.f)
            m_player->transform->velocity.y = maxPlayerSpeed;
        else if (m_player->GetYVel() < 0.f)
            m_player->transform->velocity.y = -maxPlayerSpeed;
    }

    //RL_TRACE("player velocity: <{}, {}>", m_player->GetXVel(), m_player->GetYVel());

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
        if (e->GetTag() == "player")
            e->transform->angle -= 1.f;
        else
            e->transform->angle += 1.f;
        
        // If the angle goes above 360, set it back to 0
        if (e->transform->angle > 360.f)
            e->transform->angle = 0.f;
        
        // If the angle goes below 0, set it back to 360
        if (e->transform->angle < 0.f)
            e->transform->angle = 360.f;
        
        // Set the entity's actual shape rotation at its transform's rotation
        e->shape->circle.setRotation(e->GetAngle());
        
        // Draw every entity's shape
        Draw(e->shape->circle);
    }
}

std::shared_ptr<Entity> PlayableRelicApp::SpawnPlayer()
{
    /* 
        Create the player entity and give it a tag of 'player',
        then set the components for the player, and finally return
        the new entity
    */

    std::shared_ptr<Entity> entity = AddEntity("player");
    entity->transform = std::make_shared<Transform>(Vector2(200.f, 500.f), Vector2(), 0.f);
    entity->shape = std::make_shared<Shape>(32.f, 3, sf::Color::Blue, sf::Color::White, 4.f);
    entity->collision = std::make_shared<Collision>(32.f);

    return entity;   
}

std::shared_ptr<Entity> PlayableRelicApp::SpawnEntity(const Vector2& position, const Vector2& velocity, 
                                                        float radius, int points, 
                                                        const sf::Color& fill, const sf::Color& outline)
{
    /* 
        Create an entity and give it a tag of 'object',
        then set the components for the entity, and finally return
        the new entity
    */

    std::shared_ptr<Entity> entity = AddEntity("object");
    entity->transform = std::make_shared<Transform>(position, velocity, 0.f);
    entity->shape = std::make_shared<Shape>(radius, points, fill, outline, 4.f);
    entity->collision = std::make_shared<Collision>(radius);

    return entity;   
}

void PlayableRelicApp::SpawnBullet(std::shared_ptr<Relic::Entity> entity, const Vector2& target)
{
    /* 
        Create a bullet entity, which travels towards
        the target parameter; then give the entity
        its components
    */

    std::shared_ptr<Entity> bullet = AddEntity("bullet");
    bullet->transform = std::make_shared<Relic::Transform>(target, Vector2(0.f, 0.f), 0.f);
    bullet->shape = std::make_shared<Relic::Shape>(10, 8, sf::Color::White, sf::Color::Blue, 2.f);
}


Relic::Application* Relic::CreateApplication()
{
    /*
        Create an instance of your application,
        call the OnStart() method for it, then
        return the instance to the application
    */

    WindowData properties = WindowData();
    properties.title = "Playable Relic App";
    properties.width = 1024;
    properties.height = 576;

    PlayableRelicApp* game = new PlayableRelicApp(properties);
    game->OnStart();
    return game; 
}
