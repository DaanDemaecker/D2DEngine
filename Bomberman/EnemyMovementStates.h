#pragma once
#include "glm/glm.hpp"

namespace D2D
{
	class BaseEnemyComponent;
	class Transform;
	class Collider;

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

		virtual void SetEnemy(BaseEnemyComponent* pEnemy) { m_pEnemy = pEnemy; }

		virtual void Update(Transform* pTransform, Collider* pCollider, float speed) = 0;

	protected:
		BaseEnemyComponent* m_pEnemy{};
	};

	class EnemyWanderState final : public EnemyMovementBaseState
	{
	public:
		EnemyWanderState() = delete;
		EnemyWanderState(float marginX, float marginY, float distance);
		~EnemyWanderState() = default;

		virtual void Update(Transform* pTransform, Collider* pCollider, float speed) override;

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

