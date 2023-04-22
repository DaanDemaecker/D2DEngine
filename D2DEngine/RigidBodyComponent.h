#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace D2D
{
	class Transform;

	class RigidBodyComponent final : public Component
	{
	public:
		RigidBodyComponent();

		virtual void FixedUpdate() override;

		virtual void LateUpdate() override;

		void SetMovementSpeed(const float newSpeed) { m_MoveSpeed = newSpeed; }

		void SetVelocity(const glm::vec2& velocity);

		void AddForce(const glm::vec2& force);

		float GetMoveSpeed() const { return m_MoveSpeed; }

		glm::vec2 GetVelocity() const { return m_Velocity; }

	private:
		float m_MoveSpeed;

		glm::vec2 m_Velocity{};
		glm::vec2 m_Force{};

		Transform* m_pTransform{};
	};
}

