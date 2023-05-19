#include "pch.h"
#include "EnemyManager.h"
#include "WorldEvents.h"
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
		}
	}
}
