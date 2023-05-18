#pragma once
#include "Component.h"

namespace D2D
{
	enum class PowerupType
	{
		FireUp,
		BombUp,
		RemoteControl
	};

	class Powerup : public Component
	{
	public:
		Powerup() = default;
		virtual ~Powerup() override = default;

	private:
	};
}