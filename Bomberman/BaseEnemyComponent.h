#pragma once
#include "Component.h"

namespace D2D
{
	class Transform;

	class BaseEnemyComponent : public Component
	{
	public:
		BaseEnemyComponent() = default;
		virtual ~BaseEnemyComponent() override = default;

	protected:
		bool m_IsDead{ false };

		enum class Direction
		{
			Up,
			Right,
			Down,
			Left
		};

	};
}