#include "pch.h"
#include "PlayerComponent.h"

void dae::PlayerComponent::Update()
{
}

void dae::PlayerComponent::KillPlayer()
{
	NotifyObservers(m_PlayerDieEvent);
}
