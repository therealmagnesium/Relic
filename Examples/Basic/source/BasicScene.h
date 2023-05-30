#pragma once
#include <Relic.h>

using namespace Relic;

class BasicScene : public Scene
{
public:
    BasicScene(Application* app);

    void OnUpdate() override;
};
