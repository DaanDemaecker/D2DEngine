#pragma once
#include "BaseEnemyComponent.h"

namespace D2D
{
	class Transform;
	class Collider;
	class EnemyAnimator;

	class BalloonEnemy final : public BaseEnemyComponent
	{
	public:
		BalloonEnemy() = default;
		virtual ~BalloonEnemy() override = default;

		void SetSpeed(float speed) { m_Speed = speed; }

		virtual void Update() override;

		virtual void OnTriggerEnter(const Collider* pCollider) override;

	private:
		float m_Speed{};

		EnemyAnimator* m_pAnimator{};

		Direction m_CurrentDirection{ BaseEnemyComponent::Direction::Right };

	};
}