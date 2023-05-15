#pragma once
#include "Component.h"

namespace D2D
{
	//This component currently only exists so that the player can recognize the ontriggeroverlap event as an explosion
	class ExplosionComponent final : public Component
	{
	public:
		ExplosionComponent() = default;
		virtual ~ExplosionComponent() override = default;
	private:
		int m_TestValue{};
	};
}