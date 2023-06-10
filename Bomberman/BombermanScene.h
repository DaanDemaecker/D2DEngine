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
#include "RemoteControlCommand.h"

#include "EnemyManager.h"
#include "TimerComponent.h"

#include "GameUI.h"

#include <functional>

extern SDL_Window* g_window;

namespace D2D
{
	void LoadBombermanScene(Scene& scene)
	{
		int windowWidth{}, windowHeight{};
		SDL_GetWindowSize(g_window, &windowWidth, &windowHeight);

		constexpr float hudSize{ 50.f };

		const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

		const auto pBigFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 36) };
		const auto pSmallFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 15) };
		const auto pBackgroundTexture{ pResourceManager.LoadTexture("sprites/background.tga") };
		const auto pIntroScreenBackgroundTexture{ pResourceManager.LoadTexture("sprites/StartScreenBackGround.tga") };

		const auto pBackground{ scene.CreateGameObject("Background") };
		pBackground->GetTransform()->SetWorldPosition(0, hudSize);
		pBackground->AddComponent<D2D::RenderComponent>()->SetTexture(pBackgroundTexture);


		const auto pGameUI{ scene.CreateCanvasObject("UI") };
		const auto pGameUIComponent{ pGameUI->AddComponent<GameUI>()};

		const auto pHud{ pGameUI->CreateNewObject("HUD") };

		const auto pTimer{ pHud->CreateNewObject("Timer") };
		pTimer->GetTransform()->SetWorldPosition(5.f, 5.f);
		pTimer->AddComponent<RenderComponent>();
		auto pTimerText = pTimer->AddComponent<TextComponent>();
		pTimerText->SetFont(pBigFont);
		pTimerText->SetText("TIME   200");
		auto pTimerComponent = pTimer->AddComponent<TimerComponent>();


		const auto pFPSCounter{ scene.CreateCanvasObject("Fps Counter") };
		pFPSCounter->GetTransform()->SetWorldPosition(0.0f, 0.0f);
		pFPSCounter->AddComponent<D2D::RenderComponent>();
		pFPSCounter->AddComponent<D2D::FPSCounter>();
		const auto pText{ pFPSCounter->AddComponent<D2D::TextComponent>() };
		pText->SetFont(pSmallFont);
		pText->SetColor(255, 255, 0);

		const auto pPointsDisplay{ pHud->CreateNewObject("Points Display") };
		pPointsDisplay->GetTransform()->SetWorldPosition(glm::vec2{ 400.0f, 0.f });
		pPointsDisplay->AddComponent<D2D::RenderComponent>();

		const auto pPointsText = pPointsDisplay->AddComponent<D2D::TextComponent>();
		pPointsText->SetFont(pSmallFont);
		pPointsText->SetColor(255, 255, 255);

		const auto pPointsDisplayComponent = pPointsDisplay->AddComponent<D2D::PointsDisplay>();

		const auto pLivesDisplay{ pHud->CreateNewObject("Lives Display") };
		pLivesDisplay->GetTransform()->SetWorldPosition(glm::vec2{ 500.f, 0.f });
		pLivesDisplay->AddComponent<D2D::RenderComponent>();

		const auto pLivesText = pLivesDisplay->AddComponent<D2D::TextComponent>();
		pLivesText->SetFont(pSmallFont);
		pLivesText->SetColor(255, 255, 255);

		const auto pLivesDisplayComponent = pLivesDisplay->AddComponent<LivesDisplayComponent>();


		const auto pWorld{ scene.CreateGameObject("Playfield") };
		pWorld->GetTransform()->SetWorldPosition(0, hudSize);
		const auto pGrid = pWorld->AddComponent<GridComponent>();
		pWorld->AddComponent<CameraComponent>();

		const auto pIntroScreen{ pGameUI->CreateNewObject("IntroScreen") };
		const auto pIntroScreenRenderComponent{ pIntroScreen->AddComponent<RenderComponent>() };
		pIntroScreenRenderComponent->SetTexture(pIntroScreenBackgroundTexture);
		pIntroScreenRenderComponent->SetDestRectBounds(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

		
		const auto pIntroScreenTextObject{ pIntroScreen->CreateNewObject("IntroScreenText") };
		const auto pIntroScreenTextRenderComponent{ pIntroScreenTextObject->AddComponent<RenderComponent>() };
		const auto pIntroScreenText{ pIntroScreenTextObject->AddComponent<TextComponent>() };
		pIntroScreenTextObject->GetTransform()->SetWorldPosition(static_cast<float>(windowWidth) / 2.f - 50, static_cast<float>(windowHeight) / 2.f);
		pIntroScreenText->SetFont(pBigFont);
		pIntroScreenText->SetColor(255.f, 255.f, 255.f, 255.f);
		pIntroScreenText->SetText("STAGE   1");



		const auto pGameOverScreen{ pGameUI->CreateNewObject("GameOverScreen") };
		pGameOverScreen->SetActive(false);
		const auto pGameOverScreenRenderComponent{ pGameOverScreen->AddComponent<RenderComponent>() };
		pGameOverScreenRenderComponent->SetTexture(pIntroScreenBackgroundTexture);
		pGameOverScreenRenderComponent->SetDestRectBounds(static_cast<float>(windowWidth), static_cast<float>(windowHeight));


		const auto pGameOverScreenTextObject{ pGameOverScreen->CreateNewObject("GameOverScreenText") };
		const auto pGameOverScreenTextRenderComponent{ pGameOverScreenTextObject->AddComponent<RenderComponent>() };
		const auto pGameOverScreenText{ pGameOverScreenTextObject->AddComponent<TextComponent>() };
		pGameOverScreenTextObject->GetTransform()->SetWorldPosition(static_cast<float>(windowWidth) / 2.f - 150, static_cast<float>(windowHeight) / 2.f);
		pGameOverScreenText->SetFont(pBigFont);
		pGameOverScreenText->SetColor(255.f, 255.f, 255.f, 255.f);
		pGameOverScreenText->SetText("GAME OVER");


		const auto pLevelEndScreen{ pGameUI->CreateNewObject("Level end screen") };
		pLevelEndScreen->SetActive(false);
		const auto pLevelEndRenderer{ pLevelEndScreen->AddComponent<RenderComponent>() };
		pLevelEndRenderer->SetTexture(pIntroScreenBackgroundTexture);
		pLevelEndRenderer->SetDestRectBounds(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

		const auto pLevelEndScreenTextObject{ pLevelEndScreen->CreateNewObject("Level end text") };
		const auto pLevelEndRender{ pLevelEndScreenTextObject->AddComponent<RenderComponent>() };
		const auto pLevelEndText{ pLevelEndScreenTextObject->AddComponent<TextComponent>() };
		pLevelEndScreenTextObject->GetTransform()->SetWorldPosition(static_cast<float>(windowWidth) / 2.f - 150, static_cast<float>(windowHeight) / 2.f);
		pLevelEndText->SetFont(pBigFont);
		pLevelEndText->SetColor(255.f, 255.f, 255.f, 255.f);
		pLevelEndText->SetText("YOU WIN");


		pGameUIComponent->Initialize(pIntroScreen, pHud, pWorld, pTimerComponent.get(), pPointsDisplayComponent.get(), pLivesDisplayComponent.get(), pGameOverScreen, pLevelEndScreen, pIntroScreenText.get());
		
		
		scene.StartFrame();
	}
}
