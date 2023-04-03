#pragma once

namespace dae
{
	enum class GamepadButton
	{
		DPAD_UP = 0x0001,
		DPAD_DOWN = 0x0002,
		DPAD_LEFT = 0x0004,
		DPAD_RIGHT = 0x0008,
		START = 0x0010,
		BACK = 0x0020,
		LEFT_THUMB = 0x0040,
		RIGHT_THUMB = 0x0080,
		LEFT_SHOULDER = 0x0100,
		RIHGT_SHOULDER = 0x0200,
		BUTTON_SOUTH = 0x1000,
		BUTTON_EAST = 0x2000,
		BUTTON_WEST = 0x4000,
		BUTTON_NORTH = 0x8000
	};

	enum class keyState
	{
		down,
		up,
		pressed
	};
}