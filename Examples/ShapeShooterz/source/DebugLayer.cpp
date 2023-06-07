#include "DebugLayer.h"
#include <imgui.h>

DebugLayer::DebugLayer() :
    Layer()
{

}

DebugLayer::~DebugLayer()
{

}

void DebugLayer::OnAttach()
{

}

void DebugLayer::OnDetach()
{

}

void DebugLayer::OnUpdate(float dt)
{
    ImGui::Begin("Hello World");
    ImGui::Button("Test");
    ImGui::End();

    ImGui::ShowDemoWindow();
}
