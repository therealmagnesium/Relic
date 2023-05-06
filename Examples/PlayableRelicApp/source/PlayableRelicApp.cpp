#include "PlayableRelicApp.h"
#include "Relic/Entity/Components.h"
#define MAX_SHOOT_TIME 16
#define ENEMY_POS_OFFSET 200
#define MIN_ENEMY_SPAWN_TIME 25
#define DEC_ENEMY_SPAWN_TIME 500

PlayableRelicApp::PlayableRelicApp() :
    m_score(0), m_shootTime(0), m_enemySpawnTime(51), m_lastEnemySpawnTime(0), m_currentFrame(0)
{
    srand(time(NULL));
}

void PlayableRelicApp::OnStart()
{
    // Log the app has started
    RL_TRACE("Playable Relic App has started!");
    
    /*
        Initialize the player and load the
        configuration file from 'data/settings.cfg'
    */
    
    m_player = SpawnPlayer();    
}

void PlayableRelicApp::OnUpdate()
{
    // If ESC is pressed, close the game
    if (Input::IsKeyPressed(Key::Escape))
    {
        RL_TRACE("Score: {}", m_score);
        Close();
    }

    // Call the gameplay functions
    if (!m_playerDead)
    {
        HandlePlayerMovement();
        HandleShooting();
    }

    SpawnAllEnemies();
    HandleEnemyCollision();

    // Constrain the player into the window
    Constrain(m_player, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Decrease enemy spawn time and set the current frame
    if (m_enemySpawnTime > MIN_ENEMY_SPAWN_TIME)
    {
        if (m_currentFrame % DEC_ENEMY_SPAWN_TIME == 0)
            m_enemySpawnTime--;
    }

    // Move the entities based on their velocity and update their lifetime
    for (auto& e : GetAllEntities())
    {
        e->Move(e->GetXVel(), e->GetYVel());

        if (e->HasComponent<Lifetime>())
            if (e->GetComponent<Lifetime>().lifetime > 0)
                e->GetComponent<Lifetime>().lifetime--;
    }

    m_currentFrame++;
}

void PlayableRelicApp::OnRender()
{
    // For every entitiy in the entity manager...
    for (auto& e : GetAllEntities())
    {
        // Set the entity's actual shape position at its transform's position
        e->GetComponent<Shape>().circle.setPosition(e->GetX(), e->GetY());

        // Rotate the shape's angle
        if (e->GetTag() == "player")
            e->GetComponent<Transform>().angle -= 1.f;
        else
             e->GetComponent<Transform>().angle += 1.f;
        
        // If the angle goes above 360, set it back to 0
        if (e->GetComponent<Transform>().angle > 360.f)
            e->GetComponent<Transform>().angle = 0.f;
        
        // If the angle goes below 0, set it back to 360
        if (e->GetComponent<Transform>().angle < 0.f)
            e->GetComponent<Transform>().angle = 360.f;
        
        // Set the entity's actual shape rotation at its transform's rotation
        e->GetComponent<Shape>().circle.setRotation(e->GetAngle());
        
        // Draw every entity's shape
        if (e->IsInRenderView() && e->IsActive())
            Draw(e->GetComponent<Shape>().circle);
    }
}

void PlayableRelicApp::HandlePlayerMovement()
{
    static float playerAccel = 1.f;
    static float maxPlayerSpeed = 8.f;

    // Get a direction on both axis to be multiplied by accelereation
    Vector2 input = Vector2((Input::IsKeyPressed(Key::D) - Input::IsKeyPressed(Key::A)), 
                            (Input::IsKeyPressed(Key::S) - Input::IsKeyPressed(Key::W)));
    float inputDist = GetMagnitude(input);
    if (inputDist > 0.f)
        input = input / inputDist;

    // Update the player's velocity
    m_player->GetComponent<Transform>().velocity.x += (playerAccel * input.x);
    m_player->GetComponent<Transform>().velocity.y += (playerAccel * input.y);

    // If the user isn't pressing any horizontal input keys, slow the player down on the x axis
    if (!Input::IsKeyPressed(Key::A) && !Input::IsKeyPressed(Key::D))
    {
        if (m_player->GetXVel() > 0.f)
            m_player->GetComponent<Transform>().velocity.x -= playerAccel;
        else if (m_player->GetXVel() < 0.f)
            m_player->GetComponent<Transform>().velocity.x += playerAccel;
    }
    
    // If the user isn't pressing any vertical input keys, slow the player down on the y axis
    if (!Input::IsKeyPressed(Key::W) && !Input::IsKeyPressed(Key::S))
    {
        if (m_player->GetYVel() > 0.f)
            m_player->GetComponent<Transform>().velocity.y -= playerAccel;
        else if (m_player->GetYVel() < 0.f)
            m_player->GetComponent<Transform>().velocity.y += playerAccel; 
    }

    // Cap the player's X velocity
    if (abs(m_player->GetXVel()) > maxPlayerSpeed)
        m_player->GetComponent<Transform>().velocity.x = (m_player->GetXVel() > 0.f)
                                        ? maxPlayerSpeed : -maxPlayerSpeed;
    
    // Cap the player's Y velocity
    if (abs(m_player->GetYVel()) > maxPlayerSpeed)
        m_player->GetComponent<Transform>().velocity.y = (m_player->GetYVel() > 0.f) 
                                        ? maxPlayerSpeed : -maxPlayerSpeed;

}

void PlayableRelicApp::HandleShooting()
{
    // Update shoot timer
    if (m_shootTime < MAX_SHOOT_TIME)
        m_shootTime++;

    // If the user clicks, spawn a bullet
    if (Input::IsMouseButtonPressed(sf::Mouse::Button::Left) && m_shootTime >= MAX_SHOOT_TIME)
    {
        SpawnBullet(m_player, Input::GetMousePosition(GetNativeWindow()), "player_bullet");
        m_shootTime = 0;
    }

}

void PlayableRelicApp::HandleEnemyCollision()
{
    // If the player's bullets collide...
    for (auto& b : GetAllEntities("player_bullet"))
    {
        for (auto& e : GetAllEntities("enemy"))
        {
            if (GetDistance(b->GetPosition(), e->GetPosition()) <= b->GetCollisionRadius() + e->GetCollisionRadius())
            {
                m_score++;
                b->Destroy();
                e->Destroy();
            }
        }

        // If bullets are not in render view, destroy them
        if (!b->IsInRenderView())
            b->Destroy();
    }

    for (auto& e: GetAllEntities("enemy"))
    {
        if (!m_playerDead && GetDistance(e->GetPosition(), m_player->GetPosition()) <= e->GetCollisionRadius() + m_player->GetCollisionRadius())
        {
            e->Destroy();
            m_player->Destroy();
            m_playerDead = true;
        }

        if (!e->IsInRenderView() && e->GetLifetime() == 0.f)
            e->Destroy();
    }
}

void PlayableRelicApp::SpawnAllEnemies()
{
    // Spawn an enemy over m_enemySpawnTime
    if (m_currentFrame - m_lastEnemySpawnTime == m_enemySpawnTime)
        SpawnEnemy();
}

std::shared_ptr<Entity> PlayableRelicApp::SpawnPlayer()
{
    /* 
        Create the player entity and give it a tag of 'player',
        then set the components for the player, and finally return
        the new entity.
    */

    std::shared_ptr<Entity> entity = AddEntity("player");
    entity->AddComponent<Transform>(Vector2(200.f, 500.f), Vector2(), 0.f);
    entity->AddComponent<Shape>(32.f, 3, sf::Color::Blue, sf::Color::White, 4.f);
    entity->AddComponent<Collision>(32.f);

    entity->GetComponent<Shape>().circle.setOrigin(entity->GetRadius(), entity->GetRadius());

    return entity;   
}

void PlayableRelicApp::SpawnEnemy()
{
    /* 
        Create an enemy and give it a tag of 'enemy',
        then get random values for the x and y position,
        and the amount of points. Then get random
        color values, after that set the components
        for the enemy. Then set the last enemy spawn
        time to the current frame.
    */

    std::shared_ptr<Entity> entity = AddEntity("enemy");

    Vector2 randPos = Vector2(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
    int points = rand() % 4 + 4;

    uint8_t r = rand() % 0xFF + 0x50;
    uint8_t g = rand() % 0xFF + 0x50;
    uint8_t b = rand() % 0xFF + 0x50;
    
    Vector2 velocity = m_player->GetPosition() - Vector2(randPos.x, randPos.y);
    Vector2 normalizedVel = Normalize(velocity);

    if (randPos.x < m_player->GetX())
        randPos.x -= rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    else if (randPos.x > m_player->GetX())
        randPos.x += rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    
    if (randPos.y < m_player->GetY())
        randPos.y -= rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    else if (randPos.y > m_player->GetY())
        randPos.y += rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;

    entity->AddComponent<Transform>(Vector2(randPos.x, randPos.y), (normalizedVel * points) / 1.2f, 0.f);
    entity->AddComponent<Shape>(32.f, points, sf::Color(r, g, b, 0xFF), sf::Color::White, 4.f);
    entity->AddComponent<Collision>(32.f);
    entity->AddComponent<Lifetime>(100);

    entity->GetComponent<Shape>().circle.setOrigin(32.f, 32.f);

    m_lastEnemySpawnTime = m_currentFrame;
}

void PlayableRelicApp::SpawnBullet(std::shared_ptr<Entity> entity, const Vector2& target, const std::string& tag)
{
    /* 
        Create a bullet entity, which travels towards
        the target parameter; then give the entity
        its components
    */

    float speed = 16.f;
    Vector2 aim = Input::GetMousePosition(GetNativeWindow()) - entity->GetPosition();
    Vector2 normalizedAim = Normalize(aim);

    std::shared_ptr<Entity> bullet = AddEntity(tag);
    bullet->AddComponent<Transform>(entity->GetPosition(), Vector2(normalizedAim.x*speed, normalizedAim.y*speed), 0.f);
    bullet->AddComponent<Shape>(10, 32, sf::Color::White, sf::Color::Blue, 2.f);
    bullet->AddComponent<Collision>(10.f);

    bullet->GetComponent<Shape>().circle.setOrigin(bullet->GetRadius(), bullet->GetRadius());
}

Relic::Application* Relic::CreateApplication()
{
    /*
        Create an instance of your application,
        call the OnStart() method for it, then
        return the instance to the application
    */

    PlayableRelicApp* game = new PlayableRelicApp();
    game->OnStart();
    return game; 
}
