#pragma once
#include "Component.h"
#include "Subject.h"

namespace D2D
{
	class Transform;

	enum class EnemyType
	{
		Balloom
	};

	class BaseEnemyComponent : public Component, public Subject
	{
	public:
		BaseEnemyComponent() = default;
		virtual ~BaseEnemyComponent() override = default;

	protected:
		bool m_IsDead{ false };

		EnemyType m_Type{};

		enum class Direction
		{
			Up,
			Right,
			Down,
			Left
		};

	};
}