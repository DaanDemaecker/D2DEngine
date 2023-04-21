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
#include "MoveComponent.h"
#include "PlayerComponent.h"

#include "LivesDisplayComponent.h"
#include "PointsDisplay.h"
#include "DebugCommand.h"

#include "Command.h"
#include "MoveCommand.h"

#include <functional>

namespace D2D
{
	void LoadBombermanScene(Scene& scene)
	{

		auto& input = D2D::InputManager::GetInstance();

		const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

		const auto pFont{ pResourceManager.LoadFont("Lingua.otf", 36) };
		const auto pFont2{ pResourceManager.LoadFont("Lingua.otf", 15) };
		const auto pBackgroundTexture{ pResourceManager.LoadTexture("background.tga") };
		const auto pLogoTexture{ pResourceManager.LoadTexture("logo.tga") };

		const auto pBomberManTexture{ pResourceManager.LoadTexture("sprites/Bomberman.png") };
		const auto pBombTexture{ pResourceManager.LoadTexture("sprites/Bomb.png") };
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

		const auto pBomberMan{ scene.CreateGameObject("Bomber Man") };
		pBomberMan->GetTransform()->SetLocalPosition(glm::vec2{ 300, 300 });
		const auto pPlayerComponent = pBomberMan->AddComponent<D2D::PlayerComponent>();
		auto pBomberManMoveComponent = pBomberMan->AddComponent<D2D::MoveComponent>().get();
		pBomberManMoveComponent->SetMovementSpeed(50);
		pBomberMan->AddComponent<D2D::RenderComponent>()->SetTexture(pBomberManTexture);

		const auto pLivesDisplay{ scene.CreateGameObject("Lives Display") };
		pLivesDisplay->GetTransform()->SetWorldPosition(glm::vec2{ 500.f, 0.f });
		pLivesDisplay->AddComponent<D2D::RenderComponent>();
		const auto pLivesText = pLivesDisplay->AddComponent<D2D::TextComponent>();
		pLivesText->SetFont(pFont2);
		pLivesText->SetColor(255, 255, 255);
		const auto pLivesDisplayComponent = pLivesDisplay->AddComponent<LivesDisplayComponent>();

		pPlayerComponent->AddObserver(pLivesDisplayComponent.get());

		const auto pPointsDisplay{ scene.CreateGameObject("Points Display") };
		pPointsDisplay->GetTransform()->SetWorldPosition(glm::vec2{ 400.0f, 0.f });
		pPointsDisplay->AddComponent<D2D::RenderComponent>();
		const auto pPointsText = pPointsDisplay->AddComponent<D2D::TextComponent>();
		pPointsText->SetFont(pFont2);
		pPointsText->SetColor(255, 255, 255);
		const auto pPointsDisplayComponent = pPointsDisplay->AddComponent<D2D::PointsDisplay>();

		pPlayerComponent->AddObserver(pPointsDisplayComponent.get());


		input.AddKeyboardCommand(SDL_SCANCODE_W, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, -1 }, pBomberManMoveComponent));
		input.AddKeyboardCommand(SDL_SCANCODE_A, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ -1, 0 }, pBomberManMoveComponent));
		input.AddKeyboardCommand(SDL_SCANCODE_S, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, 1 }, pBomberManMoveComponent));
		input.AddKeyboardCommand(SDL_SCANCODE_D, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 1, 0 }, pBomberManMoveComponent));

		input.AddKeyboardCommand(SDL_SCANCODE_BACKSPACE, D2D::keyState::Down, std::make_unique<D2D::DebugCommand>(std::bind(&PlayerComponent::KillPlayer, pPlayerComponent)));
		input.AddKeyboardCommand(SDL_SCANCODE_SPACE, D2D::keyState::Down, std::make_unique<D2D::DebugCommand>(std::bind(&PlayerComponent::PickupItem, pPlayerComponent)));

	
	}
}
