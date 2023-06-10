#include "pch.h"
#include "BaseEnemyComponent.h"
#include "ExplosionComponent.h"
#include "Collider.h"
#include "PlayerComponent.h"
#include "EnemyAnimator.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "WorldEvents.h"
#include "Transform.h"

void D2D::BaseEnemyComponent::Update()
{
	if (!m_IsDead && m_pMovement != nullptr && m_pCollider != nullptr)
	{
		m_pMovement->Update(GetTransform(), m_pCollider, m_Speed);
	}
}

void D2D::BaseEnemyComponent::SetVariables(EnemyType type, float speed, Collider* pCollider, Collider* pTrigger)
{
	m_Type = type;
	m_Speed = speed;
	m_pCollider = pCollider;
	m_pTrigger = pTrigger;
	m_pAnimator = GetComponent<EnemyAnimator>().get();
}

void D2D::BaseEnemyComponent::SetMovementState(std::unique_ptr<EnemyMovementBaseState> pState)
{
	m_pMovement = std::move(pState);
	m_pMovement->SetEnemy(this);
}

void D2D::BaseEnemyComponent::OnTriggerEnter(const Collider* pCollider)
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

		auto dieEvent{ EnemyDieEvent() };
		dieEvent.pEnemy = this;
		dieEvent.enemyType = m_Type;

		NotifyObservers(dieEvent);
	}
	else if (auto player = pCollider->GetComponent<PlayerComponent>())
	{
		player->KillPlayer();
	}
}
