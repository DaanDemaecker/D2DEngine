#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPSCounter final : public Component
	{
	public:
		FPSCounter() = default;
		virtual ~FPSCounter() override = default;

		virtual void Update() override;

	private:
		TextComponent* m_pTextComponent{nullptr};

		float m_Timer{};
		const float m_TimeToUpdate = 2.f;

	};

}