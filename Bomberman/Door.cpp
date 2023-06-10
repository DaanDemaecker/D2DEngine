#include "pch.h"
#include "Door.h"
#include "Collider.h"
#include "PlayerComponent.h"
#include "WorldEvents.h"
#include "ServiceLocator.h"
#include "TimeManager.h"

void D2D::Door::OnTriggerEnter(const Collider* pCollider)
{
	if (!m_EnemiesDead)
		return;

	if (pCollider->HasComponent<PlayerComponent>())
	{
		ServiceLocator::GetSoundSystem().Play(11, 128, 0);

		m_Timer = m_Time;
	}
}

void D2D::Door::Notify(const Event& event)
{
	if (auto enemyDieEvent{ dynamic_cast<const EnemiesDeadEvent*>(&event) })
	{
		m_EnemiesDead = true;
	}
}

void D2D::Door::Update()
{
	if (m_Timer > 0)
	{
		m_Timer -= TimeManager::GetInstance().GetDeltaTime();
		if (m_Timer <= 0)
		{
			NotifyObservers(LevelCompleteEvent());
		}
	}
}
