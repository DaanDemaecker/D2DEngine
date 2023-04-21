#include "pch.h"
#include "PlayerComponent.h"

void D2D::PlayerComponent::Update()
{
}

void D2D::PlayerComponent::KillPlayer()
{
	NotifyObservers(m_PlayerDieEvent);
}

void D2D::PlayerComponent::PickupItem()
{
	NotifyObservers(m_PickupItemEvent);
}
