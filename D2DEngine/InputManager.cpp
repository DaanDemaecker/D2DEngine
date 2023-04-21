#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>
#include "KeyBoard.h"
#include "GamePad.h"
#include <algorithm>

#include <iostream>

namespace D2D
{
	InputManager::InputManager()
	{
		m_pKeyBoard = std::make_unique<KeyBoard>();
		m_pGamePads.resize(m_MaxIndex + 1);
		std::fill(m_pGamePads.begin(), m_pGamePads.end(), nullptr);
	}

	InputManager::~InputManager()
	{

	}

	bool InputManager::ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
			if (e.type == SDL_KEYDOWN) {

			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {

			}
			ImGui_ImplSDL2_ProcessEvent(&e);
		}

		m_pKeyBoard->Update();

		RemoveDisconnectedControllers();
		for (auto& gamePad : m_pGamePads)
		{
			if (gamePad == nullptr)
				continue;

			 gamePad->Update();
		}

		HandleCommands();

		return true;
	}

	void InputManager::AddKeyboardCommand(SDL_Scancode keyCode, keyState keyState, std::unique_ptr<Command> pCommand)
	{
		m_KeyboardCommands.push_back(std::make_unique<KeyboardCommand>(keyCode, keyState, std::move(pCommand)));
	}

	void InputManager::AddGamepadCommand(int index, GamepadButton button, keyState keyState, std::unique_ptr<Command> pCommand)
	{
		if (CheckIndex(index))
		{
			m_GamepadCommands.push_back(std::make_unique<GamepadCommand>(
				index, button, keyState, std::move(pCommand)));
		}
	}


	void InputManager::RemoveGamepadCommands(int gamePadIdx)
	{
		m_GamepadCommands.erase(std::remove_if(m_GamepadCommands.begin(), m_GamepadCommands.end(),
			[gamePadIdx](const std::unique_ptr<GamepadCommand>& command) {return command->gamepadIndex == gamePadIdx; }), m_GamepadCommands.end());
	}

	void InputManager::HandleCommands()
	{
		for (auto& command : m_KeyboardCommands)
		{
			switch (command->state)
			{
			case keyState::Down:
				if (m_pKeyBoard->IsDown(command->key))
					command->command->Execute();
				break;
			case keyState::Up:
				if (m_pKeyBoard->IsUp(command->key))
					command->command->Execute();
				break;
			case keyState::pressed:
				if (m_pKeyBoard->IsPressed(command->key))
					command->command->Execute();
				break;
			default:
				break;
			}
		}

		for (auto& command : m_GamepadCommands)
		{
			if (m_pGamePads[command->gamepadIndex] == nullptr)
				continue;

			switch (command->state)
			{
			case keyState::Down:
				if (m_pGamePads[command->gamepadIndex]->IsDown(command->button))
					command->command->Execute();
				break;
			case keyState::Up:
				if (m_pGamePads[command->gamepadIndex]->IsUp(command->button))
					command->command->Execute();
				break;
			case keyState::pressed:
				if (m_pGamePads[command->gamepadIndex]->IsPressed(command->button))
					command->command->Execute();
				break;
			default:
				break;
			}
		}
	}

	bool InputManager::CheckIndex(int index)
	{
		if (index > m_MaxIndex || index < 0)
			return false;

		if (m_pGamePads[index] != nullptr)
			return true;

		std::cout << "Created new controller with index " << index << "\n";
		m_pGamePads[index] = std::make_unique<GamePad>(index);
		return true;
	}

	void InputManager::RemoveDisconnectedControllers()
	{
		for(int i{}; i <= m_MaxIndex; i++)
		{
			if (m_pGamePads[i] == nullptr)
				continue;

			if (m_pGamePads[i]->ShouldDelete())
			{
				RemoveGamepadCommands(i);
				m_pGamePads[i] = nullptr;
				std::cout << "Deleted controller with index " << i << "\n";
			}
		}
	}
}
