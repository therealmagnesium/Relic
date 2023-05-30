#include "MainMenuScene.h"
#include <Relic/Core/EntryPoint.h>


using namespace Relic;

class ShapeShooterz : public Application
{
public:
    ShapeShooterz()
    {
        ChangeScene("main_menu", std::make_shared<MainMenuScene>(this), false);  
    }

private:

};

Relic::Application* Relic::CreateApplication()
{
    /* Create an instance of your application,
     * then finally return the new instance. */

    ShapeShooterz* game = new ShapeShooterz();
    return game; 
}

