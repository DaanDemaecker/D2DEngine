#pragma once
#include <glm/glm.hpp>
#include "Command.h"

namespace D2D
{
	class Transform;

	class MoveCommand final : public Command
	{
	public:
		MoveCommand(const glm::vec2& direction, float speed, Transform* pTransform) : m_Direction{ direction }, m_Speed{speed}, m_pTransform{pTransform}, Command() {}

		virtual ~MoveCommand() = default;
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		virtual void Execute() override;

	private:
		glm::vec2 m_Direction;
		float m_Speed;
		Transform* m_pTransform;
	};
}