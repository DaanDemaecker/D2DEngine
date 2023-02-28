#include "FPSCounter.h"
#include "TextComponent.h"
#include "Time.h"

void dae::FPSCounter::Update()
{
	m_AccumulatedTime += Time::GetInstance().GetDeltaTime();
	if (++m_FramesSinceLastUpdate >= m_FramesToUpdate)
	{
		if (m_pTextComponent.expired())
		{
			m_pTextComponent = GetComponent<TextComponent>();

			if (m_pTextComponent.expired())
			{
				return;
			}
		}

		int fps = static_cast<int>(m_FramesToUpdate / m_AccumulatedTime);

		m_FramesSinceLastUpdate = 0;
		m_AccumulatedTime = 0;

		m_pTextComponent.lock()->SetText(std::to_string(fps) + " FPS");
	}
}
