#include "pch.h"
#include "PlayerComponent.h"
#include "Transform.h"
#include "TimeManager.h"
#include "PlayerAnimator.h"
#include "ExplosionComponent.h"
#include "Collider.h"
#include <iostream>

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
		m_pAnimator->SetShouldAnimate(m_Movement != glm::vec2{});
		m_pAnimator->SetDirection(m_Movement);
	}

	if (m_pTransform != nullptr && m_Movement != glm::vec2{})
	{
		m_Movement = glm::normalize(m_Movement) * m_Speed;
		m_pTransform->MoveLocalPosition(m_Movement * TimeManager::GetInstance().GetDeltaTime());
		m_Movement = glm::vec2{};
	}
}

void D2D::PlayerComponent::PlaceBomb()
{
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
