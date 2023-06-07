#include "BasicScene.h"
#include <Relic/Core/EntryPoint.h>

// Create an application class that inherits from Relic::Application
class BasicApp : public Relic::Application
{
public:
    BasicApp()
    {
        // Set the startup scene to the scene titled basic
        ChangeScene("basic", std::make_shared<BasicScene>(this), false);
    }
};

/* [REQUIRED] Must define Relic::CreateApplication() and return the
 * instance of your application*/ 
Relic::Application* Relic::CreateApplication()
{
    BasicApp* app = new BasicApp();
    return app;
}
