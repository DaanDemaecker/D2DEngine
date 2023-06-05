#pragma once
#include "Command.h"
#include <functional>

namespace D2D
{
	class GameObject;

	class DebugCommand final : public Command
	{
	public:
		DebugCommand(GameObject* object) : Command(), m_pGameObject{ object } {}

		virtual ~DebugCommand() = default;
		DebugCommand(const DebugCommand& other) = delete;
		DebugCommand(DebugCommand&& other) = delete;
		DebugCommand& operator=(const DebugCommand& other) = delete;
		DebugCommand& operator=(DebugCommand&& other) = delete;

		virtual void Execute() override;

	private:
		GameObject* m_pGameObject{};
	};
}

