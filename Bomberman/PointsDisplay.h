#pragma once
#include "Component.h"
#include "PlayerComponent.h"
#include "Observer.h"

namespace D2D
{
	class TextComponent;
	class PlayerComponent;

	class PointsDisplay : public Component, public Observer
	{
	public:
		PointsDisplay();
		virtual ~PointsDisplay() override = default;

		virtual void Notify(const Event& event);

		virtual void Update() override;

	private:
		int m_Score{};

		TextComponent* m_pTextComponent{};

		bool m_ShouldUpdateText{ true };

		void UpdatePointsDisplay();
	};
}