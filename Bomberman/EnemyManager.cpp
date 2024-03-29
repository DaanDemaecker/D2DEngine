#include "pch.h"
#include "EnemyManager.h"
#include "WorldEvents.h"
#include "ServiceLocator.h"
#include <algorithm>

void D2D::EnemyManager::Notify(const Event& event)
{
	if (auto enemieSpawnEvent{ dynamic_cast<const EnemySpawnEvent*>(&event) })
	{
		m_pEnemies.push_back(enemieSpawnEvent->pEnemy);

		enemieSpawnEvent->pEnemy->AddObserver(this);
	}
	else if (auto enemyDieEvent{ dynamic_cast<const EnemyDieEvent*>(&event) })
	{
		if (std::find(m_pEnemies.begin(), m_pEnemies.end(), enemyDieEvent->pEnemy) != m_pEnemies.end())
		{
			NotifyObservers(event);

			m_pEnemies.erase(std::remove(m_pEnemies.begin(), m_pEnemies.end(), enemyDieEvent->pEnemy), m_pEnemies.end());

			if (m_pEnemies.size() == 0)
			{
				NotifyObservers(EnemiesDeadEvent());
				ServiceLocator::GetSoundSystem().Play(10, 128, 0);
			}
		}
	}
}

void D2D::EnemyManager::AddSubject(Subject* subject)
{
	if (std::find(m_pSubjects.begin(), m_pSubjects.end(), subject) == m_pSubjects.end())
	{
		m_pSubjects.push_back(subject);
	}
}

void D2D::EnemyManager::RemoveSubjects()
{
	for (auto& subject : m_pSubjects)
	{
		subject->RemoveObserver(this);
	}
}
