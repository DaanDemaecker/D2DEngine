#include "ImGuiInfoComponent.h"
#include "TimeManager.h"


void D2D::ImGuiInfoComponent::SetCanvas(GameObject* pCanvas)
{
    m_pCanvas = pCanvas;
}

void D2D::ImGuiInfoComponent::OnGUI()
{
	CreateWindow();
}

void D2D::ImGuiInfoComponent::CreateWindow()
{
    if (m_ShowInfoWindow)
    {
        ImGui::Begin("Info", &m_ShowInfoWindow);

        ImGuiTreeNodeFlags mainFlags = ImGuiTreeNodeFlags_Framed;

        if (ImGui::TreeNodeEx("General Info", mainFlags))
        {
            std::string text = "FPS: " + std::to_string(TimeManager::GetInstance().GetFps());

            ImGui::Text(text.c_str());

            ImGui::TreePop();
        }

        if (ImGui::TreeNodeEx("Controls", mainFlags))
        {
            ImGui::Text("-Navigate menu    WASD/ZQSD/ARROW KEYS");
            ImGui::Text("-Select menu      SPACE");
            ImGui::Text("-Toggle mute      M");
            ImGui::Text("-Skip Level       F1");
            ImGui::Text("");


            ImGui::Text("KeyBoard:");
            ImGui::Text("-Move             WASD/ZQSD");
            ImGui::Text("-Place Bomb       SPACE");
            ImGui::Text("-Remote Detonate  Q/A");
            ImGui::Text("");
            
            ImGui::Text("Controller:");
            ImGui::Text("Coop:");
            ImGui::Text("-Move             DPAD");
            ImGui::Text("-Place Bomb       SOUTh BUTTON");
            ImGui::Text("-Remote Detonate  EAST BUTTON");
            ImGui::Text("");

            ImGui::Text("Versus:");
            ImGui::Text("-Move             DPAD");
            ImGui::Text("-Posess Enemy     SOUTh BUTTON");


            ImGui::TreePop();
        }


        if (ImGui::TreeNodeEx("SceneGraph", mainFlags))
        {
            AddObjectToTree(GetOwner());
            if (m_pCanvas != nullptr)
            {
                AddObjectToTree(m_pCanvas);
            }
                ImGui::TreePop();
        }

        ImGui::End();
    }
}

void D2D::ImGuiInfoComponent::AddObjectToTree(const GameObject* pObject)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;

    const auto& pChildren = pObject->GetChildren();
    if (pChildren.size() <= 0)
        flags |= ImGuiTreeNodeFlags_Leaf;

    if (ImGui::TreeNodeEx(pObject->GetName().c_str(), flags))
    {
        for (const auto& pChild : pChildren)
        {
            AddObjectToTree(pChild.get());
        }

        ImGui::TreePop();
    }
}


