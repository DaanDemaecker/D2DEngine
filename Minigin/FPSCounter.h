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
		std::weak_ptr<TextComponent> m_pTextComponent;

		float m_Timer{};
		const float m_TimeToUpdate = 2.f;

	};

}