#pragma once
#include "Enums.h"
#include <Windows.h>
//#include <Xinput.h>

namespace D2D
{
	class GamepadImpl
	{
	public:
		GamepadImpl(int index);
		~GamepadImpl();

		GamepadImpl(const GamepadImpl& other) = delete;
		GamepadImpl(GamepadImpl&& other) = delete;

		GamepadImpl& operator=(const GamepadImpl& other) = delete;
		GamepadImpl& operator=(GamepadImpl&& other) = delete;

		void Update();

		bool IsPressed(GamepadButton button);

		bool IsUp(GamepadButton button);

		bool IsDown(GamepadButton button);

		int GetIndex() const { return m_GamepadIndex; }

		bool ShouldDelete() const { return m_ShouldDelete; }

	private:
		int m_GamepadIndex;
		bool m_ShouldDelete{false};

		int m_State;
		int m_ButtonsDown;
		int m_ButtonsUp;
	};
}
