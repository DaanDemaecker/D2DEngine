#include "Transform.h"

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
}

void D2D::Transform::SetWorldPosition(const glm::vec2& pos)
{
	SetLocalPosition(pos - (GetWorldPosition() - m_LocalPosition));
}

void D2D::Transform::MoveLocalPosition(float x, float y)
{
	MoveLocalPosition(glm::vec2{ x, y });
}

void D2D::Transform::MoveLocalPosition(const glm::vec2& pos)
{
	SetLocalPosition(m_LocalPosition + pos);
}

void D2D::Transform::SetDirtyFlag()
{
	m_HasChanged = true;

	for (auto& pChild : GetOwner()->GetChildren())
	{
		pChild->GetTransform()->SetDirtyFlag();
	}

}
