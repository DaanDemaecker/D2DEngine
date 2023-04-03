#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class MoveComponent final : public Component
	{
	public:
		MoveComponent():m_MoveSpeed{10} {}

		virtual void Update() override;

		void SetMovementSpeed(const int newSpeed) { m_MoveSpeed = newSpeed; }

		void AddMovement(const glm::vec2& direction);

	private:
		int m_MoveSpeed;

		glm::vec2 m_Direction{};

	};
}

