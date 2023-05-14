#pragma once
#include "Component.h"
#include "Subject.h"
#include "PlayerEvents.h"
#include "Observer.h"

namespace D2D
{
	class Transform;
	class PlayerAnimator;

	class PlayerComponent final : public Component, public Subject, public Observer
	{
	public:
		PlayerComponent() = default;
		virtual ~PlayerComponent() override = default;

		virtual void Update() override;

		void SetPlayerIndex(int idx) { m_PlayerIndex = idx; m_PlayerDieEvent.playerIndex = idx; }

		void SetSpeed(float speed) { m_Speed = speed; }

		void PlaceBomb();

		void KillPlayer();

		void PickupItem();

		void AddMovement(const glm::vec2& direction) { m_Movement += direction; }

		virtual void Notify(const Event& event);
	
	private:
		Transform* m_pTransform{};
		PlayerAnimator* m_pAnimator{};

		glm::vec2 m_Movement{};
		float m_Speed{ 20 };

		int m_PlayerIndex{};
		PlayerDieEvent m_PlayerDieEvent{};
		PickupItemEvent m_PickupItemEvent{};
		PlaceBombEvent m_PlaceBombEvent{};
	};
}
