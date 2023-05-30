#pragma once
#include <Relic.h>

using namespace Relic;

class MainMenuScene : public Scene
{
public:
    MainMenuScene(Application* app);

    void OnUpdate() override;
    void OnEnd() override;

    void CreateBackground();
    void SetupAndPlayAudio();
    void SpawnLogo();
    void SpawnStartText();
    void SpawnAllEntities();
    void RotateAllEntities();
    void SpawnEntity(const Vector2& pos);

private:
    std::shared_ptr<Entity> m_backgroundMusic;

};
