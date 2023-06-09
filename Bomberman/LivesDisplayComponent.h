#pragma once
#include "Component.h"
#include "PlayerComponent.h"
#include "Observer.h"

namespace D2D
{
	class TextComponent;
	class PlayerComponent;

	class LivesDisplayComponent : public Component, public Observer
	{
	public:
		LivesDisplayComponent();
		virtual ~LivesDisplayComponent() override = default;

		virtual void Notify(const Event& event);

		virtual void Update() override;

		virtual void OnSceneLoad() override;

	private:
		const int m_StartHealth{ 3 };
		int m_PlayerHealth{};

		TextComponent* m_pTextComponent{};

		bool m_ShouldUpdateText{ true };

		void UpdateLivesDisplay();
	};
}

