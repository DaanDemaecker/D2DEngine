#pragma once
#include "Singleton.h"
#include "Command.h"
#include <SDL.h>
#include <memory>
#include <vector>
#include "Enums.h"

namespace dae
{
	class KeyBoard;
	class GamePad;
	class Command;
	class GameObject;

	struct KeyboardCommand
	{
		KeyboardCommand(SDL_Scancode keyCode, keyState keyState, GameObject* pObject, std::unique_ptr<Command> pCommand)
			:key{ keyCode }, state{ keyState }, pObject{ pObject }, command{ std::move(pCommand) }
		{}
		~KeyboardCommand() {};

		SDL_Scancode key;
		keyState state;

		GameObject* pObject;
		std::unique_ptr<Command> command;
	};

	struct GamepadCommand
	{
		GamepadCommand(int index, GamepadButton button, keyState keyState, GameObject* pObject, std::unique_ptr<Command> pCommand)
			:gamepadIndex{ index }, button {button}, state{ keyState }, pObject{ pObject }, command{ std::move(pCommand) }
		{}
		~GamepadCommand() {};

		int gamepadIndex;

		GamepadButton button;
		keyState state;

		GameObject* pObject;
		std::unique_ptr<Command> command;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput();

		void AddKeyboardCommand(SDL_Scancode keyCode, keyState keyState, GameObject* pObject, std::unique_ptr<Command> pCommand);
		void RemoveKeyboardCommands(GameObject* pObject);

		void AddGamepadCommand(int index, GamepadButton button, keyState keyState, GameObject* pObject, std::unique_ptr<Command> pCommand);
		void RemoveGamepadCommands(GameObject* pObject);
		void RemoveGamepadCommands(int gamePadIdx);

	private:
		std::unique_ptr<KeyBoard> m_pKeyBoard;
		std::vector<std::unique_ptr<GamePad>> m_pGamePads;

		std::vector<std::unique_ptr<KeyboardCommand>> m_KeyboardCommands;
		std::vector<std::unique_ptr<GamepadCommand>> m_GamepadCommands;

		const int m_MaxIndex{ 3 };

		void HandleCommands();
		bool CheckIndex(int index);
		void RemoveDisconnectedControllers();
	};
}
