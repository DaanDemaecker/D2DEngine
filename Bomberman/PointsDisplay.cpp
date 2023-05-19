#include "pch.h"
#include "PointsDisplay.h"
#include "PlayerEvents.h"
#include "TextComponent.h"
#include "PlayerComponent.h"
#include "WorldEvents.h"
#include "BaseEnemyComponent.h"

D2D::PointsDisplay::PointsDisplay()
	:Component()
{
}

void D2D::PointsDisplay::Notify(const Event& event)
{
	/*if (auto playerDieEvent{ dynamic_cast<const PlayerDieEvent*>(&event) })
	{
		m_Score = 0;
	}
	else */
	if (auto pickupItemEvent{ dynamic_cast<const PowerupCollectedEvent*>(&event) })
	{
		m_Score += 1000;
	}
	else if (auto enemieDieEvent{ dynamic_cast<const EnemyDieEvent*>(&event) })
	{
		switch (enemieDieEvent->enemyType)
		{
		case EnemyType::Balloom:
			m_Score += 100;
			break;
		default:
			break;
		}
	}
	else
	{
		return;
	}


	m_ShouldUpdateText = true;
}

void D2D::PointsDisplay::Update()
{
	if (m_ShouldUpdateText)
	{
		UpdatePointsDisplay();
		m_ShouldUpdateText = false;
	}
}

void D2D::PointsDisplay::UpdatePointsDisplay()
{
	if (m_pTextComponent == nullptr)
	{
		m_pTextComponent = GetComponent<TextComponent>().get();
	}

	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetText("SCORE: " + std::to_string(m_Score));
	}
}
