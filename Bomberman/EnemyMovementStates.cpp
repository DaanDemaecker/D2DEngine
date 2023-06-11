#include "pch.h"
#include "EnemyMovementStates.h"
#include "PhysicsManager.h"
#include "TimeManager.h"
#include "PlayerComponent.h"
#include "Transform.h"
#include "Collider.h"
#include "EnemyAnimator.h"
#include "BaseEnemyComponent.h"

#include <iostream>

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

#pragma region wanderState
D2D::EnemyWanderState::EnemyWanderState(float marginX, float marginY, float frontDistance, float sideDistance)
{
	m_MarginX = marginX;
	m_MarginY = marginY;
	m_RaycastDistance = frontDistance;
	m_RaycastSideDistance = sideDistance;
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

	auto result1 = PhysicsManager::GetInstance().RaycastDirectional(p1, rayDirection, m_RaycastSideDistance, pCollider);
	auto result2 = PhysicsManager::GetInstance().RaycastDirectional(p2, rayDirection, m_RaycastSideDistance, pCollider);

	if ((result1 == nullptr || result1->GetComponent<PlayerComponent>() != nullptr) &&
		(result2 == nullptr || result2->GetComponent<PlayerComponent>() != nullptr))
	{
		m_Direction = rotDirection;
		return true;
	}

	rotDirection = Flip(rotDirection);
	rayDirection = DirectionToVec(rotDirection);

	result1 = PhysicsManager::GetInstance().RaycastDirectional(p1, rayDirection, m_RaycastSideDistance, pCollider);
	result2 = PhysicsManager::GetInstance().RaycastDirectional(p2, rayDirection, m_RaycastSideDistance, pCollider);

	if ((result1 == nullptr || result1->GetComponent<PlayerComponent>() != nullptr) &&
		(result2 == nullptr || result2->GetComponent<PlayerComponent>() != nullptr))
	{
		m_Direction = rotDirection;
		return true;
	}


	return false;
}
#pragma endregion wanderState


#pragma region lookingState
D2D::EnemyLookingState::EnemyLookingState(float marginX, float marginY, float frontDistance, float sideDistance, float playerDistance)
{
	m_MarginX = marginX;
	m_MarginY = marginY;
	m_RaycastDistance = frontDistance;
	m_RaycastSideDistance = sideDistance;
	m_PlayerRaycastDistance = playerDistance;
}

void D2D::EnemyLookingState::Update(EnemyAnimator* pAnimator, Transform* pTransform, Collider* pCollider, float speed)
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

	LookForPlayer(pTransform, pCollider);
}

void D2D::EnemyLookingState::OnStateChange(BaseEnemyComponent* pEnemy)
{
	if (m_pPlayerTransform != nullptr)
	{
		pEnemy->SetMovementState(std::make_unique<ChasingState>(m_MarginX, m_MarginY, m_RaycastDistance, m_RaycastSideDistance, m_PlayerRaycastDistance, m_pPlayerTransform));
	}
}

bool D2D::EnemyLookingState::ShouldFlip(Transform* pTransform, Collider* pCollider)
{
	glm::vec2 frontDirection{ DirectionToVec(m_Direction) };

	auto pos{ pTransform->GetWorldPosition() };

	auto result = PhysicsManager::GetInstance().RaycastDirectional(pos, frontDirection, m_RaycastDistance, pCollider);
	if (result != nullptr && result->GetComponent<PlayerComponent>() == nullptr)
	{
		return true;
	}

	return false;
}

bool D2D::EnemyLookingState::Shouldturn(Transform* pTransform, Collider* pCollider)
{
	Direction rotDirection{ Rotate(m_Direction) };
	auto rayDirection{ DirectionToVec(rotDirection) };

	auto pos{ pTransform->GetWorldPosition() };
	glm::vec2 p1{ pos.x + (m_MarginX * rayDirection.y), pos.y + (m_MarginY * rayDirection.x) };
	glm::vec2 p2{ pos.x - (m_MarginX * rayDirection.y), pos.y - (m_MarginY * rayDirection.x) };

	auto result1 = PhysicsManager::GetInstance().RaycastDirectional(p1, rayDirection, m_RaycastSideDistance, pCollider);
	auto result2 = PhysicsManager::GetInstance().RaycastDirectional(p2, rayDirection, m_RaycastSideDistance, pCollider);

	if ((result1 == nullptr || result1->GetComponent<PlayerComponent>() != nullptr) &&
		(result2 == nullptr || result2->GetComponent<PlayerComponent>() != nullptr))
	{
		m_Direction = rotDirection;
		return true;
	}

	rotDirection = Flip(rotDirection);
	rayDirection = DirectionToVec(rotDirection);

	result1 = PhysicsManager::GetInstance().RaycastDirectional(p1, rayDirection, m_RaycastSideDistance, pCollider);
	result2 = PhysicsManager::GetInstance().RaycastDirectional(p2, rayDirection, m_RaycastSideDistance, pCollider);

	if ((result1 == nullptr || result1->GetComponent<PlayerComponent>() != nullptr) &&
		(result2 == nullptr || result2->GetComponent<PlayerComponent>() != nullptr))
	{
		m_Direction = rotDirection;
		return true;
	}


	return false;
}
void D2D::EnemyLookingState::LookForPlayer(Transform* pTransform, Collider* pCollider)
{
	Direction direction{ m_Direction };
	glm::vec2 rayDirection{ DirectionToVec(direction) };

	auto pos{ pTransform->GetWorldPosition() };

	for (int i{}; i < 4; ++i)
	{
		auto result = PhysicsManager::GetInstance().RaycastDirectional(pos, rayDirection, m_PlayerRaycastDistance, pCollider);


		if (result != nullptr)
		{
			auto player = result->GetComponent<PlayerComponent>();

			if (player != nullptr)
			{
				m_pPlayerTransform = player->GetTransform();
			}
		}

		direction = Rotate(direction);
		rayDirection = DirectionToVec(direction);
	}
}
#pragma endregion lookingState

#pragma region chasingState
D2D::ChasingState::ChasingState(float marginX, float marginY, float frontDistance, float sideDistance, float playerDistance, Transform* pPlayerTransform)
{
	m_MarginX = marginX;
	m_MarginY = marginY;
	m_RaycastDistance = frontDistance;
	m_RaycastSideDistance = sideDistance;
	m_PlayerRaycastDistance = playerDistance;
	m_pPlayerTransform = pPlayerTransform;
}

void D2D::ChasingState::Update(EnemyAnimator* pAnimator, Transform* pTransform, Collider* pCollider, float speed)
{
	m_Timer -= TimeManager::GetInstance().GetDeltaTime();

	auto pos{ pTransform->GetWorldPosition() };
	auto playerPos{ m_pPlayerTransform->GetWorldPosition() };

	glm::vec2 direction{playerPos - pos};

	if (abs(direction.x) > abs(direction.y))
	{
		direction.y = 0;
	}
	else
	{
		direction.x = 0;
	}

	direction = glm::normalize(direction);

	pAnimator->FacingRight(direction.x > 0);

	LookForPlayer(pTransform, pCollider);

	pTransform->MoveLocalPosition(direction * speed * TimeManager::GetInstance().GetDeltaTime());
}

void D2D::ChasingState::OnStateChange(BaseEnemyComponent* pEnemy)
{
	if (m_Timer <= 0)
	{
		pEnemy->SetMovementState(std::make_unique<EnemyLookingState>(m_MarginX, m_MarginY, m_RaycastDistance, m_RaycastSideDistance, m_PlayerRaycastDistance));
	}
}

void D2D::ChasingState::LookForPlayer(Transform* pTransform, Collider* pCollider)
{
	Direction direction{ Direction::Left };
	glm::vec2 rayDirection{ DirectionToVec(direction) };

	auto pos{ pTransform->GetWorldPosition() };

	for (int i{}; i < 4; ++i)
	{
		auto result = PhysicsManager::GetInstance().RaycastDirectional(pos, rayDirection, m_PlayerRaycastDistance, pCollider);


		if (result != nullptr)
		{
			auto player = result->GetComponent<PlayerComponent>();

			if (player != nullptr)
			{
				m_pPlayerTransform = player->GetTransform();
				m_Timer = m_Time;
			}
		}

		direction = Rotate(direction);
		rayDirection = DirectionToVec(direction);
	}
}





#pragma endregion chasingState

void D2D::ControlledState::Update(EnemyAnimator* /*pAnimator*/, Transform* /*pTransform*/, Collider* /*pCollider*/, float /*speed*/)
{
}

void D2D::ControlledState::SetDirection(const glm::vec2& direction)
{
	m_Direction = direction;
}
