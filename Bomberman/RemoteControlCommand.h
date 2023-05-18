#pragma once
#include "Command.h"


namespace D2D
{
	class BombManagerComponent;

	class RemoteControlCommand final : public Command
	{
	public:
		RemoteControlCommand(BombManagerComponent* pBombManager) : Command(), m_pBombManager{ pBombManager } {}

		virtual ~RemoteControlCommand() = default;
		RemoteControlCommand(const RemoteControlCommand& other) = delete;
		RemoteControlCommand(RemoteControlCommand&& other) = delete;
		RemoteControlCommand& operator=(const RemoteControlCommand& other) = delete;
		RemoteControlCommand& operator=(RemoteControlCommand&& other) = delete;

		virtual void Execute() override;

	private:
		BombManagerComponent* m_pBombManager{};
	};
}



