#include <SDL.h>
#include <glm/glm.hpp>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "minigin.h"
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

#include "SDL.h"
#include <iostream>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto& input = dae::InputManager::GetInstance();

	const auto& pResourceManager{dae::ResourceManager::GetInstance()};

	const auto pFont{ pResourceManager.LoadFont("Lingua.otf", 36) };
	const auto pFont2{ pResourceManager.LoadFont("Lingua.otf", 15) };
	const auto pBackgroundTexture{ pResourceManager.LoadTexture("background.tga") };
	const auto pLogoTexture{ pResourceManager.LoadTexture("logo.tga") };

	const auto pBomberManTexture{ pResourceManager.LoadTexture("Bomberman.png")};
	const auto pEnemyTexture{ pResourceManager.LoadTexture("Enemy.png") };

	const auto pBackground{ scene.CreateGameObject("Background")};

	pBackground->AddComponent<dae::RenderComponent>()->SetTexture(pBackgroundTexture);

	const auto pLogo{ scene.CreateGameObject("Logo")};
	pLogo->GetTransform()->SetWorldPosition(216.f, 180.f);
	pLogo->AddComponent<dae::RenderComponent>()->SetTexture(pLogoTexture);

	const auto pHeader{ scene.CreateGameObject("Header")};
	pHeader->GetTransform()->SetWorldPosition(80.f, 20.f);
	pHeader->AddComponent<dae::RenderComponent>();
	const auto pHeaderText{ pHeader->AddComponent<dae::TextComponent>() };
	pHeaderText->SetFont(pFont);
	pHeaderText->SetText("Programming 4 Assignment");

	const auto pFPSCounter{ scene.CreateGameObject("Fps Counter")};
	pFPSCounter->GetTransform()->SetWorldPosition(0.0f, 0.0f);
	pFPSCounter->AddComponent<dae::RenderComponent>();
	pFPSCounter->AddComponent<dae::FPSCounter>();
	const auto pText{ pFPSCounter->AddComponent<dae::TextComponent>() };
	pText->SetFont(pFont2);
	pText->SetColor(255, 255, 0);

	const auto pBomberMan{ scene.CreateGameObject("Bomber Man")};
	pBomberMan->GetTransform()->SetLocalPosition(glm::vec2{ 300, 300 });
	pBomberMan->AddComponent<dae::MoveComponent>()->SetMovementSpeed(50);
	pBomberMan->AddComponent<dae::RenderComponent>()->SetTexture(pBomberManTexture);

	auto pEnemy{ scene.CreateGameObject("Enemy")};
	pEnemy->GetTransform()->SetLocalPosition(glm::vec2{ 250, 300 });
	pEnemy->AddComponent<dae::MoveComponent>()->SetMovementSpeed(100);
	pEnemy->AddComponent<dae::RenderComponent>()->SetTexture(pEnemyTexture);


	input.AddKeyboardCommand(SDL_SCANCODE_W, dae::keyState::pressed, pBomberMan, std::make_unique<dae::MoveCommand>(glm::vec2{0, -1}));
	input.AddKeyboardCommand(SDL_SCANCODE_A, dae::keyState::pressed, pBomberMan, std::make_unique<dae::MoveCommand>(glm::vec2{ -1, 0 }));
	input.AddKeyboardCommand(SDL_SCANCODE_S, dae::keyState::pressed, pBomberMan, std::make_unique<dae::MoveCommand>(glm::vec2{ 0, 1 }));
	input.AddKeyboardCommand(SDL_SCANCODE_D, dae::keyState::pressed, pBomberMan, std::make_unique<dae::MoveCommand>(glm::vec2{ 1, 0 }));

	input.AddGamepadCommand(0, dae::GamepadButton::DPAD_UP, dae::keyState::pressed, pEnemy, std::make_unique<dae::MoveCommand>(glm::vec2{ 0, -1 }));
	input.AddGamepadCommand(0, dae::GamepadButton::DPAD_LEFT, dae::keyState::pressed, pEnemy, std::make_unique<dae::MoveCommand>(glm::vec2{ -1, 0 }));
	input.AddGamepadCommand(0, dae::GamepadButton::DPAD_DOWN, dae::keyState::pressed, pEnemy, std::make_unique<dae::MoveCommand>(glm::vec2{ 0, 1 }));
	input.AddGamepadCommand(0, dae::GamepadButton::DPAD_RIGHT, dae::keyState::pressed, pEnemy, std::make_unique<dae::MoveCommand>(glm::vec2{ 1, 0 }));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
} 