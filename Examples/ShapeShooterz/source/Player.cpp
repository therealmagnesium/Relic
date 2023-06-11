#include "Player.h"
#include "GameScene.h"
#include <Relic/Core/Input.h>
#include <Relic/Core/Util.h>

Player::Player(GameScene* scene) :
    m_scene(scene)
{
    m_entity = m_scene->m_entityManager.AddEntity("player"); 
    m_entity->AddComponent<Transform>(Vector2(m_scene->m_app->GetWindowWidth()/2.f, 
                m_scene->m_app->GetWindowHeight() / 2.f), Vector2(), 0.f);
    m_entity->AddComponent<Shape>(32.f, 3, 0x0000FFFF, 0xFFFFFFFF, 4.f);
    m_entity->AddComponent<Collision>(32.f);

    m_entity->GetComponent<Shape>().shape.SetOrigin(m_entity->GetRadius(), m_entity->GetRadius());
    m_entity->DisableCulling();
}

Player::~Player()
{
     
}

void Player::Update()
{
    HandleShooting();
    HandleMovement();
}

void Player::HandleMovement()
{
    // Get a direction on both axis to be multiplied by accelereation
    Vector2 input = Vector2(Input::GetAxis("horizontal"), Input::GetAxis("vertical"));
    float inputDist = GetMagnitude(input);
    if (inputDist > 0.f)
        input = input / inputDist;

    // Update the player's velocity
    m_entity->GetComponent<Transform>().velocity.x += (m_acceleration * input.x);
    m_entity->GetComponent<Transform>().velocity.y += (m_acceleration * input.y);

    // If the user isn't pressing any horizontal input keys, slow the player down on the x axis
    if (!Input::IsKeyPressed(Key::A) && !Input::IsKeyPressed(Key::D))
    {
        if (m_entity->GetXVel() > 0.f)
            m_entity->GetComponent<Transform>().velocity.x -= m_acceleration;
        else if (m_entity->GetXVel() < 0.f)
            m_entity->GetComponent<Transform>().velocity.x += m_acceleration;
    }

    // If the user isn't pressing any vertical input keys, slow the player down on the y axis
    if (!Input::IsKeyPressed(Key::W) && !Input::IsKeyPressed(Key::S))
    {
        if (m_entity->GetYVel() > 0.f)
            m_entity->GetComponent<Transform>().velocity.y -= m_acceleration;
        else if (m_entity->GetYVel() < 0.f)
            m_entity->GetComponent<Transform>().velocity.y += m_acceleration; 
    }

    // Cap the player's X velocity
    if (abs(m_entity->GetXVel()) > m_maxSpeed)
        m_entity->GetComponent<Transform>().velocity.x = (m_entity->GetXVel() > 0.f)
            ? m_maxSpeed : -m_maxSpeed;

    // Cap the player's Y velocity
    if (abs(m_entity->GetYVel()) > m_maxSpeed)
        m_entity->GetComponent<Transform>().velocity.y = (m_entity->GetYVel() > 0.f) 
            ? m_maxSpeed : -m_maxSpeed;

}

void Player::HandleShooting()
{
    // Update shoot timer
    if (m_shootTime < m_maxShootTime)
        m_shootTime++;

    // If the user clicks, spawn a bullet
    if (Input::IsMouseButtonPressed(0) && m_shootTime >= m_maxShootTime)
    {
        if (m_scene->m_powerUpState.has)
        {
            switch (m_scene->m_powerUpState.type)
            {
                case 0:
                {
                    // Spawn a bullet which will have a faster maximum shoot time 
                    m_scene->SpawnBullet(m_entity, Vector2(), "player_bullet");
                    m_shootTime = 0;
                    break;
                }
                case 1:
                {
                    // Spawn three bullets which will be shot at normal pace
                    m_scene->SpawnBullet(m_entity, Vector2(), "player_bullet");
                    m_scene->SpawnBullet(m_entity, Vector2(0.f, -200.f), "player_bullet");
                    m_scene->SpawnBullet(m_entity, Vector2(0.f, 200.f), "player_bullet");
                    m_shootTime = 0;
                    break; 
                }
            }
        }
        else
        {
            // Spawn a single bullet at normal pace
            m_scene->SpawnBullet(m_entity, Vector2(), "player_bullet");
            m_shootTime = 0;
        }
    }

}

void Player::Constrain()
{
    // Restrict the player from moving out ouf bounds 
    if (m_entity->GetX() < m_entity->GetRadius())
        m_entity->GetComponent<Transform>().position.x = m_entity->GetRadius();
    if (m_entity->GetX() + m_entity->GetRadius() > m_scene->m_app->GetWindowWidth())
        m_entity->GetComponent<Transform>().position.x = m_scene->m_app->GetWindowWidth() - m_entity->GetRadius(); 

    if (m_entity->GetY() < m_entity->GetRadius())
        m_entity->GetComponent<Transform>().position.y = m_entity->GetRadius();
    if (m_entity->GetY() + m_entity->GetRadius() > m_scene->m_app->GetWindowHeight())
        m_entity->GetComponent<Transform>().position.y = m_scene->m_app->GetWindowHeight() - m_entity->GetRadius();

}

void Player::Reset()
{
    // Reset player related variables 
    m_entity->SetPosition(Vector2(m_scene->m_app->GetWindowWidth() /2.f, m_scene->m_app->GetWindowHeight() / 2.f)); 
    m_entity->SetVelocity(0.f, 0.f);  
    m_entity->Enable();
    m_dead = false;
    m_shootTime = 0;
    m_maxShootTime = 16;
}

void Player::SendDebugData()
{
    m_scene->m_debugLayer->AddEntityInfo(m_entity); 
    m_scene->m_debugLayer->AddFloatInfo(&m_acceleration, "Player acceleration", 0.f, 200.f);
    m_scene->m_debugLayer->AddFloatInfo(&m_maxSpeed, "Max player speed", 200.f, 500.f);
}
