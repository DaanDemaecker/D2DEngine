#include "pch.h"
#include "EnemyMovementStates.h"
#include "PhysicsManager.h"
#include "TimeManager.h"
#include "PlayerComponent.h"
#include "Transform.h"
#include "Collider.h"
#include "EnemyAnimator.h"

D2D::Direction D2D::Flip(D2D::Direction direction)
{
	switch (direction)
	{
	case D2D::Direction::Up:
		return Direction::Down;
		break;
	case D2D::Direction::Right:
		return Direction::Left;
		break;
	case D2D::Direction::Down:
		return Direction::Up;
		break;
	case D2D::Direction::Left:
		return Direction::Right;
		break;
	default:
		return Direction::Up;
		break;
	}
}

D2D::Direction D2D::Rotate(D2D::Direction direction)
{
	switch (direction)
	{
	case D2D::Direction::Up:
		return Direction::Right;
		break;
	case D2D::Direction::Right:
		return Direction::Down;
		break;
	case D2D::Direction::Down:
		return Direction::Left;
		break;
	case D2D::Direction::Left:
		return Direction::Up;
		break;
	default:
		return Direction::Up;
		break;
	}
}

glm::vec2 D2D::DirectionToVec(Direction direction)
{
	switch (direction)
	{
	case D2D::Direction::Up:
		return glm::vec2{ 0, -1 };
		break;
	case D2D::Direction::Right:
		return glm::vec2{ 1, 0 };
		break;
	case D2D::Direction::Down:
		return  glm::vec2{ 0, 1 };
		break;
	case D2D::Direction::Left:
		return  glm::vec2{ -1, 0 };
		break;
	default:
		return glm::vec2{ 0, 0 };
		break;
	}
}

D2D::Direction D2D::VectToDirection(const glm::vec2 vec)
{
	if (vec.x > 0)
		return Direction::Right;
	else if (vec.x < 0)
		return Direction::Left;
	else if (vec.y > 0)
		return Direction::Down;
	else
		return Direction::Up;
}

D2D::EnemyWanderState::EnemyWanderState(float marginX, float marginY, float distance)
{
	m_MarginX = marginX;
	m_MarginY = marginY;
	m_RaycastDistance = distance;
}

void D2D::EnemyWanderState::Update(EnemyAnimator* pAnimator, Transform* pTransform, Collider* pCollider, float speed)
{
	if (m_TurnTimer > 0)
	{
		m_TurnTimer -= TimeManager::GetInstance().GetDeltaTime();
	}

	if (m_TurnTimer <= 0 && Shouldturn(pTransform, pCollider))
	{
		m_TurnTimer = m_TurnTime;
	}
	else if (ShouldFlip(pTransform, pCollider))
	{
		m_Direction = Flip(m_Direction);
	}
	

	glm::vec2 frontDirection{ DirectionToVec(m_Direction) };

	pAnimator->FacingRight(frontDirection.x > 0);

	if (!pTransform->MoveLocalPosition(frontDirection * speed * TimeManager::GetInstance().GetDeltaTime()))
	{
		m_TurnTimer = 0;
	}
}

bool D2D::EnemyWanderState::ShouldFlip(Transform* pTransform, Collider* pCollider)
{
	glm::vec2 frontDirection{ DirectionToVec(m_Direction)};

	auto pos{ pTransform->GetWorldPosition() };

	auto result = PhysicsManager::GetInstance().RaycastDirectional(pos, frontDirection, m_RaycastDistance, pCollider);
	if (result != nullptr && result->GetComponent<PlayerComponent>() == nullptr)
	{
		return true;
	}

	return false;
}

bool D2D::EnemyWanderState::Shouldturn(Transform* pTransform, Collider* pCollider)
{
	Direction rotDirection{ Rotate(m_Direction) };
	auto rayDirection{ DirectionToVec(rotDirection) };

	auto pos{ pTransform->GetWorldPosition() };
	glm::vec2 p1{pos.x + (m_MarginX * rayDirection.y), pos.y + (m_MarginY * rayDirection.x)};
	glm::vec2 p2{ pos.x - (m_MarginX * rayDirection.y), pos.y - (m_MarginY * rayDirection.x) };

	auto result1 = PhysicsManager::GetInstance().RaycastDirectional(p1, rayDirection, m_RaycastDistance, pCollider);
	auto result2 = PhysicsManager::GetInstance().RaycastDirectional(p2, rayDirection, m_RaycastDistance, pCollider);

	if ((result1 == nullptr || result1->GetComponent<PlayerComponent>() != nullptr) &&
		(result2 == nullptr || result2->GetComponent<PlayerComponent>() != nullptr))
	{
		m_Direction = rotDirection;
		return true;
	}

	rotDirection = Flip(rotDirection);
	rayDirection = DirectionToVec(rotDirection);

	result1 = PhysicsManager::GetInstance().RaycastDirectional(p1, rayDirection, m_RaycastDistance, pCollider);
	result2 = PhysicsManager::GetInstance().RaycastDirectional(p2, rayDirection, m_RaycastDistance, pCollider);

	if ((result1 == nullptr || result1->GetComponent<PlayerComponent>() != nullptr) &&
		(result2 == nullptr || result2->GetComponent<PlayerComponent>() != nullptr))
	{
		m_Direction = rotDirection;
		return true;
	}


	return false;
}
