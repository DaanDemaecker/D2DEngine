#include "pch.h"
#include "PlayerMovementCommand.h"
#include "PlayerComponent.h"

void D2D::PlayerMovementCommand::Execute()
{
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->AddMovement(m_Direction);
	}
}
