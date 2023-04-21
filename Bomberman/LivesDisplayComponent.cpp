#include "pch.h"
#include "LivesDisplayComponent.h"
#include "PlayerEvents.h"
#include "TextComponent.h"
#include "PlayerComponent.h"

D2D::LivesDisplayComponent::LivesDisplayComponent()
	:Component()
{
	m_PlayerHealth = m_StartHealth;
}

void D2D::LivesDisplayComponent::Notify(const Event& event)
{
	if (auto playerDieEvent{ dynamic_cast<const PlayerDieEvent*>(&event) })
	{
		--m_PlayerHealth;
		m_ShouldUpdateText = true;
	}
}

void D2D::LivesDisplayComponent::Update()
{
	if (m_ShouldUpdateText)
	{
		UpdateLivesDisplay();
		m_ShouldUpdateText = false;
	}
}

void D2D::LivesDisplayComponent::UpdateLivesDisplay()
{
	if (m_pTextComponent == nullptr)
	{
		m_pTextComponent = GetComponent<TextComponent>().get();
	}

	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetText("LEFT: " + std::to_string(m_PlayerHealth));
	}
}

void D2D::LivesDisplayComponent::BindPlayer(PlayerComponent* pPlayer)
{
	m_pPlayer = pPlayer;
}
