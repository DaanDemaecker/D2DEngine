#pragma once
#include "Component.h"
#include "Subject.h"
#include "PlayerEvents.h"

namespace dae
{

	class PlayerComponent final : public Component, public Subject
	{
	public:
		PlayerComponent() = default;
		virtual ~PlayerComponent() override = default;

		virtual void Update() override;

		void SetPlayerIndex(int idx) { m_PlayerIndex = idx; m_PlayerDieEvent.playerIndex = idx; }

		void KillPlayer();
	
	private:
		int m_PlayerIndex{};
		PlayerDieEvent m_PlayerDieEvent{};
	};
}
