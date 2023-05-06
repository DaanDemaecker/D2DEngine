#include "pch.h"
#include "BombComponent.h"
#include "TimeManager.h"

void D2D::BombComponent::Update()
{
	m_Timer -= TimeManager::GetInstance().GetDeltaTime();

	if (m_Timer <= 0)
	{
		BombExplodeEvent event{};
		event.gridNumber = m_GridNumber;
		event.strength = m_BombStrength;
		NotifyObservers(event);

		GetOwner()->Destroy();
	}
}
