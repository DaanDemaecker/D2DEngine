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

#include "Command.h"
#include "MoveCommand.h"

namespace D2D
{
	void LoadDemoScene(Scene& scene)
	{

		auto& input = D2D::InputManager::GetInstance();

		const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

		const auto pFont{ pResourceManager.LoadFont("Lingua.otf", 36) };
		const auto pFont2{ pResourceManager.LoadFont("Lingua.otf", 15) };
		const auto pBackgroundTexture{ pResourceManager.LoadTexture("background.tga") };
		const auto pLogoTexture{ pResourceManager.LoadTexture("logo.tga") };

		const auto pBomberManTexture{ pResourceManager.LoadTexture("sprites/Bomberman.png") };
		const auto pEnemyTexture{ pResourceManager.LoadTexture("sprites/Bomb.png") };

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
		auto pBombermanTransform = pBomberMan->GetTransform().get();
		pBombermanTransform->SetLocalPosition(glm::vec2{ 300, 300 });
		pBomberMan->AddComponent<D2D::RenderComponent>()->SetTexture(pBomberManTexture);



		auto pEnemy{ scene.CreateGameObject("Enemy") };
		auto pEnemyTransform = pEnemy->GetTransform().get();
		pEnemyTransform->SetLocalPosition(glm::vec2{ 250, 300 });
		pEnemy->AddComponent<D2D::RenderComponent>()->SetTexture(pEnemyTexture);

		const float playerSpeed{ 50.0f };

		input.AddKeyboardCommand(SDL_SCANCODE_W, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, -1 }, playerSpeed, pBombermanTransform));
		input.AddKeyboardCommand(SDL_SCANCODE_A, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ -1, 0 }, playerSpeed, pBombermanTransform));
		input.AddKeyboardCommand(SDL_SCANCODE_S, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, 1 }, playerSpeed, pBombermanTransform));
		input.AddKeyboardCommand(SDL_SCANCODE_D, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 1, 0 }, playerSpeed, pBombermanTransform));

		input.AddGamepadCommand(0, D2D::GamepadButton::DpadUp, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, -1 }, 2* playerSpeed, pEnemyTransform));
		input.AddGamepadCommand(0, D2D::GamepadButton::DpadLeft, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ -1, 0 }, 2* playerSpeed, pEnemyTransform));
		input.AddGamepadCommand(0, D2D::GamepadButton::DpadDown, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 0, 1 }, 2* playerSpeed, pEnemyTransform));
		input.AddGamepadCommand(0, D2D::GamepadButton::DpadRight, D2D::keyState::pressed, std::make_unique<D2D::MoveCommand>(glm::vec2{ 1, 0 }, 2* playerSpeed, pEnemyTransform));
	}
}
