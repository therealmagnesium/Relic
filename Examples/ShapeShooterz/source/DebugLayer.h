#pragma once
#include <Relic/Core/Layer.h>
#include <Relic/Entity/Entity.h>

struct IntInfo;
struct FloatInfo;
class GameScene;

// Make a UI layer that inherits from Relic::Layer
class DebugLayer : public Relic::Layer 
{
public:
    DebugLayer(GameScene* scene);
    ~DebugLayer(); 

    /* OnUpdate()
     *      - [REQUIRED]
     *      - Called once per frame
     *      - Used for:
     *          - Rendering imgui windows
     *          - Checking for imgui events
     */
    void OnUpdate() override;
 
    // Displays information about an entity 
    void AddEntityInfo(std::shared_ptr<Relic::Entity> entity);
    
    // Displays an integer slider given min and max values 
    void AddIntInfo(int* input, const char* label, int min = 0, int max = 100);
    
    // Displays a float slider given min and max values 
    void AddFloatInfo(float* input, const char* label, float min = 0.f, float max = 100.f);
    
    // Clears all data in the debug layer 
    void ClearAllInfo();

private:
    std::vector<IntInfo> m_intData;
    std::vector<FloatInfo> m_floatData;
    std::vector<std::shared_ptr<Relic::Entity>> m_entities;
    GameScene* m_gameScene;
};
