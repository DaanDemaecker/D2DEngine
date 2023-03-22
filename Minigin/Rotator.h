#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class Rotator final : public Component
	{
	public:
		Rotator() = default;
		virtual ~Rotator() override = default;

		virtual void Update() override;

		void SetRotSpeed(float newSpeed) { m_RotSpeed = newSpeed/5; }

	private:
		float m_Distance{ 40.f };
		float m_RotSpeed{glm::radians(180.f)};
		float m_CurrentAngle{};
	};
}

