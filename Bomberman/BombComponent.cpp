#include "pch.h"
#include "BombComponent.h"
#include "TimeManager.h"
#include "ServiceLocator.h"

void D2D::BombComponent::Update()
{
	m_Timer -= TimeManager::GetInstance().GetDeltaTime();

	if (m_Timer <= 0)
	{
		ExplodeBomb();
	}
}

void D2D::BombComponent::ExplodeBomb()
{
	BombExplodeEvent event{};
	event.gridNumber = m_GridNumber;
	event.strength = m_BombStrength;
	NotifyObservers(event);

	ServiceLocator::GetSoundSystem().Play(2, 128);


	GetOwner()->Destroy();
}

void D2D::BombComponent::InstantExplosion()
{
	m_Timer = std::min(m_Timer, m_InstantExplosionTimer);
}


