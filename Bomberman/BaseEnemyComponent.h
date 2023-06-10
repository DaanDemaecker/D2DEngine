#pragma once
#include "Component.h"
#include "Subject.h"
#include "EnemyMovementStates.h"

namespace D2D
{
	class Transform;
	class Collider;
	class EnemyAnimator;

	enum class EnemyType
	{
		Balloom,
		Oneal,
		Doll,
		Minvo
	};

	class BaseEnemyComponent : public Component, public Subject
	{
	public:
		BaseEnemyComponent() = default;
		virtual ~BaseEnemyComponent() override = default;

		virtual void Update();

		void SetVariables(EnemyType type, float speed, Collider* pCollider, Collider* pTrigger);

		void SetMovementState(std::unique_ptr<EnemyMovementBaseState> pState);

		virtual void OnTriggerEnter(const Collider* pCollider) override;

	private:
		std::unique_ptr<EnemyMovementBaseState> m_pMovement{};

		Collider* m_pCollider{};
		Collider* m_pTrigger{};


	protected:
		bool m_IsDead{ false };

		EnemyType m_Type{};
		float m_Speed{};

		EnemyAnimator* m_pAnimator{};

		enum class Direction
		{
			Up,
			Right,
			Down,
			Left
		};

	};
}