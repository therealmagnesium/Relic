#pragma once

extern Relic::Application* Relic::CreateApplication();

int main(int argc, char* argv[])
{
    Relic::Log::Init();

    Relic::Application* app = Relic::CreateApplication();
    app->Run();
    delete app;
}