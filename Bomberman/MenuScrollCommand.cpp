#include "pch.h"
#include "MenuScrollCommand.h"
#include "GameObject.h"
#include "ButtonComponent.h"

D2D::MenuScrollCommand::MenuScrollCommand(int direction, std::vector<ButtonComponent*> pButtons, GameObject* pSelector)
{
	m_Direction = direction;
	m_pButtons = pButtons;
	m_pSelector = pSelector;
}

void D2D::MenuScrollCommand::Execute()
{
	if (m_pButtons.size() <= 0)
		return;

	int currentSelected{};
	int nextSelected{};

	for (int i{}; i < static_cast<int>(m_pButtons.size()); i++)
	{
		if (m_pButtons[i]->GetSelected())
		{
			currentSelected = i;
			break;
		}
	}

	nextSelected = (currentSelected + m_Direction);
	if (nextSelected < 0)
		nextSelected = static_cast<int>(m_pButtons.size()) -1;
	else
		nextSelected %= m_pButtons.size();

	m_pButtons[currentSelected]->SetSelected(false);
	m_pButtons[nextSelected]->SetSelected(true);

	if (m_pSelector != nullptr)
	{
		m_pSelector->SetParent(m_pButtons[nextSelected]->GetOwner(), false);
	}

}
