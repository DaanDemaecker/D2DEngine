#pragma once
#include <windows.h>
#include <memory>
#include <vector>
#include <SDL_scancode.h>

namespace dae
{
	class KeyBoardImpl
	{
	public:

		KeyBoardImpl();
		~KeyBoardImpl() = default;

		KeyBoardImpl(const KeyBoardImpl& other) = delete;
		KeyBoardImpl(KeyBoardImpl&& other) = delete;

		KeyBoardImpl& operator=(const KeyBoardImpl& other) = delete;
		KeyBoardImpl& operator=(KeyBoardImpl&& other) = delete;

		void Update();

		bool IsPressed(SDL_Scancode button) { return m_Pressed[button]; }

		bool IsUp(SDL_Scancode button) { return m_Up[button]; }

		bool IsDown(SDL_Scancode button) { return m_Down[button]; }

	private:
		std::vector<Uint8> m_Pressed;
		std::vector<Uint8> m_Up;
		std::vector<Uint8> m_Down;
	};
}

