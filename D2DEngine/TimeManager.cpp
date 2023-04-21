#include "TimeManager.h"

void D2D::TimeManager::SetDeltaTime(float dt)
{
	m_DeltaTime = dt;
	m_Fps = static_cast<int>(1.0f / dt);
}
