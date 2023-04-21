#pragma once
#include "Component.h"
#include "PlayerComponent.h"
#include "Observer.h"

namespace dae
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
		
		void BindPlayer(PlayerComponent* pPlayer);

	private:
		const int m_StartHealth{ 5 };
		int m_PlayerHealth{};
		PlayerComponent* m_pPlayer{};
		TextComponent* m_pTextComponent{};

		bool m_ShouldUpdateText{ true };

		void UpdateLivesDisplay();
	};
}

