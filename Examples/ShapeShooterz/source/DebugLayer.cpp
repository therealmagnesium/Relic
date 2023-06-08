#include "DebugLayer.h"
#include "GameScene.h"
#include <imgui.h>

DebugLayer::DebugLayer(GameScene* scene) :
    Layer(), m_gameScene(scene) 
{
     
}

DebugLayer::~DebugLayer()
{

}

void DebugLayer::OnUpdate(float dt)
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

    ImGui::Begin("Audio options");
    
    if (ImGui::Button("Play"))
        m_gameScene->PlayMusic();

    if (ImGui::Button("Stop"))
        m_gameScene->StopMusic();

    ImGui::End();
}

void DebugLayer::AddEntityInfo(std::shared_ptr<Entity> entity)
{ m_entities.emplace_back(entity); }

void DebugLayer::ClearAllInfo()
{ m_entities.clear(); }

