#pragma once
#include <Relic.h>
#include "States.h"

using namespace Relic;

class DebugLayer;

// Make a playable scene class that inherits from Relic::Scene
class GameScene : public Scene 
{
public:
    GameScene(Application* app);

    /* OnUpdate()
     *      - [REQUIRED]
     *      - Called once per frame
     *      - Used for:
     *          - Collisions / physics
     *          - Movement
     */
    void OnUpdate(float dt) override;

    /* OnEnd()
     *      - [NOT REQUIRED]
     *      - Called when the current scene is switched
     *      - Used for:
     *          - Cleaning up memory
     *          - Reseting entities
     */
    void OnEnd() override;

    inline std::shared_ptr<Entity> GetPlayer() const { return m_player; }
    inline Application* GetApp() const { return m_app; }
    
    inline void PlayMusic() { m_backgroundMusic->GetComponent<AudioSource>().audio.Play(); }
    inline void StopMusic() { m_backgroundMusic->GetComponent<AudioSource>().audio.Stop(); }

private: 
    // A function to handle the debug menu
    void HandleDebugMenu();

    // A function to reset everything when the player dies
    void Reset();

    // A function to make sure the player won't go out of bounds
    void ConstrainPlayer();

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

    // A function to save the high score
    void SaveHighScore(int highScore);

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
    
    // A function to create the background
    void CreateBackground();

    // A function to decrease enemy spawn time
    void HandleEnemySpawnTime();

    // A function to play music
    std::shared_ptr<Entity> SetupAndPlayAudio();

    // A helper function to spawn the player
    std::shared_ptr<Entity> SpawnPlayer();


    // A function to spawn the score text
    std::shared_ptr<Entity> SpawnScoreText();

    // A function to spawn the high score text
    std::shared_ptr<Entity> SpawnHighScoreText();

    // A function to spawn the death text
    std::shared_ptr<Entity> SpawnDeathText();

    // A function to spawn the power up text
    std::shared_ptr<Entity> SpawnPowerUpText();

private:
    bool m_playerDead = false;
    uint32_t m_maxShootTime = 16;
    uint32_t m_shootTime = 0;
    
    int m_score = 0;
    int m_highScore = 0;

    uint32_t m_enemySpawnTime = 35;
    int m_lastEnemySpawnTime = 0;

    PowerUpState m_powerUpState;
    DebugLayer* m_debugLayer;

    std::shared_ptr<Assets> m_assets;
    
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_scoreText;
    std::shared_ptr<Entity> m_highScoreText; 
    std::shared_ptr<Entity> m_deathText;
    std::shared_ptr<Entity> m_powerUpText;
    std::shared_ptr<Entity> m_backgroundMusic;
};
