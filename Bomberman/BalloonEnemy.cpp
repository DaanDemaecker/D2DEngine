#include "pch.h"
#include "BalloonEnemy.h"
#include "PhysicsManager.h"
#include "TimeManager.h"
#include "Transform.h"
#include "EnemyAnimator.h"
#include "Collider.h"
#include "ExplosionComponent.h"
#include "PlayerComponent.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "WorldEvents.h"

void D2D::BalloonEnemy::Update()
{
	if (m_IsDead)
		return;

	if (m_pAnimator == nullptr)
	{
		m_pAnimator = GetComponent<EnemyAnimator>().get();
	}

	glm::vec2 movement{};

	switch (m_CurrentDirection)
	{
	case D2D::BaseEnemyComponent::Direction::Up:
		movement = { 0, -m_Speed };
		break;
	case D2D::BaseEnemyComponent::Direction::Down:
		movement = { 0, m_Speed };
		break;
	case D2D::BaseEnemyComponent::Direction::Left:
		movement = { -m_Speed, 0 };
		break;
	case D2D::BaseEnemyComponent::Direction::Right:
		movement = { m_Speed, 0 };
		break;
	default:
		break;
	}

	movement *= TimeManager::GetInstance().GetDeltaTime();

	if (!GetTransform()->MoveLocalPosition(movement))
	{
		m_CurrentDirection = static_cast<Direction>(rand() % 4);

		if (m_pAnimator != nullptr)
		{
			if (m_CurrentDirection == Direction::Left)
			{
				m_pAnimator->FacingRight(false);
			}
			else if (m_CurrentDirection == Direction::Right)
			{
				m_pAnimator->FacingRight(true);
			}
		}
		
	}
}

void D2D::BalloonEnemy::OnTriggerEnter(const Collider* pCollider)
{
	if (pCollider->GetComponent<ExplosionComponent>())
	{
		if (m_pAnimator != nullptr)
		{
			m_pAnimator->Kill();
		}
		GetOwner()->RemoveComponent<BoxCollider>();
		GetOwner()->RemoveComponent<CapsuleCollider>();
		m_IsDead = true;

		auto dieEvent{ EnemyDieEvent()};
		dieEvent.pEnemy = this;
		dieEvent.enemyType = m_Type;

		NotifyObservers(dieEvent);
	}
	else if (auto player = pCollider->GetComponent<PlayerComponent>())
	{
		player->KillPlayer();
	}
}
