#pragma once
#include "Event.h"

namespace dae
{
	struct PlayerDieEvent final : public Event
	{
	public:
		PlayerDieEvent() = default;

		int playerIndex{ 0 };
	};
}