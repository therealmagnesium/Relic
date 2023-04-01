#include <Relic.h>

class BasicRelicApp : public Relic::Application
{
public:
    void OnStart() override
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
    }

    void OnUpdate() override
    {

    }

    void OnRender() override
    {

    }

private:

};

class PlayableRelicApp : public Relic::Application
{
public:
    PlayableRelicApp(const Relic::ApplicationProperties& props) : Relic::Application(props)
    {

    }

    void OnStart() override
    {
        // Log the app has started
        RL_INFO("Playable Relic App has started successfully");

        // Initialize the entity manager
        m_entityManager = std::make_shared<Relic::EntityManager>();

        /*
            Initialize the scene's entities, note that
            setting the fill color to 0x00000000 gives transparency
            effect
        */
        m_octogon = SpawnEntity(Relic::Vector2(100.f, 100.f), Relic::Vector2(2.f, 4.f), 32.f, 8, sf::Color(0x00000000), sf::Color::Red);
        m_square = SpawnEntity(Relic::Vector2(100.f, 100.f), Relic::Vector2(4.f, 2.f), 64.f, 4, sf::Color(0x00000000), sf::Color::Green);
    }

    void OnUpdate() override
    {
        // Update the entity manager
        m_entityManager->Update();

        // Move the entities based on their velocity
        m_octogon->Move(m_octogon->GetXVel(), m_octogon->GetYVel());    
        m_square->Move(m_square->GetXVel(), m_square->GetYVel());

        for (auto& e : m_entityManager->GetEntities())
        {
            if (e->GetX() + e->GetRadius() > GetWindowWidth() || e->GetX() < e->GetRadius())
                e->transform->velocity.x *= -1;
            if (e->GetY() + e->GetRadius() > GetWindowHeight() || e->GetY() < e->GetRadius())
                e->transform->velocity.y *= -1;
        }
    }

    void OnRender() override
    {
        // For every entitiy in the entity manager...
        for (auto& e : m_entityManager->GetEntities())
        {
            // Set the entity's actual shape position at its transform's position
            e->shape->circle.setPosition(e->GetX(), e->GetY());

            // Rotate the shape's angle
            e->transform->angle += 1.f;

            // If the angle goes above 360, set it back to 0
            if (e->transform->angle > 360.f)
                e->transform->angle = 0.f;

            // Set the entity's actual shape rotation at its transform's rotation
            e->shape->circle.setRotation(e->transform->angle);

            // Draw every entity's shape
            Draw(e->shape->circle);
        }
    }

private:
    // A small helper function to spawn entities
    std::shared_ptr<Relic::Entity> SpawnEntity(Relic::Vector2 position, Relic::Vector2 velocity, float radius, int points, const sf::Color& fill, const sf::Color& outline)
    {
        /* 
            Create an entity and give it a tag ov 'object',
            then set the components for the entity, and finally return
            the new entity
        */
        std::shared_ptr<Relic::Entity> entity = m_entityManager->AddEntity("object");
        entity->transform = std::make_shared<Relic::Tranform>(position, velocity, 0.f);
        entity->shape = std::make_shared<Relic::Shape>(radius, points, fill, outline, 4.f);
        return entity;   
    }

private:
    std::shared_ptr<Relic::EntityManager> m_entityManager;
    std::shared_ptr<Relic::Entity> m_octogon;
    std::shared_ptr<Relic::Entity> m_square;
};

// [REQUIRED] Must declare this function
Relic::Application* Relic::CreateApplication()
{
    /*
        Create an instance of your application,
        call the OnStart() method for it, then
        return the instance to the application
    */

    Relic::ApplicationProperties properties;
    properties.name = "Playable Relic App";
    properties.width = 1600;
    properties.height = 900;

    PlayableRelicApp* game = new PlayableRelicApp(properties);
    game->OnStart();
    return game;

}