#include "Game.h"
#include "Relic/Core/Application.h"
#include "Relic/Core/KeyCodes.h"
#include "Relic/Core/Util.h"
#include "Relic/Entity/Components.h"

#include <SFML/System/Time.hpp>
#include <memory>
#include <SFML/Audio/Music.hpp>

#define ENEMY_POS_OFFSET 200
#define MIN_ENEMY_SPAWN_TIME 20
#define DEC_ENEMY_SPAWN_TIME 500
#define POWER_UP_SPAWN_TIME 1500
#define MAX_ACTIVE_POWER_UP_TIME 500

static char scoreFormat[32];
static bool hasPowerUp = false;

Relic::Application* Relic::CreateApplication()
{
    /* Create an instance of your application,
     * then call the OnStart() method for it. Finally,
     * return the instance to the application. */

    ShapeShooterz* game = new ShapeShooterz();
    game->OnStart();
    return game; 
}

ShapeShooterz::ShapeShooterz()
{
    srand(time(NULL));
}

void ShapeShooterz::OnStart()
{
    // Log the app has started
    RL_TRACE("Playable Relic App has started!");
    
    //Initialize the assets pointer
    m_assets = GetAssets();

    // Initialize the entities
    m_background = CreateBackground();
    m_player = SpawnPlayer();    
    m_scoreText = SpawnScoreText();
    m_deathText = SpawnDeathText();
    m_powerUpText = SpawnPowerUpText();

    SetupAndPlayAudio();
}

void ShapeShooterz::OnUpdate()
{
    // If ESC is pressed, close the game
    if (Input::IsKeyPressed(Key::Escape))
        Close();
    
    // Call the gameplay functions
    HandleEnemySpawnTime();
    RotateAllEntities();
    if (!m_playerDead)
    {
        SpawnAllEnemies();

        HandleEnemyCollision();
        HandlePowerUpCollision();
        
        HandleShooting();
        HandlePlayerMovement();
 
        SpawnAllPowerUps();
        HandlePowerUpActiveTime();
        
    }
    else
    {
        if (Input::IsKeyPressed(Key::Space))
            Reset();
    }

    for (auto& e : GetAllEntities("particle"))
    {
        // Destroy particles if needed
        if (e->GetComponent<Lifetime>().lifetime == 0)
            e->Destroy(); 
   
        // Set the fill and border color for the particles
        uint32_t fillColor = e->GetComponent<Shape>().circle.getFillColor().toInteger();
        uint32_t borderColor = e->GetComponent<Shape>().circle.getOutlineColor().toInteger();

        // Give the particles transparent effect
        e->GetComponent<Shape>().circle.setFillColor(sf::Color(ReplaceByte(fillColor, 0, e->GetComponent<Lifetime>().lifetime)));
        e->GetComponent<Shape>().circle.setOutlineColor(sf::Color(ReplaceByte(borderColor, 0, e->GetComponent<Lifetime>().lifetime)));
    }

    // Constrain the player into the window
    Constrain(m_player, WINDOW_WIDTH, WINDOW_HEIGHT); 

    // Move the entities based on their velocity and update their lifetime
    for (auto& e : GetAllEntities())
    {
        e->Move(e->GetXVel(), e->GetYVel());

        if (e->HasComponent<Lifetime>())
            if (e->GetComponent<Lifetime>().lifetime > 0)
                e->GetComponent<Lifetime>().lifetime--;
    }
}

void ShapeShooterz::Reset()
{
    // Destroy all the current enemies
    for (auto& entity : GetAllEntities("enemy"))
    {
        entity->Destroy();
        SpawnParticles(entity->GetPointCount(), entity);  
    }

    // Destroy all the power ups
    for (auto& pu : GetAllEntities("power_up"))
        pu->Destroy();

    // Reset genearal variables
    hasPowerUp = false;
    m_score = 0;
    m_lastPowerUpSpawnTime = Application::currentFrame;
    m_lastEnemySpawnTime = Application::currentFrame;
    m_powerUpActiveTime = 0;
    m_enemySpawnTime = 50;
 
    // Reset ui
    sprintf(scoreFormat, "Score: %d", m_score);
    m_scoreText->GetComponent<Text>().text.setString(scoreFormat);
    m_deathText->Disable(); 
    m_powerUpText->Disable();

    // Reset player related variables 
    m_player = SpawnPlayer(); 
    m_playerDead = false;
    m_shootTime = 0;
    m_maxShootTime = 16;
}

void ShapeShooterz::HandlePlayerMovement()
{
    static float playerAccel = 1.f;
    static float maxPlayerSpeed = 8.f;

    // Get a direction on both axis to be multiplied by accelereation
    Vector2 input = Vector2(Input::GetAxis("horizontal"), Input::GetAxis("vertical"));
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
    if (m_shootTime < m_maxShootTime)
        m_shootTime++;

    // If the user clicks, spawn a bullet
    if (Input::IsMouseButtonPressed(sf::Mouse::Button::Left) && m_shootTime >= m_maxShootTime)
    {
        SpawnBullet(m_player, Vector2(), "player_bullet");
        m_shootTime = 0;
    }
}

void ShapeShooterz::HandleEnemyCollision()
{
    // If the player's bullets collide with an enemy...
    for (auto& b : GetAllEntities("player_bullet"))
    {
        for (auto& e : GetAllEntities("enemy"))
        {
            if (GetDistance(b->GetPosition(), e->GetPosition()) <= b->GetCollisionRadius() + e->GetCollisionRadius())
            {
                AddScore(e->GetComponent<Shape>().circle.getPointCount());
                b->Destroy();
                e->Destroy();
                SpawnParticles(e->GetPointCount(), e);
            }
        }

        // If bullets are not in render view, destroy them
        if (!b->IsInRenderView(WINDOW_WIDTH, WINDOW_HEIGHT))
            b->Destroy();
    }

    // If an enemy collides with the player
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

void ShapeShooterz::HandlePowerUpCollision()
{
    // Handle when the player collides with a power up
    for (auto& pu : GetAllEntities("power_up"))
    {
        if (GetDistance(pu->GetPosition(), m_player->GetPosition()) <= pu->GetCollisionRadius() + m_player->GetCollisionRadius()) 
        {
            pu->Destroy();
            m_maxShootTime = 8; 
            hasPowerUp = true;
        }
    }
}

void ShapeShooterz::HandlePowerUpActiveTime()
{
    /* Handle the power up text showing and
     * handle how long the player's power up is
     * active */

    if (hasPowerUp)
    {
        m_powerUpText->Enable();

        if (m_powerUpActiveTime < MAX_ACTIVE_POWER_UP_TIME)
            m_powerUpActiveTime++;

        if (m_powerUpActiveTime >= MAX_ACTIVE_POWER_UP_TIME)
        {
            m_powerUpActiveTime = 0;
            m_maxShootTime = 16;
            hasPowerUp = false;
        }
    }
    else
        m_powerUpText->Disable();
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
    /* Increment the score, then set the 
     * score format, and then set the 
     * score text's text to be the score format */

    m_score += score;
    sprintf(scoreFormat, "Score: %d", m_score);
    m_scoreText->GetComponent<Text>().text.setString(std::string(scoreFormat));    
}


void ShapeShooterz::SpawnAllEnemies()
{
    RL_TRACE("[DEBUG] {} - {} = {}", Application::currentFrame, m_lastEnemySpawnTime, m_enemySpawnTime);

    // Spawn an enemy over m_enemySpawnTime
    if (Application::currentFrame - m_lastEnemySpawnTime == m_enemySpawnTime)
        SpawnEnemy();
}

void ShapeShooterz::SpawnAllPowerUps()
{
    // Spawn a power up over POWER_UP_SPAWN_TIME
    if (Application::currentFrame - m_lastPowerUpSpawnTime == POWER_UP_SPAWN_TIME)
        SpawnPowerUp();
}

void ShapeShooterz::SpawnEnemy()
{
    /* Create an enemy and give it a tag of 'enemy',
     * then get random values for the x and y position,
     * and the amount of points. Then get random
     * color values, after that set the components
     * for the enemy. Then set the last enemy spawn
     * time to the current frame. */

    std::shared_ptr<Entity> entity = AddEntity("enemy");

    Vector2 randPos = Vector2(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
    int points = rand() % 4 + 4;

    uint8_t r = rand() % 0xFF + 0x80;
    uint8_t g = rand() % 0xFF + 0x80;
    uint8_t b = rand() % 0xFF + 0x80;
    uint32_t color = 0xFF | (b << 8) | (g << 16) | (r << 24);

    if (randPos.x < m_player->GetX())
        randPos.x -= rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    else if (randPos.x > m_player->GetX())
        randPos.x += rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;

    if (randPos.y < m_player->GetY())
        randPos.y -= rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    else if (randPos.y > m_player->GetY())
        randPos.y += rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;

    Vector2 velocity = m_player->GetPosition() - randPos;
    Vector2 normalizedVel = Normalize(velocity);

    entity->AddComponent<Transform>(Vector2(randPos.x, randPos.y), (normalizedVel * points), 0.f);
    entity->AddComponent<Shape>(32.f, points, color, 0xFFFFFFFF, 4.f);
    entity->AddComponent<Collision>(32.f);
    entity->AddComponent<Lifetime>(100);

    entity->GetComponent<Shape>().circle.setOrigin(entity->GetRadius(), entity->GetRadius());

    m_lastEnemySpawnTime = Application::currentFrame;
}

void ShapeShooterz::SpawnPowerUp()
{
    /* Genearate a random position, then create an entity
     * with a transform and sprite renderer component. Then
     * set the properties for the sprite and
     * then we can set the last power up spawn time. */

    Vector2 position = Vector2(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);

    std::shared_ptr<Entity> powerup = AddEntity("power_up");
    powerup->AddComponent<Transform>(position);
    powerup->AddComponent<SpriteRenderer>(m_assets->GetTexture("power_up"), position);  
     
    auto& sr = powerup->GetComponent<SpriteRenderer>();
    
    Vector2 origin = Vector2(sr.sprite.GetSize().x / 2, sr.sprite.GetSize().y / 2);
    sr.sprite.SetOrigin(origin.x, origin.y);
    sr.sprite.SetScale(2.f, 2.f);

    m_lastPowerUpSpawnTime = Application::currentFrame;
}

void ShapeShooterz::SpawnParticles(int count, std::shared_ptr<Entity> entity)
{
    /* For however many particles we want to spawn, send the particle
     * to a random location. Give the particles a transform, shape,
     * and lifetime component. */

    float speed = 4.f;

    for (int i = 0; i < count; i++)
    {
        Vector2 targetPos = Vector2(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
        Vector2 velocity = targetPos - entity->GetPosition();
        Vector2 normalizedVel = Normalize(velocity); 

        std::shared_ptr<Entity> particle = AddEntity("particle");
        particle->AddComponent<Transform>(entity->GetPosition(), normalizedVel * speed);
        particle->AddComponent<Shape>(28.f, entity->GetPointCount(), entity->GetFillColor(), entity->GetBorderColor(), 4.f);
        particle->AddComponent<Lifetime>(100);
    }
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

void ShapeShooterz::SetupAndPlayAudio()
{
    /* Create an entity to play background music, 
     * and give it an AudioSource component. Then we can set 
     * the start offset and then finally play the music. */

    std::shared_ptr<Entity> backgroundMusic = AddEntity("music");
    backgroundMusic->AddComponent<AudioSource>(m_assets->GetMusicPath("main"));
    backgroundMusic->GetComponent<AudioSource>().audio.SetStartOffset(16.f);
    backgroundMusic->GetComponent<AudioSource>().audio.Play();
}

void ShapeShooterz::HandleEnemySpawnTime()
{
    // Decrease enemy spawn time
    if (m_enemySpawnTime > MIN_ENEMY_SPAWN_TIME)
    {
        if (Application::currentFrame % DEC_ENEMY_SPAWN_TIME == 0)
            m_enemySpawnTime--;
    }
}

std::shared_ptr<Entity> ShapeShooterz::SpawnPlayer()
{
    /* Create the player entity and give it a tag of 'player',
     * then set the components for the player, and finally return
     * the new entity. */
     

    std::shared_ptr<Entity> entity = AddEntity("player");
    entity->AddComponent<Transform>(Vector2(WINDOW_WIDTH /2.f, WINDOW_HEIGHT / 2.f), Vector2(), 0.f);
    entity->AddComponent<Shape>(32.f, 3, 0x0000FFFF, 0xFFFFFFFF, 4.f);
    entity->AddComponent<Collision>(32.f);

    entity->GetComponent<Shape>().circle.setOrigin(entity->GetRadius(), entity->GetRadius());

    return entity;   
}

std::shared_ptr<Entity> ShapeShooterz::CreateBackground()
{
    /* Create an entity with the tag 'ui', then add a
     * transform and sprite renderer component. Finally
     * return the entity. */

    std::shared_ptr<Entity> entity = AddEntity("ui");
    entity->AddComponent<Transform>();
    entity->AddComponent<SpriteRenderer>(m_assets->GetTexture("background"));
    return entity;
}

std::shared_ptr<Entity> ShapeShooterz::SpawnScoreText()
{
    // Initialize the score format
    sprintf(scoreFormat, "Score: %d", m_score);
    
    /* Create an entity with the tag 'ui', then add a
     * transform and a text component. Finally return
     * the entity. */
    
    std::shared_ptr<Entity> entity = AddEntity("ui");
    entity->AddComponent<Transform>(Vector2(20.f, 20.f));
    entity->AddComponent<Text>(m_assets->GetFont("main"), scoreFormat, 36);
    
    return entity;
}

std::shared_ptr<Entity> ShapeShooterz::SpawnDeathText()
{
    /* Create an entity with the tag 'ui', then add a
     * transform and a text component. Afterwards,
     * disable the entity, then finally return it. */

    std::shared_ptr<Entity> entity = AddEntity("ui");
    entity->AddComponent<Transform>(Vector2(WINDOW_WIDTH / 2.f - 300.f, WINDOW_HEIGHT / 2.f));
    entity->AddComponent<Text>(m_assets->GetFont("main"), "You died\nPress space to restart", 50);
    entity->Disable();

    return entity;
}

std::shared_ptr<Entity> ShapeShooterz::SpawnPowerUpText()
{
    /* Create an entity with the tag 'ui', then add a
     * transform and a text component. Afterwards,
     * disable the entity, then finally return it. */

    std::shared_ptr<Entity> entity = AddEntity("ui");
    entity->AddComponent<Transform>(Vector2(20.f, WINDOW_HEIGHT - 50.f));
    entity->AddComponent<Text>(m_assets->GetFont("main"), "Faster shooting", 36);
    entity->Disable();

    return entity;
}
