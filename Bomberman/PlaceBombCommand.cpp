#include "pch.h"
#include "PlaceBombCommand.h"
#include "PlayerComponent.h"

void D2D::PlaceBombCommand::Execute()
{
	if (m_pPlayerComponent != nullptr)
	{
		m_pPlayerComponent->PlaceBomb();
	}
}
