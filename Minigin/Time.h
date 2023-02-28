#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void SetDeltaTime(float dt) { m_DeltaTime = dt; }
		float GetDeltaTime() const { return m_DeltaTime; }
	private:
		float m_DeltaTime = 0;
	};
}

