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

#include "ServiceLocator.h"

#include "ButtonComponent.h"
#include "MenuScrollCommand.h"
#include "ButtonActivateCommand.h"
#include "MainMenuComponent.h"

extern SDL_Window* g_window;

namespace D2D
{
	void LoadStartScreenScene(Scene& scene)
	{
		ServiceLocator::GetSoundSystem().ReadSoundSheet("/TextFiles/SoundEffects.txt");

		//auto& input = D2D::InputManager::GetInstance();

		const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

		const auto pFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 25) };
		const auto pSmallFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 10) };
		const auto pBackgroundTexture{ pResourceManager.LoadTexture("sprites/StartScreenBackGround.tga") };

		const auto pBackground{ scene.CreateGameObject("Background") };
		pBackground->AddComponent<D2D::RenderComponent>()->SetTexture(pBackgroundTexture);

		const auto pLogoTexture{ pResourceManager.LoadTexture("sprites/BombermanLogo.png") };
		const auto pSelecterTexture{ pResourceManager.LoadTexture("sprites/UISelector.png")};


		const auto pFPSCounter{ scene.CreateCanvasObject("Fps Counter") };
		pFPSCounter->GetTransform()->SetWorldPosition(0.0f, 0.0f);
		pFPSCounter->AddComponent<D2D::RenderComponent>();
		pFPSCounter->AddComponent<D2D::FPSCounter>();
		const auto pText{ pFPSCounter->AddComponent<D2D::TextComponent>() };
		pText->SetFont(pSmallFont);
		pText->SetColor(255, 255, 0);



		int windowWidth{}, windowHeight{};
		SDL_GetWindowSize(g_window, &windowWidth, &windowHeight);

		const auto pLogo{ scene.CreateCanvasObject("Logo") };
		constexpr float margin{ 15.0f };
		const float logoWidth{ windowWidth * 0.6f };
		const float logoHeight{ windowHeight * 0.6f };
		auto pMainMenuComponent{ pLogo->AddComponent<MainMenuComponent>() };

		pLogo->GetTransform()->SetWorldPosition(windowWidth / 2.f, margin);
		auto pLogoRenderComponent = pLogo->AddComponent<RenderComponent>();
		pLogoRenderComponent->SetTexture(pLogoTexture);
		pLogoRenderComponent->SetOffset(-logoWidth / 2, 0);
		pLogoRenderComponent->SetDestRectBounds(logoWidth, logoHeight);


		const float textOffset{ windowWidth / 10.f };

		const auto pSinglePlayerButton{ scene.CreateCanvasObject("SinglePlayerButton") };
		pSinglePlayerButton->AddComponent<RenderComponent>();
		auto pSinglePlayerText = pSinglePlayerButton->AddComponent<TextComponent>();
		pSinglePlayerText->SetFont(pFont);
		pSinglePlayerText->SetColor(255, 255, 255);
		pSinglePlayerText->SetText("SINGLEPLAYER");
		pSinglePlayerButton->GetTransform()->SetWorldPosition(windowWidth/2.f - textOffset, windowHeight - 10 * margin);
		auto pSinglePlayerButtonComponent = pSinglePlayerButton->AddComponent<ButtonComponent>();
		pSinglePlayerButtonComponent->SetSelected(true);
		pSinglePlayerButtonComponent->SetFunction(std::bind(&MainMenuComponent::SinglePlayerButton, pMainMenuComponent.get()));

		const auto pCoopButton{ scene.CreateCanvasObject("CoopButton") };
		pCoopButton->AddComponent<RenderComponent>();
		auto pCoopText = pCoopButton->AddComponent<TextComponent>();
		pCoopText->SetFont(pFont);
		pCoopText->SetColor(255, 255, 255);
		pCoopText->SetText("CO-OP");
		pCoopButton->GetTransform()->SetWorldPosition(windowWidth / 2.f - textOffset, windowHeight - 8 * margin);
		pCoopButton->AddComponent<ButtonComponent>();
		auto pCoopButtonComponent = pCoopButton->AddComponent<ButtonComponent>();
		pCoopButtonComponent->SetFunction(std::bind(&MainMenuComponent::CoopButton, pMainMenuComponent.get()));

		const auto pVersusButton{ scene.CreateCanvasObject("VersusButton") };
		pVersusButton->AddComponent<RenderComponent>();
		auto pVersusText = pVersusButton->AddComponent<TextComponent>();
		pVersusText->SetFont(pFont);
		pVersusText->SetColor(255, 255, 255);
		pVersusText->SetText("VERSUS");
		pVersusButton->GetTransform()->SetWorldPosition(windowWidth / 2.f - textOffset, windowHeight - 6 * margin);
		auto pVersusButtonComponent = pVersusButton->AddComponent<ButtonComponent>();
		pVersusButtonComponent->SetFunction(std::bind(&MainMenuComponent::VersusButton, pMainMenuComponent.get()));

		const auto pSelector{ pSinglePlayerButton->CreateNewObject("Selector") };
		auto pSelectorRenderComponent = pSelector->AddComponent<RenderComponent>();
		pSelectorRenderComponent->SetTexture(pSelecterTexture);
		pSelector->GetTransform()->SetLocalPosition(-30, -5);

		std::vector<ButtonComponent*> pButtons{pSinglePlayerButtonComponent.get(), pCoopButtonComponent.get(), pVersusButtonComponent.get()};

		auto& input = D2D::InputManager::GetInstance();

		input.AddKeyboardCommand(SDL_SCANCODE_UP, D2D::keyState::Down, std::make_unique<D2D::MenuScrollCommand>(-1, pButtons, pSelector));
		input.AddKeyboardCommand(SDL_SCANCODE_DOWN, D2D::keyState::Down, std::make_unique<D2D::MenuScrollCommand>(1, pButtons, pSelector));

		input.AddKeyboardCommand(SDL_SCANCODE_SPACE, D2D::keyState::Down, std::make_unique<D2D::ButtonActivateCommand>(pButtons));
	}
}
