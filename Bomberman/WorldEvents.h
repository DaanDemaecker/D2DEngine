#pragma once
#include "Event.h"
#include "glm/glm.hpp"
#include "GameObject.h"

namespace D2D
{
	struct AnimationFinished final : public Event
	{
	public:
		AnimationFinished() = default;

		int test{ 5 };
	};

	struct BombExplodeEvent final : public Event
	{
	public:
		BombExplodeEvent() = default;

		int gridNumber{};
		int strength{};
	};
}