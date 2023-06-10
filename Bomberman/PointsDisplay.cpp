#include "pch.h"
#include "PointsDisplay.h"
#include "PlayerEvents.h"
#include "TextComponent.h"
#include "PlayerComponent.h"
#include "WorldEvents.h"
#include "BaseEnemyComponent.h"
#include "GameData.h"

D2D::PointsDisplay::PointsDisplay()
	:Component()
{
}

void D2D::PointsDisplay::Notify(const Event& event)
{
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
		case EnemyType::Oneal:
			m_Score += 200;
			break;
		case EnemyType::Doll:
			m_Score += 400;
			break;
		case EnemyType::Minvo:
			m_Score += 800;
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

void D2D::PointsDisplay::OnSceneLoad()
{
	m_Score = 0;
	UpdatePointsDisplay();
	GameData::GetInstance().SetScore(0);
}

void D2D::PointsDisplay::OnSceneUnload()
{
	GameData::GetInstance().SetScore(m_Score);
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
