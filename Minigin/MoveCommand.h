#pragma once
#include <glm/glm.hpp>
#include "Command.h"

namespace dae
{
	class GameObject;

	class MoveCommand final : public Command
	{
	public:
		MoveCommand(const glm::vec2& direction) : m_Direction{ direction }, Command() {}

		virtual ~MoveCommand() = default;
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		virtual void Execute(const GameObject* Object) override;

	private:
		const glm::vec2 m_Direction;
	};
}