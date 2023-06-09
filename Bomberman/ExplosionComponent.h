#pragma once
#include "Component.h"
#include "Subject.h"

namespace D2D
{
	class ExplosionComponent final : public Component, public Subject
	{
	public:
		ExplosionComponent() = default;
		virtual ~ExplosionComponent() override = default;

		void SetGridIndex(int index) { m_GridIndex = index; }

		virtual void Destroy() override;

	private:
		int m_GridIndex{};
	};
}