#include "LoggingRelicApp.h"

LoggingRelicApp::LoggingRelicApp(const WindowData& props) :
    Application(props) 
{

}

void LoggingRelicApp::OnStart() 
{
    // Log example texts to the console (will not show in dist build)
    RL_TRACE("Relic trace example");
    RL_INFO("Relic info example");
    RL_WARN("Relic warn example");
    RL_ERROR("Relic error example");
    RL_CRITICAL("Relic critical example");
 
    // Create 3 vectors
    Relic::Vector2 v1(100.f, 100.f);
    Relic::Vector2 v2(200.f, 200.f);
    Relic::Vector2 v3 = v1 + v2;

    // Log the vectors to the console
    RL_TRACE("v1: {}, {}", v1.x, v1.y);        
    RL_TRACE("v2: {}, {}", v2.x, v2.y);        
    RL_TRACE("v1 + v2 = {}, {}", v3.x, v3.y); 
}

void LoggingRelicApp::OnUpdate() 
{
    RL_TRACE("{}, {}", Input::GetMouseX(GetNativeWindow()), Input::GetMouseY(GetNativeWindow()));
}

void LoggingRelicApp::OnRender() 
{

}

Relic::Application* Relic::CreateApplication()
{
    /*
        Create an instance of your application,
        call the OnStart() method for it, then
        return the instance to the application
    */
   
    WindowData properties = WindowData();
    properties.title = "Logging Relic App";
    properties.width = 1024;
    properties.height = 576;

    LoggingRelicApp* game = new LoggingRelicApp(properties);
    game->OnStart();
    return game; 
}
