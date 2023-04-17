#pragma once
#include <glm/glm.hpp>
#include "Command.h"

namespace dae
{
	class MoveComponent;

	class MoveCommand final : public Command
	{
	public:
		MoveCommand(const glm::vec2& direction, MoveComponent* pMoveComponent) : m_Direction{ direction }, m_pMoveComponent{pMoveComponent}, Command() {}

		virtual ~MoveCommand() = default;
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		virtual void Execute() override;

	private:
		const glm::vec2 m_Direction;
		MoveComponent* m_pMoveComponent;
	};
}