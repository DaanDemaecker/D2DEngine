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

		virtual void OnTriggerEnter(const Collider* pCollider) override;

		void SetType(PowerupType type) { m_Type = type; }

	private:
		PowerupType m_Type{};


	};
}