#include "Game.h"
#include "Relic/Entity/Components.h"

#define MAX_SHOOT_TIME 16
#define ENEMY_POS_OFFSET 200
#define MIN_ENEMY_SPAWN_TIME 20
#define DEC_ENEMY_SPAWN_TIME 500

static char scoreFormat[32];

ShapeShooterz::ShapeShooterz() :
    m_score(0), m_shootTime(0), m_enemySpawnTime(46), m_lastEnemySpawnTime(0)
{
    srand(time(NULL));
}

void ShapeShooterz::OnStart()
{
    // Log the app has started
    RL_TRACE("Playable Relic App has started!");
    
    //Initialize the assets pointer
    m_assets = GetAssets();

    m_background = CreateBackground();
    m_player = SpawnPlayer();    
    m_scoreText = SpawnScoreText();
    m_deathText = SpawnDeathText();

}

void ShapeShooterz::OnUpdate()
{
    // If ESC is pressed, close the game
    if (Input::IsKeyPressed(Key::Escape))
        Close();

    // Call the gameplay functions
    RotateAllEntities();
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
        if (Application::currentFrame % DEC_ENEMY_SPAWN_TIME == 0)
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

}

void ShapeShooterz::HandlePlayerMovement()
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

void ShapeShooterz::HandleShooting()
{
    // Update shoot timer
    if (m_shootTime < MAX_SHOOT_TIME)
        m_shootTime++;

    // If the user clicks, spawn a bullet
    if (Input::IsMouseButtonPressed(sf::Mouse::Button::Left) && m_shootTime >= MAX_SHOOT_TIME)
    {
        SpawnBullet(m_player, Vector2(), "player_bullet");
        m_shootTime = 0;
    }

}

void ShapeShooterz::HandleEnemyCollision()
{
    // If the player's bullets collide...
    for (auto& b : GetAllEntities("player_bullet"))
    {
        for (auto& e : GetAllEntities("enemy"))
        {
            if (GetDistance(b->GetPosition(), e->GetPosition()) <= b->GetCollisionRadius() + e->GetCollisionRadius())
            {
                AddScore(e->GetComponent<Shape>().circle.getPointCount());
                b->Destroy();
                e->Destroy();
            }
        }

        // If bullets are not in render view, destroy them
        if (!b->IsInRenderView(WINDOW_WIDTH, WINDOW_HEIGHT))
            b->Destroy();
    }

    for (auto& e: GetAllEntities("enemy"))
    {
        if (!m_playerDead && GetDistance(e->GetPosition(), m_player->GetPosition()) <= e->GetCollisionRadius() + m_player->GetCollisionRadius())
        {
            e->Destroy();
            m_player->Destroy();
            m_playerDead = true;
            m_deathText->Enable();
        }

        // If enemies are not in render view and their lifetime is 0, then destroy them
        if (!e->IsInRenderView(WINDOW_WIDTH, WINDOW_HEIGHT) && e->GetLifetime() == 0.f)
            e->Destroy();
    }
}

void ShapeShooterz::RotateAllEntities()
{
    for (auto& e : GetAllEntities())
    {
        // Rotate the shape's angle
        if (e->GetTag() == "player")
            e->GetComponent<Transform>().angle -= 1.f;
        else if (e->GetTag() == "ui" || e->GetTag() == "bg")
            e->GetComponent<Transform>().angle = 0.f;
        else
             e->GetComponent<Transform>().angle += 1.f;

        // If the angle goes above 360, set it back to 0
        if (e->GetComponent<Transform>().angle > 360.f)
            e->GetComponent<Transform>().angle = 0.f;
        
        // If the angle goes below 0, set it back to 360
        if (e->GetComponent<Transform>().angle < 0.f)
            e->GetComponent<Transform>().angle = 360.f; 
    }
}

void ShapeShooterz::AddScore(int score)
{
    m_score += score;
    sprintf(scoreFormat, "Score: %d", m_score);
    m_scoreText->GetComponent<Text>().text.setString(std::string(scoreFormat));    
}

std::shared_ptr<Entity> ShapeShooterz::CreateBackground()
{
    std::shared_ptr<Entity> entity = AddEntity("ui");
    entity->AddComponent<Transform>();
    entity->AddComponent<SpriteRenderer>(m_assets->GetTexture("background"));
    return entity;
}

std::shared_ptr<Entity> ShapeShooterz::SpawnScoreText()
{
    // Initialize the score format
    sprintf(scoreFormat, "Score: %d", m_score);
    
    std::shared_ptr<Entity> entity = AddEntity("ui");
    entity->AddComponent<Transform>(Vector2(20.f, 20.f));
    entity->AddComponent<Text>(m_assets->GetFont("main"), scoreFormat, 36);
    
    return entity;
}

std::shared_ptr<Entity> ShapeShooterz::SpawnDeathText()
{
    std::shared_ptr<Entity> entity = AddEntity("ui");
    entity->AddComponent<Transform>(Vector2(WINDOW_WIDTH - 600.f, WINDOW_HEIGHT - 200.f));
    entity->AddComponent<Text>(m_assets->GetFont("main"), "You died", 40);
    entity->Disable();

    return entity;
}

std::shared_ptr<Entity> ShapeShooterz::SpawnPlayer()
{
    /* 
       Create the player entity and give it a tag of 'player',
       then set the components for the player, and finally return
       the new entity.
       */

    std::shared_ptr<Entity> entity = AddEntity("player");
    entity->AddComponent<Transform>(Vector2(200.f, 500.f), Vector2(), 0.f);
    entity->AddComponent<Shape>(32.f, 3, 0x0000FFFF, 0xFFFFFFFF, 4.f);
    entity->AddComponent<Collision>(32.f);

    entity->GetComponent<Shape>().circle.setOrigin(entity->GetRadius(), entity->GetRadius());

    return entity;   
}

void ShapeShooterz::SpawnAllEnemies()
{
    // Spawn an enemy over m_enemySpawnTime
    if (Application::currentFrame - m_lastEnemySpawnTime == m_enemySpawnTime)
        SpawnEnemy();
}


void ShapeShooterz::SpawnEnemy()
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
    uint32_t color = 0xFF | (b << 8) | (g << 16) | (r << 24);

    if (randPos.x < m_player->GetX())
        randPos.x -= rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    else if (randPos.x > m_player->GetX())
        randPos.x += rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    
    if (randPos.y < m_player->GetY())
        randPos.y -= rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    else if (randPos.y > m_player->GetY())
        randPos.y += rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;

    Vector2 velocity = m_player->GetPosition() - Vector2(randPos.x, randPos.y);
    Vector2 normalizedVel = Normalize(velocity);

    entity->AddComponent<Transform>(Vector2(randPos.x, randPos.y), (normalizedVel * points), 0.f);
    entity->AddComponent<Shape>(32.f, points, color, 0xFFFFFFFF, 4.f);
    entity->AddComponent<Collision>(32.f);
    entity->AddComponent<Lifetime>(300);

    entity->GetComponent<Shape>().circle.setOrigin(entity->GetRadius(), entity->GetRadius());

    m_lastEnemySpawnTime = currentFrame;
}

void ShapeShooterz::SpawnBullet(std::shared_ptr<Entity> entity, const Vector2& offset, const std::string& tag)
{
    /* 
        Create a bullet entity, which travels towards
        the target parameter; then give the entity
        its components
    */

    float speed = 16.f;
    Vector2 aim = (Input::GetMousePosition(GetNativeWindow()) - entity->GetPosition()) + offset;
    Vector2 normalizedAim = Normalize(aim);

    std::shared_ptr<Entity> bullet = AddEntity(tag);
    bullet->AddComponent<Transform>(entity->GetPosition(), Vector2(normalizedAim.x*speed, normalizedAim.y*speed), 0.f);
    bullet->AddComponent<Shape>(10, 32, 0xFFFFFFFF, 0x0000FFFF, 2.f);
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

    ShapeShooterz* game = new ShapeShooterz();
    game->OnStart();
    return game; 
}
