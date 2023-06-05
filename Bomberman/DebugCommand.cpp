#include "pch.h"
#include "DebugCommand.h"
#include "GameObject.h"

void D2D::DebugCommand::Execute()
{
	m_pGameObject->SetActive(!m_pGameObject->IsActive());
}
