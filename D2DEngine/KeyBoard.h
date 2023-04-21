#pragma once
#include "KeyBoardImpl.h"

namespace D2D
{
	class KeyBoard final
	{
	public:
		KeyBoard()
		{
			m_pImpl = std::make_unique<KeyBoardImpl>();
		}


		~KeyBoard() = default;

		KeyBoard(const KeyBoard& other) = delete;
		KeyBoard(KeyBoard&& other) = delete;

		KeyBoard& operator=(const KeyBoard& other) = delete;
		KeyBoard& operator=(KeyBoard&& other) = delete;

		void Update()
		{
			m_pImpl->Update();
		}

		bool IsPressed(SDL_Scancode button)
		{
			return m_pImpl->IsPressed(button);
		}

		bool IsUp(SDL_Scancode button)
		{
			return m_pImpl->IsUp(button);
		}

		bool IsDown(SDL_Scancode button)
		{
			return m_pImpl->IsDown(button);
		}


	private:
		std::unique_ptr<KeyBoardImpl> m_pImpl;
	};
}

