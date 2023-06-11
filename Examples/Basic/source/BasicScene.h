#pragma once
#include <Relic.h>

using namespace Relic;

class BasicScene : public Scene
{
public:
    BasicScene(Application* app);

    void OnUpdate() override;

private:
    std::shared_ptr<Entity> SpawnEntity(const Vector2& pos, uint32_t fill, uint32_t outline);

private:
    std::shared_ptr<Entity> m_blueHex;
    std::shared_ptr<Entity> m_greenHex;
    std::shared_ptr<Entity> m_redHex;
};
