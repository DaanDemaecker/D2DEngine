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

#include "ServiceLocator.h"

#include "EnemyManager.h"
#include "TimerComponent.h"

#include <functional>


extern SDL_Window* g_window;

namespace D2D
{
	void LoadStartScreenScene(Scene& scene)
	{
		ServiceLocator::GetSoundSystem().ReadSoundSheet("/TextFiles/SoundEffects.txt");

		//auto& input = D2D::InputManager::GetInstance();

		const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

		const auto pBigFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 36) };
		const auto pSmallFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 15) };
		const auto pBackgroundTexture{ pResourceManager.LoadTexture("sprites/StartScreenBackGround.tga") };

		const auto pBackground{ scene.CreateGameObject("Background") };
		pBackground->AddComponent<D2D::RenderComponent>()->SetTexture(pBackgroundTexture);

		const auto pLogoTexture{ pResourceManager.LoadTexture("sprites/BombermanLogo.png") };


		const auto pFPSCounter{ scene.CreateCanvasObject("Fps Counter") };
		pFPSCounter->GetTransform()->SetWorldPosition(0.0f, 0.0f);
		pFPSCounter->AddComponent<D2D::RenderComponent>();
		pFPSCounter->AddComponent<D2D::FPSCounter>();
		const auto pText{ pFPSCounter->AddComponent<D2D::TextComponent>() };
		pText->SetFont(pSmallFont);
		pText->SetColor(255, 255, 0);



		int windowWidth{}, windowHeight{};
		SDL_GetWindowSize(g_window, &windowWidth, &windowHeight);

		const auto pLogo{ scene.CreateGameObject("Logo") };
		constexpr float margin{ 10.0f };
		const float logoWidth{ windowWidth * 0.6f };
		const float logoHeight{ windowHeight * 0.6f };

		pLogo->GetTransform()->SetWorldPosition(windowWidth / 2.f, margin);
		auto pLogoRenderComponent = pLogo->AddComponent<RenderComponent>();
		pLogoRenderComponent->SetTexture(pLogoTexture);
		pLogoRenderComponent->SetOffset(-logoWidth / 2, 0);
		pLogoRenderComponent->SetDestRectBounds(logoWidth, logoHeight);
	}
}
