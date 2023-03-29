#include "Transform.h"

void dae::Transform::SetLocalPosition(const float x, const float y)
{
	SetLocalPosition(glm::vec2{ x, y });
}

void dae::Transform::SetLocalPosition(const glm::vec2& pos)
{
	m_LocalPosition = pos;

	const auto& pChildren{ m_pOwner->GetChildren() };

	for (auto& pChild : pChildren)
	{
		pChild->GetTransform()->SetDirtyFlag();
	}
}

glm::vec2 dae::Transform::GetWorldPosition()
{
	if (m_pOwner == nullptr || m_pOwner->GetParent() == nullptr)
	{
		m_ParentWorldPosition = glm::vec2{};
		m_HasChanged = false;
	}
	else if (m_HasChanged)
	{
		m_ParentWorldPosition = m_pOwner->GetParent()->GetTransform()->GetWorldPosition();
		m_HasChanged = false;
	}

	return m_ParentWorldPosition + m_LocalPosition;
}

void dae::Transform::SetWorldPosition(float x, float y)
{
	SetWorldPosition(glm::vec2{ x, y });
}

void dae::Transform::SetWorldPosition(const glm::vec2& pos)
{
	SetLocalPosition(pos - (GetWorldPosition() - m_LocalPosition));
}

void dae::Transform::SetDirtyFlag()
{
	m_HasChanged = true;

	for (auto& pChild : m_pOwner->GetChildren())
	{
		pChild->GetTransform()->SetDirtyFlag();
	}

}
