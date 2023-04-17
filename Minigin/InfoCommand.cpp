#include "InfoCommand.h"
#include "ImGuiInfoComponent.h"

void dae::InfoCommand::Execute()
{
	m_pInfoComponent->ToggleInfoWindow();
}
