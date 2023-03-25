#pragma once
#include "Application.h"

extern Relic::Application* Relic::CreateApplication();

int main(int argc, char* argv[])
{
    Relic::Application* app = Relic::CreateApplication();
    app->Run();
    delete app;
}