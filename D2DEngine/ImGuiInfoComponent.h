#pragma once
#include "Component.h"
#include "imgui.h"
#include "imgui_plot.h"
#include <vector>

namespace D2D
{
	class ImGuiInfoComponent final : public Component
	{
	public:
		ImGuiInfoComponent() = default;
		virtual ~ImGuiInfoComponent() = default;

		ImGuiInfoComponent(const ImGuiInfoComponent& other) = delete;
		ImGuiInfoComponent(ImGuiInfoComponent&& other) = delete;
		ImGuiInfoComponent& operator=(const ImGuiInfoComponent& other) = delete;
		ImGuiInfoComponent& operator=(ImGuiInfoComponent&& other) = delete;

		void ToggleInfoWindow() { m_ShowInfoWindow = !m_ShowInfoWindow; }

		void SetCanvas(GameObject* pCanvas);

		virtual void OnGUI() override;

	private:
		bool m_ShowInfoWindow{ false };

		GameObject* m_pCanvas{ nullptr };

		void CreateWindow();

		void AddObjectToTree(const GameObject* pObject);
	};
}