#pragma once
#include <Relic.h>

using namespace Relic;

class MainMenuScene : public Scene
{
public:
    MainMenuScene(Application* app);

    /* OnUpdate()
     *      - [REQUIRED]
     *      - Called once per frame
     *      - Used for:
     *          - Collisions / physics
     *          - Movement
     */
    void OnUpdate() override;

    /* OnEnd()
     *      - [NOT REQUIRED]
     *      - Called when the current scene is switched
     *      - Used for:
     *          - Cleaning up memory
     *          - Reseting entities
     */
    void OnEnd() override;
    
    // A function to create the background image
    void CreateBackground();

    // A function to setup the background music
    void SetupAndPlayAudio();

    // [TEMP] A function to spawn the Relic logo
    void SpawnLogo();

    // A function to spawn the text to begin 
    void SpawnStartText();

    // A function to spawn the credit text 
    void SpawnCreditText();
    
    // A function to spawn every entity
    void SpawnAllEntities();

    // A function to rotate every entity clockwise
    void RotateAllEntities();

    // A function to spawn a single entity, given a position
    void SpawnEntity(const Vector2& pos);

private:
    std::shared_ptr<Entity> m_backgroundMusic;

};
