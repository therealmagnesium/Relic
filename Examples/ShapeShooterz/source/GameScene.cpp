#include "GameScene.h"
#include "MainMenuScene.h"
#include "DebugLayer.h"

#define ENEMY_POS_OFFSET 200
#define MIN_ENEMY_SPAWN_TIME 20
#define DEC_ENEMY_SPAWN_TIME 500
#define POWER_UP_SPAWN_TIME 1500
#define MAX_ACTIVE_POWER_UP_TIME 500

static char scoreFormat[32];
static char highScoreFormat[32];

GameScene::GameScene(Application* app) :
    Scene(app)
{
    srand(time(NULL));
      
    // Log the app has started
    RL_TRACE("Playable Relic App has started!");

    // Set the high score 
    if (!IO::DoesFileExist("highscores.bin"))
        IO::WriteNumberToFile(0, "highscores.bin");   
    m_highScore = IO::ReadNumberFromFile("highscores.bin"); 

    //Initialize the assets pointer
    m_assets = m_app->GetAssets();

    // Setup the scene 
    CreateBackground();
    m_player = std::make_shared<Player>(this);    
    m_scoreText = SpawnScoreText();
    m_highScoreText = SpawnHighScoreText(); 
    m_deathText = SpawnDeathText();
    m_powerUpText = SpawnPowerUpText();
    m_backgroundMusic = SetupAndPlayAudio();
 
    // Debug menu stuff
    m_debugLayer = new DebugLayer(this);
    m_player->SendDebugData();  
    PushLayer(m_debugLayer);
}

void GameScene::OnUpdate()
{
    // If the debug layer is enabled, render it
    if (m_debugLayer->IsEnabled())
        m_debugLayer->OnUpdate();

    // If ESC is pressed, close the game
    if (Input::IsKeyPressed(Key::Escape))
        m_app->Close();

    // Switch back to the main menu scene if the backspace key is pressed
    if (Input::IsKeyPressed(Key::Backspace))
        m_app->ChangeScene("main_menu", std::make_shared<MainMenuScene>(m_app), true); 

    // Call the gameplay functions
    HandleEnemySpawnTime(); 
    SpawnAllEnemies();
    if (!m_player->IsDead())
    {
        m_player->Update(); 
        
        HandleEnemyCollision();
  
        SpawnAllPowerUps();
        HandlePowerUpCollision();
        HandlePowerUpActiveTime(); 
    }
    else
    {
        // Reset the game if the space key was pressed
        if (Input::IsKeyPressed(Key::Space))
            Reset(); 
    }
    RotateAllEntities();
    HandleDebugMenu();

    for (auto& e : m_entityManager.GetEntities("particle"))
    {
        // Destroy particles if needed
        if (e->GetComponent<Lifetime>().lifetime == 0)
            e->Destroy(); 
   
        // Set the fill and border color for the particles
        uint32_t fillColor = e->GetComponent<Shape>().shape.GetFillColor();
        uint32_t borderColor = e->GetComponent<Shape>().shape.GetOutlineColor();

        // Give the particles transparent effect
        e->GetComponent<Shape>().shape.SetFillColor(ReplaceByte(fillColor, 0, e->GetComponent<Lifetime>().lifetime));
        e->GetComponent<Shape>().shape.SetOutlineColor(ReplaceByte(borderColor, 0, e->GetComponent<Lifetime>().lifetime));
    }

    // Move the entities based on their velocity and update their lifetime
    for (auto& e : m_entityManager.GetEntities())
    {
        e->Move(e->GetXVel() * Application::deltaTime, e->GetYVel() * Application::deltaTime);

        if (e->HasComponent<Lifetime>() && e->GetComponent<Lifetime>().lifetime > 0)
        { 
            if (e->GetTag() == "particle")
                e->GetComponent<Lifetime>().lifetime -= 3;
            else
                e->GetComponent<Lifetime>().lifetime--; 
        } 
    }
    m_player->Constrain();
    
    m_currentFrame++;
}

void GameScene::OnEnd()
{
    // Stop the game music
    RL_INFO("Ending scene [{}]", m_app->GetCurrentScene());
    m_backgroundMusic->GetComponent<AudioSource>().audio.Stop(); 
}

void GameScene::HandleDebugMenu()
{
    // Set showDebugMenu if F3 is pressedc
    static bool showDebugMenu = false;
    if (Input::IsKeyTyped(Key::F3))
        showDebugMenu = !showDebugMenu;

    // Enable or disable the debug layer depending on showDebugMenu
    if (showDebugMenu)
        m_debugLayer->Enable();
    else
        m_debugLayer->Disbale();
}

void GameScene::Reset()
{ 
    // Destroy all the current enemies
    for (auto& entity : m_entityManager.GetEntities("enemy"))
    {
        entity->Destroy();
        SpawnParticles(entity->GetPointCount(), entity);  
    }

    // Destroy all the power ups
    for (auto& pu : m_entityManager.GetEntities("power_up"))
        pu->Destroy();

    // Set high score if a new record was set
    if (m_score > m_highScore)
        SaveHighScore(m_score);

    // Reset genearal variables
    m_powerUpState.has = false;
    m_powerUpState.shown = false; 
    m_powerUpState.type = 0; 
    m_score = 0;
    m_powerUpState.activeTime = 0;
    m_powerUpState.lastSpawnTime = m_currentFrame;
    m_enemySpawnTime = 50;
 
    // Reset ui
    sprintf(scoreFormat, "Score: %d", m_score);
    m_scoreText->GetComponent<Text>().text.SetMessage(scoreFormat);
    m_deathText->Disable(); 
    m_powerUpText->Disable();

    m_player->Reset();
}

void GameScene::HandleEnemyCollision()
{
    // If the player's bullets collide with an enemy...
    for (auto& b : m_entityManager.GetEntities("player_bullet"))
    {
        for (auto& e : m_entityManager.GetEntities("enemy"))
        {
            if (GetDistance(b->GetPosition(), e->GetPosition()) <= b->GetCollisionRadius() + e->GetCollisionRadius())
            {
                AddScore(e->GetComponent<Shape>().shape.GetPointCount());
                SpawnParticles(e->GetPointCount(), e);
                b->Destroy();
                e->Destroy();
            }
        }

        // If bullets are not in render view, destroy them
        if (!b->IsInRenderView(m_app->GetWindowWidth(), m_app->GetWindowHeight()))
            b->Destroy();
    }

    // If an enemy collides with the player
    for (auto& e: m_entityManager.GetEntities("enemy"))
    {
        if (GetDistance(e->GetPosition(), m_player->GetEntity()->GetPosition()) <= e->GetCollisionRadius() + m_player->GetEntity()->GetCollisionRadius())
        {
            e->Destroy();
            m_player->GetEntity()->Disable();
            m_player->Die(); 
            m_deathText->Enable();
        }

        // If enemies are not in render view and their lifetime is 0, then destroy them
        if (!e->IsInRenderView(m_app->GetWindowWidth(), m_app->GetWindowHeight()) && e->GetLifetime() == 0.f)
            e->Destroy();
    }
}

void GameScene::HandlePowerUpCollision()
{
    // Handle when the player collides with a power up
    for (auto& pu : m_entityManager.GetEntities("power_up"))
    {
        if (GetDistance(pu->GetPosition(), m_player->GetEntity()->GetPosition()) <= pu->GetCollisionRadius() + m_player->GetEntity()->GetCollisionRadius()) 
        {
            pu->Destroy();
            
            if (m_powerUpState.type == 0) 
                m_player->SetMaxShootTime(8); 
            
            m_powerUpState.has = true;
            m_powerUpState.shown = false; 
            m_powerUpState.lastSpawnTime = m_currentFrame; 
        }
    }
}

void GameScene::HandlePowerUpActiveTime()
{
    /* Handle the power up text showing and
     * handle how long the player's power up is
     * active */

    if (m_powerUpState.has)
    {
        m_powerUpText->GetComponent<Text>().text.SetMessage(m_powerUpState.text);
        m_powerUpText->Enable();

        if (m_powerUpState.activeTime < MAX_ACTIVE_POWER_UP_TIME)
            m_powerUpState.activeTime++;

        if (m_powerUpState.activeTime >= MAX_ACTIVE_POWER_UP_TIME)
        {
            m_powerUpState.activeTime = 0;
            m_player->SetMaxShootTime(16); 
            m_powerUpState.has = false;
            m_powerUpState.type = 0; 
        }
    }
    else
        m_powerUpText->Disable();
}

void GameScene::RotateAllEntities()
{
    float rotationSpeed = 2.f;

    for (auto& e : m_entityManager.GetEntities())
    {
        // Rotate the shape's angle
        if (e->GetTag() == "player")
            e->GetComponent<Transform>().angle -= rotationSpeed;
        else if (e->GetTag() == "ui" || e->GetTag() == "bg")
            e->GetComponent<Transform>().angle = 0.f;
        else if (e->GetTag() == "power_up")
            e->GetComponent<Transform>().angle++;
        else
             e->GetComponent<Transform>().angle += rotationSpeed;

        // If the angle goes above 360, set it back to 0
        if (e->GetComponent<Transform>().angle > 360.f)
            e->GetComponent<Transform>().angle = 0.f;
        
        // If the angle goes below 0, set it back to 360
        if (e->GetComponent<Transform>().angle < 0.f)
            e->GetComponent<Transform>().angle = 360.f; 
    }
}

void GameScene::AddScore(int score)
{
    /* Increment the score, then set the 
     * score format, and then set the 
     * score text's text to be the score format */

    m_score += score;
    sprintf(scoreFormat, "Score: %d", m_score);
    m_scoreText->GetComponent<Text>().text.SetMessage(std::string(scoreFormat));    
}

void GameScene::SaveHighScore(int highScore)
{
    m_highScore = highScore;
    IO::WriteNumberToFile(m_highScore, "highscores.bin");
    sprintf(highScoreFormat, "High score: %d", m_highScore);
    m_highScoreText->GetComponent<Text>().text.SetMessage(std::string(highScoreFormat));
}

void GameScene::SpawnAllEnemies()
{
    // Spawn an enemy over m_enemySpawnTime
    if (m_currentFrame - m_lastEnemySpawnTime == m_enemySpawnTime)
        SpawnEnemy();
}

void GameScene::SpawnAllPowerUps()
{
    // Spawn a power up over POWER_UP_SPAWN_TIME
    if (m_currentFrame - m_powerUpState.lastSpawnTime == POWER_UP_SPAWN_TIME)
        SpawnPowerUp();
}

void GameScene::SpawnEnemy()
{
    /* Create an enemy and give it a tag of 'enemy',
     * then get random values for the x and y position,
     * and the amount of points. Then get random
     * color values, after that set the components
     * for the enemy. Then set the last enemy spawn
     * time to the current frame. */

    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("enemy");

    static float speed = 80.f;
    
    int spawnSide = rand() % 4;
    int points = rand() % 4 + 4;
    Vector2 randPos = Vector2();

    switch (spawnSide)
    {
        case 0: // Left side
        {
            randPos = Vector2(-50.f, rand() % m_app->GetWindowHeight()); 
            break;
        }
        case 1: // Right side
        {
            randPos = Vector2(m_app->GetWindowWidth() + 50.f, rand() % m_app->GetWindowHeight()); 
            break;
        }
        case 2: // Top side
        {
            randPos = Vector2(rand() % m_app->GetWindowWidth(), -50.f); 
            break;
        }
        case 3: // Bottom side
        {
            randPos = Vector2(rand() % m_app->GetWindowWidth(), m_app->GetWindowHeight() + 50.f); 
            break;
        }
    }

    uint8_t r = rand() % 0xFF + 0x80;
    uint8_t g = rand() % 0xFF + 0x80;
    uint8_t b = rand() % 0xFF + 0x80;
    uint32_t color = 0xFF | (b << 8) | (g << 16) | (r << 24);

    if (randPos.x < m_player->GetEntity()->GetX())
        randPos.x -= rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    else if (randPos.x > m_player->GetEntity()->GetX())
        randPos.x += rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;

    if (randPos.y < m_player->GetEntity()->GetY())
        randPos.y -= rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;
    else if (randPos.y > m_player->GetEntity()->GetY())
        randPos.y += rand() % ENEMY_POS_OFFSET + ENEMY_POS_OFFSET;

    Vector2 velocity = m_player->GetEntity()->GetPosition() - randPos;
    Vector2 normalizedVel = Normalize(velocity);

    entity->AddComponent<Transform>(Vector2(randPos.x, randPos.y), (normalizedVel * points * speed), 0.f);
    entity->AddComponent<Shape>(32.f, points, color, 0xFFFFFFFF, 4.f);
    entity->AddComponent<Collision>(32.f);
    entity->AddComponent<Lifetime>(100);

    entity->GetComponent<Shape>().shape.SetOrigin(entity->GetRadius(), entity->GetRadius());

    m_lastEnemySpawnTime = m_currentFrame;
}

void GameScene::SpawnPowerUp()
{
    /* Genearate a random position, then create an entity
     * with a transform and an image depending on the current
     * power up type. Then set the properties for the sprite and
     * then set the last power up spawn time. */

    if (!m_powerUpState.has && !m_powerUpState.shown)
    {
        m_powerUpState.type = rand() % 2;

        Vector2 position = Vector2(rand() % m_app->GetWindowWidth(), rand() % m_app->GetWindowHeight());

        std::shared_ptr<Entity> powerup = m_entityManager.AddEntity("power_up");
        powerup->AddComponent<Transform>(position);

        switch (m_powerUpState.type)
        {
            case 0:
                {
                    m_powerUpState.text = "2x shooting speed";
                    powerup->AddComponent<SpriteRenderer>(m_assets->GetTexture("faster_shooting"), position);  
                    break;
                } 
            case 1:
                {
                    m_powerUpState.text = "Multiple bullets";
                    powerup->AddComponent<SpriteRenderer>(m_assets->GetTexture("multi_bullets"), position);  
                    break; 
                }}

        auto& sr = powerup->GetComponent<SpriteRenderer>();

        Vector2 origin = Vector2(sr.sprite.GetSize().x / 2, sr.sprite.GetSize().y / 2);
        sr.sprite.SetOrigin(origin.x, origin.y);
        sr.sprite.SetScale(4.f, 4.f);

        m_powerUpState.shown = true;
    }

    m_powerUpState.lastSpawnTime = m_currentFrame;
}

void GameScene::SpawnParticles(int count, std::shared_ptr<Entity> entity)
{
    /* For however many particles we want to spawn, send the particle
     * to a random location. Give the particles a transform, shape,
     * and lifetime component. */

    float speed = 125.f;

    for (int i = 0; i < count; i++)
    {
        Vector2 targetPos = Vector2(rand() % m_app->GetWindowWidth(), rand() % m_app->GetWindowHeight());
        Vector2 velocity = targetPos - entity->GetPosition();
        Vector2 normalizedVel = Normalize(velocity); 

        std::shared_ptr<Entity> particle = m_entityManager.AddEntity("particle");
        particle->AddComponent<Transform>(entity->GetPosition(), normalizedVel * speed);
        particle->AddComponent<Shape>(28.f, entity->GetPointCount(), entity->GetFillColor(), entity->GetBorderColor(), 4.f);
        particle->AddComponent<Lifetime>(150);
        
        particle->GetComponent<Shape>().shape.SetOrigin(particle->GetRadius(), particle->GetRadius());
    }
}

void GameScene::SpawnBullet(std::shared_ptr<Entity> entity, const Vector2& offset, const std::string& tag)
{
    /* 
       Create a bullet entity, which travels towards
       the target parameter; then give the entity
       its components
       */

    float speed = 1500.f;
    Vector2 aim = (Input::GetMousePosition(m_app->GetNativeWindow()) - entity->GetPosition()) + offset;
    Vector2 normalizedAim = Normalize(aim);

    std::shared_ptr<Entity> bullet = m_entityManager.AddEntity(tag);
    bullet->AddComponent<Transform>(entity->GetPosition(), Vector2(normalizedAim.x*speed, normalizedAim.y*speed), 0.f);
    bullet->AddComponent<Shape>(10, 32, 0xFFFFFFFF, 0x0000FFFF, 2.f);
    bullet->AddComponent<Collision>(10.f);

    bullet->GetComponent<Shape>().shape.SetOrigin(bullet->GetRadius(), bullet->GetRadius());
}

std::shared_ptr<Entity> GameScene::SetupAndPlayAudio()
{
    /* Create an entity to play background music, 
     * and give it an AudioSource component. Then we can set 
     * the start offset and then finally play the music. */

    std::shared_ptr<Entity> backgroundMusic = m_entityManager.AddEntity("music");
    backgroundMusic->AddComponent<AudioSource>(m_assets->GetMusicPath("main"));
    backgroundMusic->GetComponent<AudioSource>().audio.SetStartOffset(0.f);
    backgroundMusic->GetComponent<AudioSource>().audio.Play();

    return backgroundMusic;
}

void GameScene::HandleEnemySpawnTime()
{
    // Decrease enemy spawn time
    if (m_enemySpawnTime > MIN_ENEMY_SPAWN_TIME)
    {
        if (m_currentFrame % DEC_ENEMY_SPAWN_TIME == 0)
            m_enemySpawnTime--;
    }
}

std::shared_ptr<Entity> GameScene::SpawnPlayer()
{
    /* Create the player entity and give it a tag of 'player',
     * then set the components for the player, and finally return
     * the new entity. */
     

    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("player");
    entity->AddComponent<Transform>(Vector2(m_app->GetWindowWidth() /2.f, m_app->GetWindowHeight() / 2.f), Vector2(), 0.f);
    entity->AddComponent<Shape>(32.f, 3, 0x0000FFFF, 0xFFFFFFFF, 4.f);
    entity->AddComponent<Collision>(32.f);

    entity->GetComponent<Shape>().shape.SetOrigin(entity->GetRadius(), entity->GetRadius());
    entity->DisableCulling();

    return entity;   
}

void GameScene::CreateBackground()
{
    /* Create an entity with the tag 'ui', then add a
     * transform and sprite renderer component. Finally
     * return the entity. */

    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("bg");
    entity->AddComponent<Transform>();
    entity->AddComponent<SpriteRenderer>(m_assets->GetTexture("game_bg"));
    entity->GetComponent<SpriteRenderer>().sprite.SetScale(0.4f, 0.4f);
}

std::shared_ptr<Entity> GameScene::SpawnScoreText()
{
    // Initialize the score format
    sprintf(scoreFormat, "Score: %d", m_score);
    
    /* Create an entity with the tag 'ui', then add a
     * transform and a text component. Finally return
     * the entity. */
    
    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("ui");
    entity->AddComponent<Transform>(Vector2(20.f, 20.f));
    entity->AddComponent<Text>(m_assets->GetFont("main"), scoreFormat, 36);
    entity->DisableCulling(); 

    return entity;
}

std::shared_ptr<Entity> GameScene::SpawnHighScoreText()
{
    // Initialize high score format
    RL_TRACE("{}", m_highScore);
    sprintf(highScoreFormat, "High score: %d", m_highScore);

    /* Create an entity with the tag 'ui', then add a
     * transform and a text component. Finally return
     * the entity */

    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("ui");
    entity->AddComponent<Text>(m_assets->GetFont("main"), highScoreFormat, 36);  
    auto& text = entity->GetComponent<Text>().text;
    entity->AddComponent<Transform>(Vector2(m_app->GetWindowWidth() - text.GetWidth() * 1.5, text.GetHeight()));
    entity->DisableCulling();

    return entity;
}

std::shared_ptr<Entity> GameScene::SpawnDeathText()
{
    /* Create an entity with the tag 'ui', then add a
     * transform and a text component. Afterwards,
     * disable the entity, then finally return it. */

    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("ui");
    entity->AddComponent<Transform>(Vector2(m_app->GetWindowWidth() / 2.f - 300.f, m_app->GetWindowHeight() / 2.f));
    entity->AddComponent<Text>(m_assets->GetFont("main"), "You died\nPress space to restart", 50);
    entity->Disable();
    entity->DisableCulling();

    return entity;
}

std::shared_ptr<Entity> GameScene::SpawnPowerUpText()
{
    /* Create an entity with the tag 'ui', then add a
     * transform and a text component. Afterwards,
     * disable the entity, then finally return it. */

    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("ui");
    entity->AddComponent<Transform>(Vector2(20.f, m_app->GetWindowHeight() - 50.f));
    entity->AddComponent<Text>(m_assets->GetFont("main"), "None", 36);
    entity->Disable();
    entity->DisableCulling();

    return entity;
}
