#pragma once
#include "Component.h"
#include <functional>

namespace D2D
{
	class ButtonComponent final : public Component
	{
	public:
		ButtonComponent() = default;
		~ButtonComponent() = default;

		void SetSelected(bool selected) { m_Selected = selected; }
		bool GetSelected() const { return m_Selected; }

		void Execute();

		void SetFunction(std::function<void()> function) { m_Function = function; }

	private:
		bool m_Selected{ false };

		std::function<void()> m_Function{};
	};
}

