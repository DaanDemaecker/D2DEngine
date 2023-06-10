#pragma once
#include "glm/glm.hpp"

namespace D2D
{
	class BaseEnemyComponent;
	class Transform;
	class Collider;
	class EnemyAnimator;

	enum class Direction
	{
		Up,
		Right,
		Down,
		Left
	};

	Direction Flip(Direction direction);

	Direction Rotate(Direction direction);

	glm::vec2 DirectionToVec(Direction direction);

	Direction VectToDirection(const glm::vec2 vec);



	class EnemyMovementBaseState
	{
	public:
		virtual ~EnemyMovementBaseState() = default;

		virtual void Update(EnemyAnimator* pAnimator, Transform* pTransform, Collider* pCollider, float speed) = 0;

		virtual void OnStateChange(BaseEnemyComponent* pEnemy) = 0;
	};

	class EnemyWanderState final : public EnemyMovementBaseState
	{
	public:
		EnemyWanderState() = delete;
		EnemyWanderState(float marginX, float marginY, float distance);
		~EnemyWanderState() = default;

		virtual void Update(EnemyAnimator* pAnimator, Transform* pTransform, Collider* pCollider, float speed) override;

		virtual void OnStateChange(BaseEnemyComponent* /*pEnemy*/) override {}

	private:
		Direction m_Direction{ Direction::Left };

		float m_TurnTimer{5.f};
		const float m_TurnTime{5.f};

		float m_MarginX{};
		float m_MarginY{};
		float m_RaycastDistance{};

		bool ShouldFlip(Transform* pTransform, Collider* pCollider);

		bool Shouldturn(Transform* pTransform, Collider* pCollider);
	};
}

