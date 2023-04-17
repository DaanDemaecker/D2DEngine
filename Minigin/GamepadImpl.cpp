#include "GamepadImpl.h"
#include <winerror.h>
#include <Xinput.h>

dae::GamepadImpl::GamepadImpl(int index)
	:m_GamepadIndex{index}
{
	XINPUT_STATE state;

	DWORD result = XInputGetState(m_GamepadIndex, &state);
	if (result == ERROR_DEVICE_NOT_CONNECTED)
	{
		m_ShouldDelete = true;
	}
	else
	{
		m_State = state.Gamepad.wButtons;
	}
}

dae::GamepadImpl::~GamepadImpl()
{
}

void dae::GamepadImpl::Update()
{
	auto previousState = m_State;

	XINPUT_STATE state;

	DWORD result = XInputGetState(m_GamepadIndex, &state);
	if (result == ERROR_DEVICE_NOT_CONNECTED)
	{
		m_ShouldDelete = true;
		return;
	}

	m_State = state.Gamepad.wButtons;

	auto changes = m_State ^ previousState;

	m_ButtonsDown = changes & m_State;
	m_ButtonsUp = changes & (~m_State);
}

bool dae::GamepadImpl::IsPressed(GamepadButton button)
{
	return m_State & static_cast<int>(button);
}

bool dae::GamepadImpl::IsUp(GamepadButton button)
{
	return m_ButtonsUp & static_cast<int>(button);
}

bool dae::GamepadImpl::IsDown(GamepadButton button)
{
	return m_ButtonsDown & static_cast<int>(button);
}