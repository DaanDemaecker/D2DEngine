#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void SetDeltaTime(float dt) { m_DeltaTime = dt; }
		float GetDeltaTime() const { return m_DeltaTime; }

		void SetFixedTime(float ft) { m_FixedTime = ft; }
		float GetFixedTime() const { return m_FixedTime; }

	private:
		float m_DeltaTime = 0;
		float m_FixedTime = 0;
	};
}

