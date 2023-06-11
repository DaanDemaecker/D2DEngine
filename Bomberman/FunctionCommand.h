#pragma once
#include "Command.h"
#include <functional>

#include <iostream>

namespace D2D
{
	class FunctionCommand final : public Command
	{
	public:
		FunctionCommand(const std::function<void()>& function) : Command() { m_Function = function; }

		virtual ~FunctionCommand() = default;

		virtual void Execute() override;

	private:
		std::function<void()> m_Function{};
	};
}



