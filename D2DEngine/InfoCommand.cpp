#include "InfoCommand.h"
#include "ImGuiInfoComponent.h"

void D2D::InfoCommand::Execute()
{
	m_pInfoComponent->ToggleInfoWindow();
}
