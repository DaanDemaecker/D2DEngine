#include "pch.h"
#include "LivesDisplayComponent.h"
#include "PlayerEvents.h"
#include "TextComponent.h"
#include "PlayerComponent.h"
#include "GameData.h"

D2D::LivesDisplayComponent::LivesDisplayComponent()
	:Component()
{
	m_PlayerHealth = m_StartHealth;
	GameData::GetInstance().SetLives(m_PlayerHealth);
}

void D2D::LivesDisplayComponent::Notify(const Event& event)
{
	if (auto playerDieEvent{ dynamic_cast<const PlayerDieEvent*>(&event) })
	{
		--m_PlayerHealth;
		GameData::GetInstance().SetLives(m_PlayerHealth);
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
