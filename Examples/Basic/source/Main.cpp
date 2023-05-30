#include "BasicScene.h"
#include <Relic/Core/EntryPoint.h>

class BasicApp : public Relic::Application
{
public:
    BasicApp()
    {
        ChangeScene("basic", std::make_shared<BasicScene>(this), false);
    }
};

Relic::Application* Relic::CreateApplication()
{
    BasicApp* app = new BasicApp();
    return app;
}
