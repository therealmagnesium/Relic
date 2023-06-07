#pragma once
#include <Relic.h>

using namespace Relic;

class DebugLayer : public Relic::Layer 
{
public:
    DebugLayer();
    ~DebugLayer(); 

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float dt) override;
};
