#include "GamepadImpl.h"
#include <winerror.h>

dae::GamepadImpl::GamepadImpl(int index)
	:m_GamepadIndex{index}
{
	DWORD result = XInputGetState(m_GamepadIndex, &m_State);
	if (result == ERROR_DEVICE_NOT_CONNECTED)
	{
		m_ShouldDelete = true;
	}
}

dae::GamepadImpl::~GamepadImpl()
{
}

void dae::GamepadImpl::Update()
{
	auto previousState = m_State;

	DWORD result = XInputGetState(m_GamepadIndex, &m_State);
	if (result == ERROR_DEVICE_NOT_CONNECTED)
	{
		m_ShouldDelete = true;
		return;
	}

	auto changes = m_State.Gamepad.wButtons ^ previousState.Gamepad.wButtons;

	m_ButtonsDown = changes & m_State.Gamepad.wButtons;
	m_ButtonsUp = changes & (~m_State.Gamepad.wButtons);
}

bool dae::GamepadImpl::IsPressed(GamepadButton button)
{
	return m_State.Gamepad.wButtons & static_cast<int>(button);
}

bool dae::GamepadImpl::IsUp(GamepadButton button)
{
	return m_ButtonsUp & static_cast<int>(button);
}

bool dae::GamepadImpl::IsDown(GamepadButton button)
{
	return m_ButtonsDown & static_cast<int>(button);
}