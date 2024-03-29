#include "Transform.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include <iostream>

void D2D::Transform::SetCollider(BoxCollider* pCollider)
{
	m_pBoxCollider = pCollider;
}

void D2D::Transform::SetCollider(CapsuleCollider* pCollider)
{
	m_pCapsuleCollider = pCollider;
}

void D2D::Transform::RemoveCollider()
{
	m_pBoxCollider = nullptr;
	m_pCapsuleCollider = nullptr;
}

void D2D::Transform::SetLocalPosition(const float x, const float y)
{
	SetLocalPosition(glm::vec2{ x, y });
}

void D2D::Transform::SetLocalPosition(const glm::vec2& pos)
{
	m_LocalPosition = pos;

	const auto& pChildren{ GetOwner()->GetChildren()};

	for (auto& pChild : pChildren)
	{
		pChild->GetTransform()->SetDirtyFlag();
	}
}

glm::vec2 D2D::Transform::GetWorldPosition()
{
	if (GetOwner() == nullptr || GetOwner()->GetParent() == nullptr)
	{
		m_ParentWorldPosition = glm::vec2{};
		m_HasChanged = false;
	}
	else if (m_HasChanged)
	{
		m_ParentWorldPosition = GetOwner()->GetParent()->GetTransform()->GetWorldPosition();
		m_HasChanged = false;
	}

	return m_ParentWorldPosition + m_LocalPosition;
}

void D2D::Transform::SetWorldPosition(float x, float y)
{
	SetWorldPosition(glm::vec2{ x, y });
	CheckTriggers();
}

void D2D::Transform::SetWorldPosition(const glm::vec2& pos)
{
	SetLocalPosition(pos - (GetWorldPosition() - m_LocalPosition));
	CheckTriggers();
}

bool D2D::Transform::MoveLocalPosition(float x, float y)
{
	return MoveLocalPosition(glm::vec2{ x, y });
}

bool D2D::Transform::MoveLocalPosition(const glm::vec2& dir)
{
	if (m_pBoxCollider != nullptr && m_pCapsuleCollider != nullptr)
	{
		if (m_pBoxCollider->IsTrigger())
		{
			glm::vec2 direction{ dir };
			if (PhysicsManager::GetInstance().CanMove(m_pCapsuleCollider, direction))
			{
				SetLocalPosition(m_LocalPosition + direction);
				CheckTriggers();
				return true;
			}
			else return false;
		}
		else
		{
			glm::vec2 direction{ dir };
			if (PhysicsManager::GetInstance().CanMove(m_pBoxCollider, direction))
			{
				SetLocalPosition(m_LocalPosition + direction);
				CheckTriggers();
				return true;
			}
			else return false;
		}
	}
	
	if (m_pBoxCollider != nullptr)
	{
		glm::vec2 direction{ dir };
		if (m_pBoxCollider->IsTrigger())
		{
			SetLocalPosition(m_LocalPosition + direction);
			CheckTriggers();
			return true;
		}
		else
		{
			if (PhysicsManager::GetInstance().CanMove(m_pBoxCollider, direction))
			{
				SetLocalPosition(m_LocalPosition + direction);
				CheckTriggers();
				return true;
			}
		}

	}
	else if (m_pCapsuleCollider != nullptr)
	{
		glm::vec2 direction{ dir };
		if (PhysicsManager::GetInstance().CanMove(m_pCapsuleCollider, direction))
		{
			SetLocalPosition(m_LocalPosition + direction);
			CheckTriggers();
			return true;
		}
	}
	else
	{
		SetLocalPosition(m_LocalPosition + dir);
		CheckTriggers();
		return true;
	}
	return false;
}

void D2D::Transform::SetDirtyFlag()
{
	m_HasChanged = true;

	for (auto& pChild : GetOwner()->GetChildren())
	{
		pChild->GetTransform()->SetDirtyFlag();
	}
}

void D2D::Transform::Render() const
{
	//auto pos = m_ParentWorldPosition + m_LocalPosition;

	//Renderer::GetInstance().DrawMarker(pos.x, pos.y, 20, SDL_Color(255, 0, 0));
}

void D2D::Transform::CheckTriggers()
{
	if (m_pBoxCollider != nullptr)
	{
		if (m_pBoxCollider->IsTrigger())
		{
			PhysicsManager::GetInstance().CheckTrigger(m_pBoxCollider);
		}
		else
		{
			PhysicsManager::GetInstance().CheckColliderForTrigger(m_pBoxCollider);
		}
	}
	
	if (m_pCapsuleCollider != nullptr)
	{
			PhysicsManager::GetInstance().CheckColliderForTrigger(m_pCapsuleCollider);
	}
}
