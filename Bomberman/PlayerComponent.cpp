#include "pch.h"
#include "PlayerComponent.h"
#include "Transform.h"

void D2D::PlayerComponent::Update()
{
}

void D2D::PlayerComponent::PlaceBomb()
{
	if (m_pTransform == nullptr)
	{
		m_pTransform = GetOwner()->GetTransform().get();
	}

	if (m_pTransform != nullptr)
	{
		m_PlaceBombEvent.position = m_pTransform->GetLocalPosition();
		NotifyObservers(m_PlaceBombEvent);
	}
}

void D2D::PlayerComponent::KillPlayer()
{
	NotifyObservers(m_PlayerDieEvent);
}

void D2D::PlayerComponent::PickupItem()
{
	NotifyObservers(m_PickupItemEvent);
}
