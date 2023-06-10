#pragma once

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
		float m_MarginX{};
		float m_MarginY{};
		float m_RaycastDistance{};
	};
}

