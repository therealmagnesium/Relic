#include <Relic.h>
#include <SDL2/SDL.h>

class Game : public Relic::Application
{
public:
    void OnStart() override
    {
        RL_INFO("Game has started successfully");

        Relic::Vector2 v1(100.f, 100.f);
        Relic::Vector2 v2(200.f, 200.f);
        Relic::Vector2 v3 = v1 + v2;

        RL_TRACE("v1: {}, {}", v1.x, v1.y);        
        RL_TRACE("v2: {}, {}", v2.x, v2.y);        
        RL_TRACE("v1 + v2 = {}", v3.x);        
    }

    void OnUpdate() override
    {
        
    }

private:
    
};

Relic::Application* Relic::CreateApplication()
{
    Game* game = new Game();
    game->OnStart();
    return game;
}