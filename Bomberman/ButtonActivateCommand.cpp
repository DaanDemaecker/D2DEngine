#include "pch.h"
#include "ButtonActivateCommand.h"
#include "ButtonComponent.h"

D2D::ButtonActivateCommand::ButtonActivateCommand(std::vector<ButtonComponent*> pButtons)
{
	m_pButtons = pButtons;
}

void D2D::ButtonActivateCommand::Execute()
{
	for (auto& pButton : m_pButtons)
	{
		if (pButton->GetSelected())
		{
			pButton->Execute();
			return;
		}
	}
}
