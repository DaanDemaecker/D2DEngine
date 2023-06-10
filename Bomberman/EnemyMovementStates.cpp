#include "pch.h"
#include "EnemyMovementStates.h"
#include "PhysicsManager.h"
#include "TimeManager.h"
#include <iostream>

D2D::EnemyWanderState::EnemyWanderState(float marginX, float marginY, float distance)
{
	m_MarginX = marginX;
	m_MarginY = marginY;
	m_RaycastDistance = distance;
}

void D2D::EnemyWanderState::Update(Transform* /*pTransform*/, Collider* /*pCollider*/, float /*speed*/)
{
	std::cout << "Text\n";
}
