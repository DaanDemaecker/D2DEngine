#pragma once
#include "Event.h"
#include "glm/glm.hpp"
#include "Powerup.h"

namespace D2D
{
	struct PlayerDieEvent final : public Event
	{
	public:
		PlayerDieEvent() = default;

		int playerIndex{ 0 };
	};

	struct PickupItemEvent final : public Event
	{
	public:
		PickupItemEvent() = default;
	};

	struct PlaceBombEvent final : public Event
	{
	public:
		PlaceBombEvent() = default;

		glm::vec2 position{};
	};

	struct PowerupCollectedEvent final : public Event
	{
	public:
		PowerupCollectedEvent() = default;

		PowerupType type{};
	};
}