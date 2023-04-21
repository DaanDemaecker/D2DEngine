#include "KeyBoardImpl.h"
#include "SDL.h"
#include <algorithm>
#include <functional>

D2D::KeyBoardImpl::KeyBoardImpl()
{
	m_Pressed.resize(SDL_NUM_SCANCODES);

	m_Down.resize(SDL_NUM_SCANCODES);

	m_Up.resize(SDL_NUM_SCANCODES);
}

void D2D::KeyBoardImpl::Update()
{
	const auto test = SDL_GetKeyboardState(nullptr);

	std::vector<Uint8> currentState;
	currentState.resize(SDL_NUM_SCANCODES);

	for (size_t i{}; i < currentState.size(); i++)
	{
		currentState[i] = test[i];
	}

	std::vector<Uint8> changes;
	changes.resize(SDL_NUM_SCANCODES);

	std::transform(currentState.begin(), currentState.end(), m_Pressed.begin(), changes.begin(), std::bit_xor<Uint8>());

	std::transform(changes.begin(), changes.end(), currentState.begin(), m_Down.begin(), std::bit_and<Uint8>());

	std::transform(changes.begin(), changes.end(), currentState.begin(), m_Up.begin(), [](Uint8 first, Uint8 second)
		{return std::bit_and<Uint8>()(first,~second); });

	m_Pressed = std::move(currentState);
}
