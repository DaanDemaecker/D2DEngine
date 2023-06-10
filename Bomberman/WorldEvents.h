#pragma once
#include "Event.h"
#include "glm/glm.hpp"
#include "GameObject.h"
#include "BaseEnemyComponent.h"

namespace D2D
{
	struct AnimationFinished final : public Event
	{
	public:
		AnimationFinished() = default;

		int test{ 5 };
	};

	struct BombExplodeEvent final : public Event
	{
	public:
		BombExplodeEvent() = default;

		int gridNumber{};
		int strength{};
	};

	struct ExplosionOverEvent final : public Event
	{
	public:
		ExplosionOverEvent() = default;

		int gridIndex{};
	};

	struct EnemySpawnEvent final : public Event
	{
	public:
		EnemySpawnEvent() = default;

		BaseEnemyComponent* pEnemy{};
	};

	struct EnemyDieEvent final : public Event
	{
	public:
		EnemyDieEvent() = default;

		BaseEnemyComponent* pEnemy{};
		EnemyType enemyType{};
	};

	struct TimerOverEvent final : public Event
	{
	public:
		TimerOverEvent() = default;
	};

	struct StartGameEvent final : public Event
	{
	public:
		StartGameEvent() = default;
	};

	struct EnemiesDeadEvent final : public Event
	{
	public:
		EnemiesDeadEvent() = default;
	};

	struct LevelCompleteEvent final : public Event
	{
	public:
		LevelCompleteEvent() = default;
	};
}