#pragma once
#include "Component.h"

namespace D2D
{
	class MainMenuComponent final : public Component
	{
	public:
		MainMenuComponent() = default;
		virtual ~MainMenuComponent() = default;

		void SinglePlayerButton();
		void CoopButton();
		void VersusButton();

	private:

	};
}

