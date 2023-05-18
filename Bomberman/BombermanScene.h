#pragma once

#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "InputManager.h"

#include "GameObject.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "FPSCounter.h"
#include "Rotator.h"
#include "TrashTheCacheComponent.h"
#include "PlayerComponent.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"

#include "LivesDisplayComponent.h"
#include "PointsDisplay.h"
#include "BombManagerComponent.h"
#include "PlayerAnimator.h"

#include "DebugCommand.h"
#include "Command.h"
#include "PlayerMovementCommand.h"
#include "PlaceBombCommand.h"
#include "AnimationClip.h"

#include "GridComponent.h"
#include "CameraComponent.h"

#include "ServiceLocator.h"

#include <functional>

namespace D2D
{
	GameObject* SetupPlayer(GameObject* pWorld, Scene& scene, InputManager& input, std::shared_ptr<Font> font, int idx, float gridSize);

	void LoadBombermanScene(Scene& scene)
	{
		ServiceLocator::GetSoundSystem().ReadSoundSheet("/TextFiles/SoundEffects.txt");

		auto& input = D2D::InputManager::GetInstance();

		const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

		const auto pFont{ pResourceManager.LoadFont("Lingua.otf", 36) };
		const auto pFont2{ pResourceManager.LoadFont("Lingua.otf", 15) };
		const auto pBackgroundTexture{ pResourceManager.LoadTexture("sprites/background.tga") };

		const int gridSize{ 34 };

		const auto pBackground{ scene.CreateGameObject("Background") };

		pBackground->AddComponent<D2D::RenderComponent>()->SetTexture(pBackgroundTexture);

		const auto pFPSCounter{ scene.CreateCanvasObject("Fps Counter") };
		pFPSCounter->GetTransform()->SetWorldPosition(0.0f, 0.0f);
		pFPSCounter->AddComponent<D2D::RenderComponent>();
		pFPSCounter->AddComponent<D2D::FPSCounter>();
		const auto pText{ pFPSCounter->AddComponent<D2D::TextComponent>() };
		pText->SetFont(pFont2);
		pText->SetColor(255, 255, 0);

		const auto pWorld{ scene.CreateGameObject("Playfield") };
		pWorld->GetTransform()->SetWorldPosition(0, 50);
		const auto pGrid = pWorld->AddComponent<GridComponent>();
		pGrid->SetGrid("../Data/TextFiles/Level.txt", gridSize);
		pWorld->AddComponent<CameraComponent>()->SetLevelBounds(0, pGrid->GetLevelWidth());
		

		SetupPlayer(pWorld, scene, input, pFont2, 0, gridSize);
	}

	GameObject* SetupPlayer(GameObject* pWorld, Scene& scene, InputManager& input, std::shared_ptr<Font> font, int idx, float gridSize)
	{
		float playerSpeed{ 4 *  gridSize };

		const float playerHeight{ gridSize * .9f };
		const float playerRadius{ gridSize / 2.f * 0.8f};

		const auto pBombManager{ pWorld->CreateNewObject("BombManager") };

		const auto pGridComponent{ pWorld->GetComponent<GridComponent>().get() };

		const auto pPlayer{ pWorld->CreateNewObject("Bomber Man " + std::to_string(idx)) };

		pWorld->GetComponent<CameraComponent>()->SetPlayer(pPlayer->GetTransform().get());

		auto pPlayerTransform = pPlayer->GetTransform().get();
		pPlayerTransform->SetWorldPosition(pGridComponent->GetPlayerPosition(idx)); 

		const auto pPlayerComponent = pPlayer->AddComponent<D2D::PlayerComponent>().get();
		pPlayerComponent->SetSpeed(playerSpeed);

		auto pPlayerRenderComponent = pPlayer->AddComponent<D2D::RenderComponent>();
		pPlayerRenderComponent->SetOffset(-playerRadius, -playerHeight/2);
		pPlayerRenderComponent->SetDestRectBounds(2 * playerRadius, playerHeight);

		auto pPlayerAnimator = pPlayer->AddComponent<D2D::PlayerAnimator>();
		pPlayerAnimator->Init(pPlayerRenderComponent.get());
	


		auto pPlayerCollider = pPlayer->AddComponent<CapsuleCollider>();
		pPlayerCollider->AddToPhysicsManager(false);
		pPlayerCollider->SetVariables(playerHeight, playerRadius);


		const auto pLivesDisplay{ scene.CreateCanvasObject("Lives Display") };
		pLivesDisplay->GetTransform()->SetWorldPosition(glm::vec2{ 500.f, 0.f });
		pLivesDisplay->AddComponent<D2D::RenderComponent>();

		const auto pLivesText = pLivesDisplay->AddComponent<D2D::TextComponent>();
		pLivesText->SetFont(font);
		pLivesText->SetColor(255, 255, 255);

		const auto pLivesDisplayComponent = pLivesDisplay->AddComponent<LivesDisplayComponent>();

		pPlayerComponent->AddObserver(pLivesDisplayComponent.get());



		const auto pPointsDisplay{ scene.CreateCanvasObject("Points Display") };
		pPointsDisplay->GetTransform()->SetWorldPosition(glm::vec2{ 400.0f, 0.f });
		pPointsDisplay->AddComponent<D2D::RenderComponent>();

		const auto pPointsText = pPointsDisplay->AddComponent<D2D::TextComponent>();
		pPointsText->SetFont(font);
		pPointsText->SetColor(255, 255, 255);

		const auto pPointsDisplayComponent = pPointsDisplay->AddComponent<D2D::PointsDisplay>();

		pPlayerComponent->AddObserver(pPointsDisplayComponent.get());


		const auto pBombmanagercomponent = pBombManager->AddComponent<BombManagerComponent>();
		pBombmanagercomponent->SetGrid(pGridComponent);
		pBombmanagercomponent->SetBombSize(gridSize);

		pPlayerComponent->AddObserver(pBombmanagercomponent.get());

		

		if (idx == 0)
		{
			input.AddKeyboardCommand(SDL_SCANCODE_W, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 0, -1 }, pPlayerComponent));
			input.AddKeyboardCommand(SDL_SCANCODE_A, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ -1, 0 }, pPlayerComponent));
			input.AddKeyboardCommand(SDL_SCANCODE_S, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 0, 1 }, pPlayerComponent));
			input.AddKeyboardCommand(SDL_SCANCODE_D, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 1, 0 }, pPlayerComponent));

			input.AddKeyboardCommand(SDL_SCANCODE_BACKSPACE, D2D::keyState::Down, std::make_unique<D2D::DebugCommand>(std::bind(&PlayerComponent::KillPlayer, pPlayerComponent)));
			input.AddKeyboardCommand(SDL_SCANCODE_SPACE, D2D::keyState::Down, std::make_unique<D2D::PlaceBombCommand>(pPlayerComponent));
		}
		else if (idx == 1)
		{
			input.AddGamepadCommand(0, GamepadButton::DpadUp, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 0, -1 }, pPlayerComponent));
			input.AddGamepadCommand(0, GamepadButton::DpadLeft, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ -1, 0 }, pPlayerComponent));
			input.AddGamepadCommand(0, GamepadButton::DpadDown, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 0, 1 }, pPlayerComponent));
			input.AddGamepadCommand(0, GamepadButton::DpadRight, D2D::keyState::pressed, std::make_unique<D2D::PlayerMovementCommand>(glm::vec2{ 1, 0 }, pPlayerComponent));
		}

		return pPlayer;
	}
}
