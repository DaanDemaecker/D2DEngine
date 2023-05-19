#pragma once
#include "Component.h"
#include "Subject.h"

namespace D2D
{
	class TextComponent;

	class TimerComponent final : public Component, public Subject
	{
	public:
		TimerComponent() = default;
		~TimerComponent() = default;

		virtual void Update() override;


	private:
		TextComponent* m_pTextComponent = nullptr;;

		float m_SecondTimer{1.0f};
		int m_Timer{ 200 };
	};
}

