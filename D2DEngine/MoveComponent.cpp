#include "MoveComponent.h"
#include "Transform.h"
#include "TimeManager.h"

void D2D::MoveComponent::Update()
{
	auto pTransform = GetOwner()->GetTransform();

	if (m_Direction == glm::vec2{})
		return;

	m_Direction = glm::normalize(m_Direction);

	pTransform->MoveLocalPosition( m_Direction.x * m_MoveSpeed * TimeManager::GetInstance().GetDeltaTime(),
		m_Direction.y * m_MoveSpeed * TimeManager::GetInstance().GetDeltaTime());

	m_Direction = glm::vec2{};

}

void D2D::MoveComponent::AddMovement(const glm::vec2& direction)
{
	m_Direction += direction;
}
