#include "CapsuleCollider.h"
#include "Transform.h"
#include "Renderer.h"
#include "PhysicsManager.h"
#include "ColliderEvent.h"

D2D::CapsuleCollider::CapsuleCollider()
{
	PhysicsManager::GetInstance().AddCollider(this);
}

D2D::CapsuleCollider::~CapsuleCollider()
{
	if (m_IsTrigger)
	{
		//PhysicsManager::GetInstance().RemoveTrigger(this);
	}
	else
	{
		PhysicsManager::GetInstance().RemoveCollider(this);
	}
}

void D2D::CapsuleCollider::AddToPhysicsManager(bool isTrigger)
{
	m_IsTrigger = isTrigger;

	if (m_IsTrigger)
	{
		//PhysicsManager::GetInstance().AddTrigger(this);
	}
	else
	{
		PhysicsManager::GetInstance().AddCollider(this);
	}
}

void D2D::CapsuleCollider::TriggerOverlap(Collider* other)
{
	TriggerOverlapEvent triggerOverlapEvent{};
	triggerOverlapEvent.Self = this;
	triggerOverlapEvent.Other = other;

	NotifyObservers(triggerOverlapEvent);
}

void D2D::CapsuleCollider::SetVariables(float height, float radius, float offsetX, float offsetY)
{
	if (m_pTransform == nullptr)
	{
		m_pTransform = GetOwner()->GetTransform().get();
		m_pTransform->SetCollider(this);
	}

	if (m_pTransform != nullptr)
	{
		auto pos{ m_pTransform->GetWorldPosition() };
		m_Bounds = Capsule{ pos, {offsetX, offsetY}, height, radius};
	}
}

void D2D::CapsuleCollider::LateUpdate()
{
	if (m_pTransform != nullptr)
	{
		const auto pos{ m_pTransform->GetWorldPosition() };
		m_Bounds.center = pos;
	}
}

void D2D::CapsuleCollider::Render() const
{
	/*Renderer::GetInstance().DrawCircle(m_Bounds.center.x, m_Bounds.center.y + m_Bounds.height / 2 - m_Bounds.radius, m_Bounds.radius);
	Renderer::GetInstance().DrawCircle(m_Bounds.center.x, m_Bounds.center.y - m_Bounds.height / 2 + m_Bounds.radius, m_Bounds.radius);
	Renderer::GetInstance().DrawRect(m_Bounds.center.x - m_Bounds.radius, m_Bounds.center.y - m_Bounds.height / 2 + m_Bounds.radius,
		2 * m_Bounds.radius, m_Bounds.height - 2 * m_Bounds.radius,
		SDL_Color{255, 0, 0, 255});*/
}

D2D::Capsule& D2D::CapsuleCollider::GetBounds()
{
	if (m_pTransform != nullptr)
	{
		auto pos{ m_pTransform->GetWorldPosition() };
		m_Bounds.center = pos;
	}
	
	return m_Bounds;
}
