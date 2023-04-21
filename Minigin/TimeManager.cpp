#include "TimeManager.h"

void dae::TimeManager::SetDeltaTime(float dt)
{
	m_DeltaTime = dt;
	m_Fps = static_cast<int>(1.0f / dt);
}
