#include <Relic.h>

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
    // A function to organize player movement code
    void HandlePlayerMovement();

    // A function to organize player shooting code
    void HandleShooting();

    // A function to organize enemy collision code
    void HandleEnemyCollision();

    // A function to rotate all the entities
    void RotateAllEntities();

    void AddScore(int score);

    // A function to spawn all the enemies
    void SpawnAllEnemies();

    // A helper function to spawn the player
    std::shared_ptr<Entity> SpawnPlayer();

    // A helper function to spawn enemies
    void SpawnEnemy();

    // A helper function to spawn bullets
    void SpawnBullet(std::shared_ptr<Entity> entity, const Vector2& target, const std::string& tag);

private:
    int m_score;
    int m_shootTime;
    int m_enemySpawnTime;
    int m_lastEnemySpawnTime;
    bool m_playerDead = false;

    std::shared_ptr<Assets> m_assets;
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_scoreText;
    std::shared_ptr<Entity> m_deathText;
};
