#include <Relic.h>
#include <SDL2/SDL.h>

class Game : public Relic::Application
{
public:
    Game()
    {
        Relic::Vector2 v1(100.f, 100.f);
        Relic::Vector2 v2(200.f, 200.f);
        Relic::Vector2 v3 = v1 + v2;

        printf("v1: %f, %f\n", v1.x, v1.y);        
        printf("v2: %f, %f\n", v2.x, v2.y);        
        printf("v1 + v2: %f, %f\n", v3.x, v1.y);        
    }

    ~Game()
    {

    }

private:
    
};

Relic::Application* Relic::CreateApplication()
{
    return new Game();
}