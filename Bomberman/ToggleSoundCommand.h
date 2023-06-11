#pragma once
#include "Command.h"

namespace D2D
{
	class ToggleSoundCommand final : public Command
	{
	public:
		ToggleSoundCommand() = default;

		virtual ~ToggleSoundCommand() = default;

		virtual void Execute() override;
	};
}



