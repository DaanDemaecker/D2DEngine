#pragma once
#include "Component.h"

namespace D2D
{
	class MainMenuComponent final : public Component
	{
	public:
		MainMenuComponent() = default;
		virtual ~MainMenuComponent() = default;

		virtual void OnSceneLoad() override;

		void SinglePlayerButton();
		void CoopButton();
		void VersusButton();

	private:

	};
}

