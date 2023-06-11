#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "InputManager.h"
#include "PointsDisplay.h"
#include "ResourceManager.h"
#include "GridComponent.h"
#include "CameraComponent.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "PlayerAnimator.h"
#include "CapsuleCollider.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "LivesDisplayComponent.h"
#include "PointsDisplay.h"
#include "BombManagerComponent.h"
#include "PlayerMovementCommand.h"
#include "DebugCommand.h"
#include "PlaceBombCommand.h"
#include "RemoteControlCommand.h"
#include "Observer.h"
#include "VersusPlayer.h"
#include "SDL.h"

extern SDL_Window* g_window;

namespace D2D
{
	GameObject* SetupPlayer(GameObject* pWorld, Observer* pMainLevelUIObserver, Observer* pLivesDisplay, Observer* pPointsDisplay,
		const std::string& sceneName, int idx, int controllerIdx, float gridSize,
		std::vector<std::shared_ptr<Texture2D>> playerSprites, std::shared_ptr<Texture2D> bombSprites)
	{
		int windowWidth{}, windowHeight{};
		SDL_GetWindowSize(g_window, &windowWidth, &windowHeight);

		auto& input = InputManager::GetInstance();
		const auto font{ ResourceManager::GetInstance().LoadFont("Fonts/Minecraft.ttf", 15)};


		float playerSpeed{ 4 * gridSize };

		const float playerHeight{ gridSize * .9f };
		const float playerRadius{ gridSize / 2.f * 0.8f };

		const auto pBombManager{ pWorld->CreateNewObject("BombManager")};

		const auto pGridComponent{ pWorld->GetComponent<GridComponent>().get() };

		const auto pPlayer{ pWorld->CreateNewObject("Bomber Man " + std::to_string(idx), "Player") };

		auto pPlayerTransform = pPlayer->GetTransform().get();
		pPlayerTransform->SetWorldPosition(pGridComponent->GetPlayerPosition(idx));

		const auto pPlayerComponent = pPlayer->AddComponent<D2D::PlayerComponent>().get();
		pPlayerComponent->SetSpeed(playerSpeed);
		pPlayerComponent->SetPlayerHalfWidth(playerRadius);
		pPlayerComponent->SetLevelWidth(static_cast<float>(windowWidth));

		auto pPlayerRenderComponent = pPlayer->AddComponent<D2D::RenderComponent>();
		pPlayerRenderComponent->SetOffset(-playerRadius, -playerHeight / 2);
		pPlayerRenderComponent->SetDestRectBounds(2 * playerRadius, playerHeight);

		auto pPlayerAnimator = pPlayer->AddComponent<D2D::PlayerAnimator>();
		pPlayerAnimator->Init(playerSprites, pPlayerRenderComponent.get(), pMainLevelUIObserver);


		auto pPlayerCollider = pPlayer->AddComponent<CapsuleCollider>();
		pPlayerCollider->AddToPhysicsManager(false);
		pPlayerCollider->SetVariables(playerHeight, playerRadius);

		pPlayerComponent->AddObserver(pLivesDisplay);

		pPlayerComponent->AddObserver(pPointsDisplay);


		const auto pBombmanagercomponent = pBombManager->AddComponent<BombManagerComponent>();
		pBombmanagercomponent->SetBombTexture(bombSprites);
		pBombmanagercomponent->SetPlayerIndex(idx);
		pBombmanagercomponent->SetGrid(pGridComponent);
		pBombmanagercomponent->SetBombSize(gridSize);

		pPlayerComponent->AddObserver(pBombmanagercomponent.get());

		if (idx == 0)
		{
			input.AddKeyboardCommand(SDL_SCANCODE_W, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 0, -1 }, pPlayerComponent), sceneName);
			input.AddKeyboardCommand(SDL_SCANCODE_A, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ -1, 0 }, pPlayerComponent), sceneName);
			input.AddKeyboardCommand(SDL_SCANCODE_S, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 0, 1 }, pPlayerComponent), sceneName);
			input.AddKeyboardCommand(SDL_SCANCODE_D, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 1, 0 }, pPlayerComponent), sceneName);

			input.AddKeyboardCommand(SDL_SCANCODE_BACKSPACE, D2D::keyState::Down, std::make_unique<D2D::DebugCommand>(pPlayer), sceneName);
			input.AddKeyboardCommand(SDL_SCANCODE_SPACE, D2D::keyState::Down, std::make_unique<D2D::PlaceBombCommand>(pPlayerComponent), sceneName);
			input.AddKeyboardCommand(SDL_SCANCODE_Q, D2D::keyState::Down, std::make_unique<D2D::RemoteControlCommand>(pBombmanagercomponent.get()), sceneName);

		}
		
		input.AddGamepadCommand(controllerIdx, GamepadButton::DpadUp, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 0, -1 }, pPlayerComponent), sceneName);
		input.AddGamepadCommand(controllerIdx, GamepadButton::DpadLeft, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ -1, 0 }, pPlayerComponent), sceneName);
		input.AddGamepadCommand(controllerIdx, GamepadButton::DpadDown, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 0, 1 }, pPlayerComponent), sceneName);
		input.AddGamepadCommand(controllerIdx, GamepadButton::DpadRight, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 1, 0 }, pPlayerComponent), sceneName);

		input.AddGamepadCommand(controllerIdx, GamepadButton::ButtonSouth, D2D::keyState::Down, std::make_unique<D2D::PlaceBombCommand>(pPlayerComponent), sceneName);
		input.AddGamepadCommand(controllerIdx, GamepadButton::ButtonEast, D2D::keyState::Down, std::make_unique<D2D::RemoteControlCommand>(pBombmanagercomponent.get()), sceneName);

		return pPlayer;
	}

	void SetupVerusPlayer(const std::string& sceneName, GameObject* pParent, std::shared_ptr<Texture2D> pTexture, int controllerIdx, float gridSize)
	{
		constexpr float hudSize{ 50.f };

		float playerSpeed{ 4 * gridSize };

		int windowWidth{}, windowHeight{};
		SDL_GetWindowSize(g_window, &windowWidth, &windowHeight);


		auto pPlayer{ pParent->CreateNewObject("Versus Player") };
		pPlayer->GetTransform()->SetWorldPosition(static_cast<float>(windowWidth) / 2, static_cast<float>(windowHeight) / 2);

		auto playerRender{ pPlayer->AddComponent<RenderComponent>() };
		playerRender->SetOffset(-gridSize / 2, -gridSize / 2);
		playerRender->SetDestRectBounds(gridSize, gridSize);
		playerRender->SetTexture(pTexture);

		auto pPlayerComponent{ pPlayer->AddComponent<VersusPlayer>() };
		pPlayerComponent->Setup(sceneName, playerSpeed, controllerIdx, {0, hudSize}, {windowWidth, windowHeight});

	}
}