#include "MainMenuScene.h"
#include <Relic/Core/EntryPoint.h>

// Create an application class that inherits from Relic::Application
class ShapeShooterz : public Relic::Application
{
public:
    ShapeShooterz()
    {
        // Set the first scene shown to be the main menu scene
        ChangeScene("main_menu", std::make_shared<MainMenuScene>(this), false);  
        
    }

private:

};

/* [REQUIRED] Must define Relic::CreateApplication() and return the
 * instance of your application*/ 
Relic::Application* Relic::CreateApplication()
{
    ShapeShooterz* game = new ShapeShooterz();
    return game; 
}

