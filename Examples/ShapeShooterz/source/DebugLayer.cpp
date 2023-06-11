#include "DebugLayer.h"
#include "GameScene.h"
#include <imgui.h>

using namespace Relic;

struct FloatInfo
{
    std::string label = "default";
    float min = 0.f;
    float max = 0.f;
    float* buffer = nullptr;
};

struct IntInfo 
{
    std::string label = "default";
    int min = 0;
    int max = 0;
    int* buffer = nullptr;
};

DebugLayer::DebugLayer(GameScene* scene) :
    Layer(), m_gameScene(scene) 
{
     
}

DebugLayer::~DebugLayer()
{

}

void DebugLayer::OnUpdate()
{
    ImGui::Begin("Entities");
    for (std::shared_ptr<Entity> entity : m_entities)
    {
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Entity %d, %s", (int)entity->GetId(), entity->GetTag().c_str());
        ImGui::Text("Enabled: %d", entity->IsEnabled());
        ImGui::Text("Culling enabled: %d", entity->HasCullEnabled());

        if (entity->HasComponent<Transform>())
        {
            ImGui::Text("Position: (%f, %f)", entity->GetX(), entity->GetY());
            ImGui::Text("Velocity: <%f, %f>", entity->GetXVel(), entity->GetYVel());
            ImGui::Text("Angle: %f", entity->GetAngle());
        }
    }
    ImGui::End();

    ImGui::Begin("General settings");
    
    ImGui::Text("Current frame: %d", m_gameScene->m_currentFrame);
    ImGui::Text("Last enemy spawn frame: %d", m_gameScene->m_lastEnemySpawnTime);

    for (IntInfo data : m_intData)
        ImGui::SliderInt(data.label.c_str(), data.buffer, data.min, data.max);

    for (FloatInfo data : m_floatData)
        ImGui::SliderFloat(data.label.c_str(), data.buffer, data.min, data.max);

    ImGui::End();

    ImGui::Begin("Audio options");
    
    if (ImGui::Button("Play"))
        m_gameScene->PlayMusic();

    if (ImGui::Button("Stop"))
        m_gameScene->StopMusic();

    ImGui::End();
}

void DebugLayer::AddEntityInfo(std::shared_ptr<Entity> entity)
{ m_entities.emplace_back(entity); }

void DebugLayer::AddFloatInfo(float* input, const char* label, float min, float max)
{
    FloatInfo temp;
    temp.buffer = input;
    temp.label = label;
    temp.min = min;
    temp.max = max;

    m_floatData.emplace_back(temp);
}

void DebugLayer::AddIntInfo(int* input, const char* label, int min, int max)
{
    IntInfo temp;
    temp.buffer = input;
    temp.label = label;
    temp.min = min;
    temp.max = max;

    m_intData.emplace_back(temp);   
}

void DebugLayer::ClearAllInfo()
{ 
    m_intData.clear();
    m_floatData.clear();
    m_entities.clear(); 
}

