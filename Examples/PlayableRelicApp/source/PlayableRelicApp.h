#include <Relic.h>

using namespace Relic;

// Make an app class that inherits from Relic::Application
class PlayableRelicApp : public Application
{
public:
    PlayableRelicApp();

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

    /* OnRender()
     *      - [REQUIRED]
     *      - Called once per frame, after OnUpdate()
     *      - Used for:
     *              - Rendering entities
     *              - Dynamic graphic properties
     */
    void OnRender() override;

private:
    // A function to organize player movement code
    void HandlePlayerMovement();

    // A function to organize player shooting code
    void HandleShooting();

    // A function to organize enemy collision code
    void HandleEnemyCollision();

    // A function to spawn all the enemies
    void SpawnAllEnemies();

    // A helper function to spawn the player
    std::shared_ptr<Entity> SpawnPlayer();

    // A helper function to spawn enemies
    void SpawnEnemy();

    // A helper function to spawn bullets
    void SpawnBullet(std::shared_ptr<Entity> entity, const Vector2& target, const std::string& tag);


private:
    int m_shootTime;
    int m_enemySpawnTime;
    int m_lastEnemySpawnTime;
    int m_currentFrame;

    std::shared_ptr<Entity> m_player;
};
