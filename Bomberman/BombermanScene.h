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

#include "LivesDisplayComponent.h"
#include "PointsDisplay.h"
#include "BombManagerComponent.h"

#include "DebugCommand.h"
#include "Command.h"
#include "MoveCommand.h"
#include "PlaceBombCommand.h"


#include <functional>

namespace D2D
{
	GameObject* SetupPlayer(Scene& scene, InputManager& input, std::shared_ptr<Texture2D> pTexture, std::shared_ptr<Font> font, int idx);

	void LoadBombermanScene(Scene& scene)
	{
		auto& input = D2D::InputManager::GetInstance();

		const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

		const auto pFont{ pResourceManager.LoadFont("Lingua.otf", 36) };
		const auto pFont2{ pResourceManager.LoadFont("Lingua.otf", 15) };
		const auto pBackgroundTexture{ pResourceManager.LoadTexture("background.tga") };
		const auto pLogoTexture{ pResourceManager.LoadTexture("logo.tga") };

		const auto pBomberManTexture{ pResourceManager.LoadTexture("sprites/Bomberman.png") };
		const auto pEnemyTexture{ pResourceManager.LoadTexture("sprites/Enemy.png") };

		const auto pBackground{ scene.CreateGameObject("Background") };

		pBackground->AddComponent<D2D::RenderComponent>()->SetTexture(pBackgroundTexture);

		const auto pLogo{ scene.CreateGameObject("Logo") };
		pLogo->GetTransform()->SetWorldPosition(216.f, 180.f);
		pLogo->AddComponent<D2D::RenderComponent>()->SetTexture(pLogoTexture);

		const auto pHeader{ scene.CreateGameObject("Header") };
		pHeader->GetTransform()->SetWorldPosition(80.f, 20.f);
		pHeader->AddComponent<D2D::RenderComponent>();
		const auto pHeaderText{ pHeader->AddComponent<D2D::TextComponent>() };
		pHeaderText->SetFont(pFont);
		pHeaderText->SetText("Programming 4 Assignment");

		const auto pFPSCounter{ scene.CreateGameObject("Fps Counter") };
		pFPSCounter->GetTransform()->SetWorldPosition(0.0f, 0.0f);
		pFPSCounter->AddComponent<D2D::RenderComponent>();
		pFPSCounter->AddComponent<D2D::FPSCounter>();
		const auto pText{ pFPSCounter->AddComponent<D2D::TextComponent>() };
		pText->SetFont(pFont2);
		pText->SetColor(255, 255, 0);

		auto pPlayer1 = SetupPlayer(scene, input, pBomberManTexture, pFont2, 0);

//
//#pragma region player1
//		const auto pEnemy{ scene.CreateGameObject("Enemy") };
//		pEnemy->GetTransform()->SetLocalPosition(glm::vec2{ 300, 300 });
//		const auto pPlayerComponent2 = pEnemy->AddComponent<D2D::PlayerComponent>();
//		auto pEnemyMoveComponent = pEnemy->AddComponent<D2D::RigidBodyComponent>().get();
//		pEnemyMoveComponent->SetMovementSpeed(50);
//		pEnemy->AddComponent<D2D::RenderComponent>()->SetTexture(pEnemyTexture);
//
//		const auto pLivesDisplay{ scene.CreateGameObject("Lives Display") };
//		pLivesDisplay->GetTransform()->SetWorldPosition(glm::vec2{ 300.f, 0.f });
//		pLivesDisplay->AddComponent<D2D::RenderComponent>();
//		const auto pLivesText = pLivesDisplay->AddComponent<D2D::TextComponent>();
//		pLivesText->SetFont(pFont2);
//		pLivesText->SetColor(255, 255, 255);
//		const auto pLivesDisplayComponent2 = pLivesDisplay->AddComponent<LivesDisplayComponent>();
//
//		pPlayerComponent2->AddObserver(pLivesDisplayComponent2
//			.get());
//
//		const auto pPointsDisplay2{ scene.CreateGameObject("Points Display") };
//		pPointsDisplay2->GetTransform()->SetWorldPosition(glm::vec2{ 200.0f, 0.f });
//		pPointsDisplay2->AddComponent<D2D::RenderComponent>();
//		const auto pPointsText2 = pPointsDisplay2->AddComponent<D2D::TextComponent>();
//		pPointsText2->SetFont(pFont2);
//		pPointsText2->SetColor(255, 255, 255);
//		const auto pPointsDisplayComponent2 = pPointsDisplay2->AddComponent<D2D::PointsDisplay>();
//
//		pPlayerComponent2->AddObserver(pPointsDisplayComponent2.get());
//
//
//		input.AddGamepadCommand(0, D2D::GamepadButton::DpadUp, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, -1 }, pEnemyMoveComponent));
//		input.AddGamepadCommand(0, D2D::GamepadButton::DpadLeft, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ -1, 0 }, pEnemyMoveComponent));
//		input.AddGamepadCommand(0, D2D::GamepadButton::DpadDown, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, 1 }, pEnemyMoveComponent));
//		input.AddGamepadCommand(0, D2D::GamepadButton::DpadRight, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 1, 0 }, pEnemyMoveComponent));
//
//		input.AddKeyboardCommand(SDL_SCANCODE_O, D2D::keyState::Down, std::make_unique<D2D::DebugCommand>(std::bind(&PlayerComponent::KillPlayer, pPlayerComponent2)));
//		input.AddKeyboardCommand(SDL_SCANCODE_P, D2D::keyState::Down, std::make_unique<D2D::DebugCommand>(std::bind(&PlayerComponent::PickupItem, pPlayerComponent2)));
//#pragma endregion Player1
//	
	}

	GameObject* SetupPlayer(Scene& scene, InputManager& input, std::shared_ptr<Texture2D> pTexture, std::shared_ptr<Font> font, int idx)
	{
		const auto pBombManager{ scene.CreateGameObject("BombManager") };

		const auto pPlayer{ scene.CreateGameObject("Bomber Man" + std::to_string(idx)) };

		auto pPlayerTransform = pPlayer->GetTransform().get();
		pPlayerTransform->SetLocalPosition(glm::vec2{ 300, 300 }); 

		const auto pPlayerComponent = pPlayer->AddComponent<D2D::PlayerComponent>();
		auto pPlayerRenderComponent = pPlayer->AddComponent<D2D::RenderComponent>();
		pPlayerRenderComponent->SetTexture(pTexture);
		pPlayerRenderComponent->SetOffset(-14.f, -18.f);

		auto pPlayerCollider = pPlayer->AddComponent<BoxCollider>();
		pPlayerCollider->SetVariables(30, 40, -14.f, -18.f);


		const auto pLivesDisplay{ scene.CreateGameObject("Lives Display") };
		pLivesDisplay->GetTransform()->SetWorldPosition(glm::vec2{ 500.f, 0.f });
		pLivesDisplay->AddComponent<D2D::RenderComponent>();

		const auto pLivesText = pLivesDisplay->AddComponent<D2D::TextComponent>();
		pLivesText->SetFont(font);
		pLivesText->SetColor(255, 255, 255);

		const auto pLivesDisplayComponent = pLivesDisplay->AddComponent<LivesDisplayComponent>();

		pPlayerComponent->AddObserver(pLivesDisplayComponent.get());



		const auto pPointsDisplay{ scene.CreateGameObject("Points Display") };
		pPointsDisplay->GetTransform()->SetWorldPosition(glm::vec2{ 400.0f, 0.f });
		pPointsDisplay->AddComponent<D2D::RenderComponent>();

		const auto pPointsText = pPointsDisplay->AddComponent<D2D::TextComponent>();
		pPointsText->SetFont(font);
		pPointsText->SetColor(255, 255, 255);

		const auto pPointsDisplayComponent = pPointsDisplay->AddComponent<D2D::PointsDisplay>();

		pPlayerComponent->AddObserver(pPointsDisplayComponent.get());


		const auto pBombmanagercomponent = pBombManager->AddComponent<BombManagerComponent>();

		pPlayerComponent->AddObserver(pBombmanagercomponent.get());

		const float playerSpeed{ 50.0f };

		if (idx == 0)
		{
			input.AddKeyboardCommand(SDL_SCANCODE_W, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, -1 }, playerSpeed, pPlayerTransform));
			input.AddKeyboardCommand(SDL_SCANCODE_A, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ -1, 0 }, playerSpeed, pPlayerTransform));
			input.AddKeyboardCommand(SDL_SCANCODE_S, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, 1 }, playerSpeed, pPlayerTransform));
			input.AddKeyboardCommand(SDL_SCANCODE_D, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 1, 0 }, playerSpeed, pPlayerTransform));

			input.AddKeyboardCommand(SDL_SCANCODE_BACKSPACE, D2D::keyState::Down, std::make_unique<D2D::DebugCommand>(std::bind(&PlayerComponent::KillPlayer, pPlayerComponent)));
			input.AddKeyboardCommand(SDL_SCANCODE_SPACE, D2D::keyState::Down, std::make_unique<D2D::PlaceBombCommand>(pPlayerComponent.get()));
		}

		return pPlayer;
	}
}
