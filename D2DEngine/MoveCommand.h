#pragma once
#include <glm/glm.hpp>
#include "Command.h"

namespace D2D
{
	class RigidBodyComponent;

	class MoveCommand final : public Command
	{
	public:
		MoveCommand(const glm::vec2& direction, RigidBodyComponent* pMoveComponent) : m_Direction{ direction }, m_pRigidBody{pMoveComponent}, Command() {}

		virtual ~MoveCommand() = default;
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		virtual void Execute() override;

	private:
		const glm::vec2 m_Direction;
		RigidBodyComponent* m_pRigidBody;
	};
}