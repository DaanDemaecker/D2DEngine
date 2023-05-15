#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Transform.h"
#include "Renderer.h"
#include "Structs.h"

#include <iostream>

D2D::BoxCollider::BoxCollider()
{
	
}

D2D::BoxCollider::~BoxCollider()
{
	if (m_IsTrigger)
	{
		PhysicsManager::GetInstance().RemoveTrigger(this);
	}
	else
	{
		PhysicsManager::GetInstance().RemoveCollider(this);
	}
}

void D2D::BoxCollider::AddToPhysicsManager(bool isTrigger)
{
	m_IsTrigger = isTrigger;

	if (m_IsTrigger)
	{
		PhysicsManager::GetInstance().AddTrigger(this);
	}
	else
	{
		PhysicsManager::GetInstance().AddCollider(this);
	}
}

void D2D::BoxCollider::SetVariables(float width, float height, float offsetX, float offsetY)
{
	if (m_pTransform == nullptr)
	{
		m_pTransform = GetOwner()->GetTransform().get();
		m_pTransform->SetCollider(this);
	}

	if (m_pTransform != nullptr)
	{
		auto pos{ m_pTransform->GetWorldPosition() };
		m_Bounds = BoxColliderBounds{ pos.x, pos.y, offsetX, offsetY, width, height };
	}
}

void D2D::BoxCollider::Render() const
{
	/*if (m_pTransform != nullptr)
	{
		const auto rect{ Rect{m_Bounds} };

		Renderer::GetInstance().DrawRect(rect.x, rect.y, rect.w, rect.h);
	}*/
}

D2D::BoxColliderBounds& D2D::BoxCollider::GetBounds()
{

	if (m_pTransform == nullptr)
	{
		m_pTransform = GetOwner()->GetTransform().get();
		m_pTransform->SetCollider(this);
	}

	if (m_pTransform != nullptr)
	{
		auto pos{ m_pTransform->GetWorldPosition() };
		m_Bounds.x = pos.x;
		m_Bounds.y = pos.y;
	}

	return m_Bounds;
}


