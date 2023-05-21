#pragma once
#include "Command.h"
#include <vector>

namespace D2D
{
	class ButtonComponent;

	class ButtonActivateCommand final : public Command
	{
	public:
		ButtonActivateCommand() = default;
		ButtonActivateCommand(std::vector<ButtonComponent*> pButtons);
		
		~ButtonActivateCommand() = default;

		virtual void Execute() override;

	private:
		std::vector<ButtonComponent*> m_pButtons{};
	};
}

