#pragma once
#include <Relic/Entity/Entity.h>

class GameScene;

class Player
{
public:
    Player(GameScene* scene);
    ~Player(); 

    // Handles player movement and shooting
    void Update(); 
    
    // Constrains the player in bounds
    void Constrain();
    
    // Resets member variables to default values
    void Reset();
    
    // Sends any info we want about the player to the debug layer 
    void SendDebugData();

    inline bool IsDead() const { return m_dead; }
    inline std::shared_ptr<Relic::Entity> GetEntity() const { return m_entity; }

    inline void Die() { m_dead = true; }
    inline void SetMaxShootTime(uint8_t time) { m_maxShootTime = time; }

private: 
    void HandleMovement();
    void HandleShooting();

private:
    bool m_dead = false;
    float m_acceleration = 25.f;
    float m_maxSpeed = 350.f;
    uint8_t m_shootTime = 0;
    uint8_t m_maxShootTime = 16;

    GameScene* m_scene = nullptr;
    std::shared_ptr<Relic::Entity> m_entity;
};
