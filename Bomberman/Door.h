#pragma once
#include "Component.h"
#include "Subject.h"
#include "Observer.h"

namespace D2D
{
	class Door : public Component, public Subject, public Observer
	{
	public:
		Door() = default;
		virtual ~Door() override = default;

		virtual void OnTriggerEnter(const Collider* pCollider) override;

		virtual void Notify(const Event& event) override;

		virtual void Update() override;

	private:
		bool m_EnemiesDead{};

		float m_Timer{};
		const float m_Time{ 4.0f };
	};
}