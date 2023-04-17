#pragma once

namespace dae
{
	enum class GamepadButton
	{
		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		ButtonSouth = 0x1000,
		ButtonEast = 0x2000,
		ButtonWest = 0x4000,
		ButtonNorth = 0x8000
	};

	enum class keyState
	{
		Down,
		Up,
		pressed
	};
}