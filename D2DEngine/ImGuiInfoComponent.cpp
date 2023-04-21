#include "ImGuiInfoComponent.h"


void D2D::ImGuiInfoComponent::OnGUI()
{
	CreateWindow();
}

void D2D::ImGuiInfoComponent::CreateWindow()
{
    if (m_ShowInfoWindow)
    {
        ImGui::Begin("Info", &m_ShowInfoWindow);

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed;

        if (ImGui::TreeNodeEx("SceneGraph", flags))
        {

            AddObjectToTree(GetOwner());

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


