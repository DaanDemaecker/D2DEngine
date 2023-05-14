#pragma once
#include "Event.h"
#include "Collider.h"

namespace D2D
{
	struct TriggerOverlapEvent final : public Event
	{
	public:
		TriggerOverlapEvent() = default;

		Collider* Self{};
		Collider* Other{};
	};
}