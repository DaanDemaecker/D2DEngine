#pragma once
#include "Singleton.h"
#include "Command.h"
#include <SDL.h>
#include <memory>
#include <vector>
#include "Enums.h"
#include <string>

namespace D2D
{
	class KeyBoard;
	class GamePad;
	class Command;
	class GameObject;

	struct KeyboardCommand
	{
		KeyboardCommand(SDL_Scancode keyCode, keyState keyState, std::unique_ptr<Command> pCommand, std::string sceneName)
			:key{ keyCode }, state{ keyState }, command{ std::move(pCommand) }, sceneName{sceneName}
		{}
		~KeyboardCommand() {};

		SDL_Scancode key;
		keyState state;

		std::unique_ptr<Command> command;
		std::string sceneName;
	};

	struct GamepadCommand
	{
		GamepadCommand(int index, GamepadButton button, keyState keyState, std::unique_ptr<Command> pCommand, std::string sceneName)
			:gamepadIndex{ index }, button {button}, state{ keyState }, command{ std::move(pCommand) }, sceneName{sceneName}
		{}
		~GamepadCommand() {};

		int gamepadIndex;

		GamepadButton button;
		keyState state;

		std::unique_ptr<Command> command;
		std::string sceneName;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput();

		void AddKeyboardCommand(SDL_Scancode keyCode, keyState keyState, std::unique_ptr<Command> pCommand, const std::string& sceneName);

		void AddGamepadCommand(int index, GamepadButton button, keyState keyState, std::unique_ptr<Command> pCommand, const std::string& sceneName);
		void RemoveGamepadCommands(int gamePadIdx);

		void RemoveCommands(const std::string& sceneName);

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
