#pragma once
#include "Component.h"
#include "Subject.h"
#include "WorldEvents.h"

namespace D2D
{

	class BombComponent final : public Component, public Subject
	{
	public:
		BombComponent() = default;
		virtual ~BombComponent() override = default;

		virtual void Update() override;

		void SetGridNumber(int number) { m_GridNumber = number; }
		void SetBombStrength(int strength) { m_BombStrength = strength; }

		void ExplodeBomb();

		void InstantExplosion();

		int GetGridNumber() const { return m_GridNumber; }

	private:
		int m_BombStrength{};
		int m_GridNumber{};
		float m_Timer{ 2.5f };
		const float m_InstantExplosionTimer{ 0.05f };
	};
}