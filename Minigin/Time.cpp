#include "Time.h"

void dae::Time::SetDeltaTime(float dt)
{
	m_DeltaTime = dt;
	m_Fps = static_cast<int>(1.0f / dt);
}
