#include "FPSCounter.h"
#include "TextComponent.h"
#include "Time.h"

void dae::FPSCounter::Update()
{
	if (m_Timer >= 0)
	{
		m_Timer -= Time::GetInstance().GetDeltaTime();
	}
	else
	{
		if (m_pTextComponent.expired())
		{
			m_pTextComponent = GetComponent<TextComponent>();

			if (m_pTextComponent.expired())
			{
				return;
			}
		}

		m_Timer = m_TimeToUpdate;

		m_pTextComponent.lock()->SetText(std::to_string(Time::GetInstance().GetFps()) + " FPS");
	}
}
