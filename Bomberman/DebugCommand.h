#pragma once
#include "Command.h"
#include <functional>

namespace D2D
{
	class DebugCommand final : public Command
	{
	public:
		DebugCommand(std::function<void()> fn) : Command(), m_pDebugFunction{ fn } {}

		virtual ~DebugCommand() = default;
		DebugCommand(const DebugCommand& other) = delete;
		DebugCommand(DebugCommand&& other) = delete;
		DebugCommand& operator=(const DebugCommand& other) = delete;
		DebugCommand& operator=(DebugCommand&& other) = delete;

		virtual void Execute() override;

	private:
		std::function<void()> m_pDebugFunction;
	};
}

