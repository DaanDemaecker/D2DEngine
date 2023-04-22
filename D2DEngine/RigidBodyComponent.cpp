#include "RigidBodyComponent.h"
#include "Transform.h"
#include "TimeManager.h"
#include "Transform.h"

D2D::RigidBodyComponent::RigidBodyComponent()
	:m_MoveSpeed{ 10 }
{
}

void D2D::RigidBodyComponent::FixedUpdate()
{
	if (m_pTransform == nullptr)
	{
		m_pTransform = GetOwner()->GetTransform().get();
	}

	if (m_pTransform != nullptr)
	{
		auto translation = (m_Velocity + m_Force) * TimeManager::GetInstance().GetFixedTime();

		m_pTransform->MoveLocalPosition(translation);
	}
}

void D2D::RigidBodyComponent::LateUpdate()
{
	m_Force = glm::vec2{};
}

void D2D::RigidBodyComponent::SetVelocity(const glm::vec2& velocity)
{
	m_Velocity = velocity;
}

void D2D::RigidBodyComponent::AddForce(const glm::vec2& force)
{
	m_Force += force;
}
