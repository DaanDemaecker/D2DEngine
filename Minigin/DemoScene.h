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

#include "Command.h"
#include "MoveCommand.h"

namespace dae
{
	void LoadDemoScene(Scene& scene)
	{

		auto& input = dae::InputManager::GetInstance();

		const auto& pResourceManager{ dae::ResourceManager::GetInstance() };

		const auto pFont{ pResourceManager.LoadFont("Lingua.otf", 36) };
		const auto pFont2{ pResourceManager.LoadFont("Lingua.otf", 15) };
		const auto pBackgroundTexture{ pResourceManager.LoadTexture("background.tga") };
		const auto pLogoTexture{ pResourceManager.LoadTexture("logo.tga") };

		const auto pBomberManTexture{ pResourceManager.LoadTexture("sprites/Bomberman.png") };
		const auto pEnemyTexture{ pResourceManager.LoadTexture("sprites/Bomb.png") };

		const auto pBackground{ scene.CreateGameObject("Background") };

		pBackground->AddComponent<dae::RenderComponent>()->SetTexture(pBackgroundTexture);

		const auto pLogo{ scene.CreateGameObject("Logo") };
		pLogo->GetTransform()->SetWorldPosition(216.f, 180.f);
		pLogo->AddComponent<dae::RenderComponent>()->SetTexture(pLogoTexture);

		const auto pHeader{ scene.CreateGameObject("Header") };
		pHeader->GetTransform()->SetWorldPosition(80.f, 20.f);
		pHeader->AddComponent<dae::RenderComponent>();
		const auto pHeaderText{ pHeader->AddComponent<dae::TextComponent>() };
		pHeaderText->SetFont(pFont);
		pHeaderText->SetText("Programming 4 Assignment");

		const auto pFPSCounter{ scene.CreateGameObject("Fps Counter") };
		pFPSCounter->GetTransform()->SetWorldPosition(0.0f, 0.0f);
		pFPSCounter->AddComponent<dae::RenderComponent>();
		pFPSCounter->AddComponent<dae::FPSCounter>();
		const auto pText{ pFPSCounter->AddComponent<dae::TextComponent>() };
		pText->SetFont(pFont2);
		pText->SetColor(255, 255, 0);

		const auto pBomberMan{ scene.CreateGameObject("Bomber Man") };
		pBomberMan->GetTransform()->SetLocalPosition(glm::vec2{ 300, 300 });
		auto pBomberManMoveComponent = pBomberMan->AddComponent<dae::MoveComponent>().get();
		pBomberManMoveComponent->SetMovementSpeed(50);
		pBomberMan->AddComponent<dae::RenderComponent>()->SetTexture(pBomberManTexture);

		auto pEnemy{ scene.CreateGameObject("Enemy") };
		pEnemy->GetTransform()->SetLocalPosition(glm::vec2{ 250, 300 });
		auto pEnemyMovementComponent = pEnemy->AddComponent<dae::MoveComponent>().get();
		pEnemyMovementComponent->SetMovementSpeed(100);
		pEnemy->AddComponent<dae::RenderComponent>()->SetTexture(pEnemyTexture);


		input.AddKeyboardCommand(SDL_SCANCODE_W, dae::keyState::pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 0, -1 }, pBomberManMoveComponent));
		input.AddKeyboardCommand(SDL_SCANCODE_A, dae::keyState::pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ -1, 0 }, pBomberManMoveComponent));
		input.AddKeyboardCommand(SDL_SCANCODE_S, dae::keyState::pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 0, 1 }, pBomberManMoveComponent));
		input.AddKeyboardCommand(SDL_SCANCODE_D, dae::keyState::pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 1, 0 }, pBomberManMoveComponent));

		input.AddGamepadCommand(0, dae::GamepadButton::DpadUp, dae::keyState::pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 0, -1 }, pEnemyMovementComponent));
		input.AddGamepadCommand(0, dae::GamepadButton::DpadLeft, dae::keyState::pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ -1, 0 }, pEnemyMovementComponent));
		input.AddGamepadCommand(0, dae::GamepadButton::DpadDown, dae::keyState::pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 0, 1 }, pEnemyMovementComponent));
		input.AddGamepadCommand(0, dae::GamepadButton::DpadRight, dae::keyState::pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 1, 0 }, pEnemyMovementComponent));
	}
}
