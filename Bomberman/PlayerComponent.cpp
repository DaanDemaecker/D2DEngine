#include "pch.h"
#include "PlayerComponent.h"
#include "Transform.h"
#include "TimeManager.h"
#include "PlayerAnimator.h"
#include "ExplosionComponent.h"
#include "Collider.h"
#include "ServiceLocator.h"
#include <iostream>

#include "PhysicsManager.h"
#include "Renderer.h"

void D2D::PlayerComponent::Update()
{
	if (m_pTransform == nullptr)
	{
		m_pTransform = GetOwner()->GetTransform().get();
	}

	if (m_pAnimator == nullptr)
	{
		m_pAnimator = GetComponent<PlayerAnimator>().get();
	}

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->SetShouldAnimate(m_Movement != glm::vec2{} || m_IsDead);
		m_pAnimator->SetDirection(m_Movement);
	}

	if (m_pTransform != nullptr && m_Movement != glm::vec2{} && !m_IsDead)
	{
		m_Movement = glm::normalize(m_Movement) * m_Speed * TimeManager::GetInstance().GetDeltaTime();

		auto pos{ m_pTransform->GetWorldPosition() };

		if (pos.x - m_PlayerHalfWidth + m_Movement.x > 0 &&
			pos.x + m_PlayerHalfWidth + m_Movement.x < m_LevelWidth)
		{
			m_pTransform->MoveLocalPosition(m_Movement);
		}
		m_Movement = glm::vec2{};
	}
}

void D2D::PlayerComponent::PlaceBomb()
{
	if (m_IsDead || !IsActive())
		return;

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
	ServiceLocator::GetSoundSystem().Play(7, 128, 0);
	m_pAnimator->Kill();
	m_IsDead = true;
}

void D2D::PlayerComponent::PickupItem()
{
	NotifyObservers(m_PickupItemEvent);
}

void D2D::PlayerComponent::OnTriggerEnter(const Collider* pCollider)
{
	if (pCollider->HasComponent<ExplosionComponent>())
	{
		KillPlayer();
	}
}

void D2D::PlayerComponent::PowerupCollected(PowerupType powerupType)
{
	PowerupCollectedEvent powerupEvent{};
	powerupEvent.type = powerupType;

	NotifyObservers(powerupEvent);
}
