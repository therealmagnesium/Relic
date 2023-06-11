#pragma once
#include "States.h"
#include "DebugLayer.h"
#include "Player.h"

#include <Relic/Core/Scene.h>
#include <Relic/Core/Application.h>

using namespace Relic;

class DebugLayer;

// Make a playable scene class that inherits from Relic::Scene
class GameScene : public Scene 
{
public:
    friend class DebugLayer;
    friend class Player;

    GameScene(Application* app);

    /* OnUpdate()
     *      - [REQUIRED]
     *      - Called once per frame
     *      - Used for:
     *          - Collisions / physics
     *          - Movement
     */
    void OnUpdate() override;

    /* OnEnd()
     *      - [NOT REQUIRED]
     *      - Called when the current scene is switched
     *      - Used for:
     *          - Cleaning up memory
     *          - Reseting entities
     */
    void OnEnd() override;

    inline Application* GetApp() const { return m_app; }
    
    inline void PlayMusic() { m_backgroundMusic->GetComponent<AudioSource>().audio.Play(); }
    inline void StopMusic() { m_backgroundMusic->GetComponent<AudioSource>().audio.Stop(); }

private: 
    // A function to handle the debug menu
    void HandleDebugMenu();

    // A function to reset everything when the player dies
    void Reset();

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
    uint32_t m_score = 0;
    uint32_t m_highScore = 0;

    uint32_t m_enemySpawnTime = 50;
    int m_lastEnemySpawnTime = 0;

    PowerUpState m_powerUpState;
    DebugLayer* m_debugLayer;

    std::shared_ptr<Assets> m_assets;
    
    std::shared_ptr<Player> m_player;
    std::shared_ptr<Entity> m_scoreText;
    std::shared_ptr<Entity> m_highScoreText; 
    std::shared_ptr<Entity> m_deathText;
    std::shared_ptr<Entity> m_powerUpText;
    std::shared_ptr<Entity> m_backgroundMusic;
};
