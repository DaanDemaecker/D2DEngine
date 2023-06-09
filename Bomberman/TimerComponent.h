#pragma once
#include "Component.h"
#include "Subject.h"
#include "Observer.h"

namespace D2D
{
	class TextComponent;

	class TimerComponent final : public Component, public Subject, public Observer
	{
	public:
		TimerComponent() { m_Timer = m_Time; }
		~TimerComponent() = default;

		virtual void Update() override;

		virtual void Notify(const Event& event) override;

	private:
		TextComponent* m_pTextComponent = nullptr;;

		float m_SecondTimer{1.0f};
		int m_Timer{ 200 };
		const int m_Time{ 200 };
	};
}

