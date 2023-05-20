#pragma once
#include "Command.h"
#include <vector>

namespace D2D
{
	class GameObject;
	class ButtonComponent;

	class MenuScrollCommand final : public Command
	{
	public:
		MenuScrollCommand(int direction, std::vector<ButtonComponent*> pButtons, GameObject* pSelector);

		virtual ~MenuScrollCommand() = default;
		MenuScrollCommand(const MenuScrollCommand& other) = delete;
		MenuScrollCommand(MenuScrollCommand&& other) = delete;
		MenuScrollCommand& operator=(const MenuScrollCommand& other) = delete;
		MenuScrollCommand& operator=(MenuScrollCommand&& other) = delete;

		virtual void Execute() override;

	private:
		int m_Direction{};
		std::vector<ButtonComponent*> m_pButtons{};
		GameObject* m_pSelector{};
	};
}

