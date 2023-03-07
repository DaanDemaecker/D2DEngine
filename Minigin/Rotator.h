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



	private:
		float m_Distance{ 20.f };
		float m_RotSpeed{glm::radians(90.f)};
		float m_CurrentAngle{};
	};
}

