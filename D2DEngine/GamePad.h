#pragma once
#include "Enums.h"
#include "GamepadImpl.h"
#include <memory>

namespace D2D
{
	class GamePad
	{
	public:
		GamePad(int index) { m_pImpl = std::make_unique<GamepadImpl>(index); }
		~GamePad() = default;

		GamePad(const GamePad& other) = delete;
		GamePad(GamePad&& other) = delete;

		GamePad& operator=(const GamePad& other) = delete;
		GamePad& operator=(GamePad&& other) = delete;

		void Update()
		{
			m_pImpl->Update();
		}

		bool IsPressed(GamepadButton button)
		{
			return m_pImpl->IsPressed(button);
		}

		bool IsUp(GamepadButton button)
		{
			return m_pImpl->IsUp(button);
		}

		bool IsDown(GamepadButton button)
		{
			return m_pImpl->IsDown(button);
		}

		int GetIndex() const { return m_pImpl->GetIndex(); }

		void SetShouldDelete(bool shouldDelete) { m_pImpl->SetShouldDelete(shouldDelete); }

		bool ShouldDelete() const { return m_pImpl->ShouldDelete(); }

	private:
		std::unique_ptr<GamepadImpl> m_pImpl;
	};
}

