#pragma once
#include "Command.h"


namespace D2D
{
	class PlayerComponent;

	class PlaceBombCommand final : public Command
	{
	public:
		PlaceBombCommand(PlayerComponent* player) : Command(), m_pPlayerComponent{player} {}

		virtual ~PlaceBombCommand() = default;
		PlaceBombCommand(const PlaceBombCommand& other) = delete;
		PlaceBombCommand(PlaceBombCommand&& other) = delete;
		PlaceBombCommand& operator=(const PlaceBombCommand& other) = delete;
		PlaceBombCommand& operator=(PlaceBombCommand&& other) = delete;

		virtual void Execute() override;

	private:
		PlayerComponent* m_pPlayerComponent{};
	};
}

