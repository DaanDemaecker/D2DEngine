#pragma once
#include "Event.h"

namespace D2D
{
	struct PlayerDieEvent final : public Event
	{
	public:
		PlayerDieEvent() = default;

		int playerIndex{ 0 };
	};
}