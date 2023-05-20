#include <Relic.h>
#include <memory>

using namespace Relic;

// Make an app class that inherits from Relic::Application
class ShapeShooterz : public Application
{
public:
    ShapeShooterz();

    /* OnStart()
     *      - [REQUIRED]
     *      - Called once, when the app is initialized
     *      - Used for initializing entities and other game objects
     */
    void OnStart() override;

    /* OnUpdate()
     *      - [REQUIRED]
     *      - Called once per frame
     *      - Used for:
     *              - Collisions / physics
     *              - Movement
     */
    void OnUpdate() override;

private:
    // A function to reset everything when the player dies
    void Reset();

    // A function to organize player movement code
    void HandlePlayerMovement();

    // A function to organize player shooting code
    void HandleShooting();

    // A function to organize enemy collision code
    void HandleEnemyCollision();

    // A function to organize all power up collision code
    void HandlePowerUpCollision();

    // A function to update power up active time
    void HandlePowerUpActiveTime();

    // A function to rotate all the entities
    void RotateAllEntities();

    // A function to update score text
    void AddScore(int score);

    // A function to spawn all the enemies
    void SpawnAllEnemies();

    // A function to spawn all the power ups
    void SpawnAllPowerUps();

    // A function to spawn enemies
    void SpawnEnemy();

    // A function to spawn power ups
    void SpawnPowerUp();

    // A function to spawn particles
    void SpawnParticles(int count, std::shared_ptr<Entity> entity);

    // A function to spawn bullets
    void SpawnBullet(std::shared_ptr<Entity> entity, const Vector2& offset, const std::string& tag);

    // A function to play music
    void SetupAndPlayAudio();

    // A helper function to spawn the player
    std::shared_ptr<Entity> SpawnPlayer();

    // A function to create the background
    std::shared_ptr<Entity> CreateBackground();

    // A functino to spawn the score text
    std::shared_ptr<Entity> SpawnScoreText();

    // A function to spawn the death text
    std::shared_ptr<Entity> SpawnDeathText();

    // A function to spawn the power up text
    std::shared_ptr<Entity> SpawnPowerUpText();

private:
    bool m_playerDead = false;
    uint32_t m_maxShootTime = 16;
    uint32_t m_shootTime = 0;
    
    int m_score = 0;
   
    uint32_t m_enemySpawnTime = 50;
    int m_lastEnemySpawnTime = 0;

    uint32_t m_powerUpActiveTime = 0; 
    int m_lastPowerUpSpawnTime = 0;

    std::shared_ptr<Assets> m_assets;
    
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_scoreText;
    std::shared_ptr<Entity> m_deathText;
    std::shared_ptr<Entity> m_powerUpText;
    std::shared_ptr<Entity> m_background;
};
