#pragma once
#include <Relic.h>

using namespace Relic;

class GameScene;

class DebugLayer : public Relic::Layer 
{
public:
    DebugLayer(GameScene* scene);
    ~DebugLayer(); 

    void OnUpdate(float dt) override;

    void AddEntityInfo(std::shared_ptr<Entity> entity);
    void ClearAllInfo();

private:
    EntityVec m_entities;
    GameScene* m_gameScene;
};
