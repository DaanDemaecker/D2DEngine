#include "pch.h"
#include "TimerComponent.h"
#include "TimeManager.h"
#include "WorldEvents.h"
#include "TextComponent.h"

void D2D::TimerComponent::Update()
{
	if (m_Timer <= 0)
		return;

	m_SecondTimer -= TimeManager::GetInstance().GetDeltaTime();

	if (m_SecondTimer <= 0)
	{
		m_SecondTimer += 1.f;
		m_Timer--;

		if (m_Timer == 0)
		{
			NotifyObservers(TimerOverEvent());
		}

		if (m_pTextComponent == nullptr)
		{
			m_pTextComponent = GetComponent<TextComponent>().get();
		}

		if (m_pTextComponent != nullptr)
		{
			m_pTextComponent->SetText("TIME  " + std::to_string(m_Timer));
		}
	}

}
