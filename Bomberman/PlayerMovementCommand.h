#pragma once
#include <glm/glm.hpp>
#include "Command.h"

namespace D2D
{
	class PlayerComponent;

	class PlayerMovementCommand final : public Command
	{
	public:
		PlayerMovementCommand(const glm::vec2& direction, PlayerComponent* pPlayer) : Command{}, m_Direction{ direction }, m_pPlayer{pPlayer} {}

		virtual ~PlayerMovementCommand() = default;
		PlayerMovementCommand(const PlayerMovementCommand& other) = delete;
		PlayerMovementCommand(PlayerMovementCommand&& other) = delete;
		PlayerMovementCommand& operator=(const PlayerMovementCommand& other) = delete;
		PlayerMovementCommand& operator=(PlayerMovementCommand&& other) = delete;

		virtual void Execute() override;

	private:
		glm::vec2 m_Direction;
		PlayerComponent* m_pPlayer;
	};
}