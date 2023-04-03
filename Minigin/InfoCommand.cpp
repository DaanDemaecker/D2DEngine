#include "InfoCommand.h"
#include "ImGuiInfoComponent.h"
#include "GameObject.h"

void dae::InfoCommand::Execute(const GameObject* Object)
{
	auto infoComponent = Object->GetComponent<ImGuiInfoComponent>();

	if (infoComponent != nullptr)
	{
		infoComponent->ToggleInfoWindow();
	}
}
