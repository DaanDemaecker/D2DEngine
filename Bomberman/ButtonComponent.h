#pragma once
#include "Component.h"

namespace D2D
{
	class ButtonComponent final : public Component
	{
	public:
		ButtonComponent() = default;
		~ButtonComponent() = default;

		void SetSelected(bool selected) { m_Selected = selected; }
		bool GetSelected() const { return m_Selected; }

	private:
		bool m_Selected{ false };

	};
}

