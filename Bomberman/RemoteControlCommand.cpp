#include "pch.h"
#include "RemoteControlCommand.h"
#include "BombManagerComponent.h"

void D2D::RemoteControlCommand::Execute()
{
	if (m_pBombManager != nullptr)
	{
		m_pBombManager->RemoteControlTriggered();
	}
}
