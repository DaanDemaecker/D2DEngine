#include "FPSCounter.h"
#include "TextComponent.h"
#include "TimeManager.h"

void D2D::FPSCounter::Update()
{
	if (m_Timer >= 0)
	{
		m_Timer -= TimeManager::GetInstance().GetDeltaTime();
	}
	else
	{
		if (m_pTextComponent == nullptr)
		{
			m_pTextComponent = GetComponent<TextComponent>().get();
		}


		m_Timer = m_TimeToUpdate;

		m_pTextComponent->SetText(std::to_string(TimeManager::GetInstance().GetFps()) + " FPS");
	}
}
