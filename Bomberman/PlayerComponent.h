#pragma once
#include "Component.h"
#include "Subject.h"
#include "PlayerEvents.h"
#include "Observer.h"

namespace D2D
{
	class Transform;
	class PlayerAnimator;
	class Collider;
	enum class PowerupType;

	class PlayerComponent final : public Component, public Subject, public Observer
	{
	public:
		PlayerComponent() = default;
		virtual ~PlayerComponent() override = default;

		virtual void FixedUpdate() override;

		virtual void LateUpdate() override;

		void SetPlayerIndex(int idx) { m_PlayerIndex = idx; m_PlayerDieEvent.playerIndex = idx; }

		void SetSpeed(float speed) { m_Speed = speed; }

		void SetPlayerHalfWidth(float halfWidth) { m_PlayerHalfWidth = halfWidth; }

		void SetLevelWidth(float width) { m_LevelWidth = width; }

		void PlaceBomb();

		void KillPlayer();

		void PickupItem();

		void AddMovement(const glm::vec2& direction) { m_Movement += direction; }

		virtual void OnTriggerEnter(const Collider* pCollider) override;

		void PowerupCollected(PowerupType powerupType);

		virtual void Notify(const Event& event) override;
	
	private:
		Transform* m_pTransform{};
		PlayerAnimator* m_pAnimator{};

		float m_PlayerHalfWidth{};
		float m_LevelWidth{};

		glm::vec2 m_Movement{};
		float m_Speed{ 20 };

		bool m_IsDead{ false };

		int m_PlayerIndex{};
		PlayerDieEvent m_PlayerDieEvent{};
		PickupItemEvent m_PickupItemEvent{};
		PlaceBombEvent m_PlaceBombEvent{};
	};
}
