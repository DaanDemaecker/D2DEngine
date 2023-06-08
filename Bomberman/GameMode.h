#pragma once
#include "Component.h"

namespace D2D
{
	class GameMode final : public Component
	{
	public:
		GameMode() = default;
		virtual ~GameMode() override = default;

		virtual void OnSceneLoad() override;

	};
}