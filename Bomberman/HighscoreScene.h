#pragma once
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "RenderComponent.h"
#include "HighScoreScreenComponent.h"
#include "Transform.h"

extern SDL_Window* g_window;

namespace D2D
{
	void LoadHighscoreScene(Scene& scene)
	{
		int windowWidth{}, windowHeight{};
		SDL_GetWindowSize(g_window, &windowWidth, &windowHeight);
		constexpr float margin{ 15.0f };
		const float logoWidth{ windowWidth * 0.4f };
		const float logoHeight{ windowHeight * 0.4f };



		const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

		const auto pBackgroundTexture{ pResourceManager.LoadTexture("sprites/StartScreenBackGround.tga") };
		const auto pLogoTexture{ pResourceManager.LoadTexture("sprites/BombermanLogo.png") };

		const auto pBackground{ scene.CreateGameObject("Background") };
		auto pBackgroundRenderComponent = pBackground->AddComponent<D2D::RenderComponent>();
		pBackgroundRenderComponent->SetTexture(pBackgroundTexture);
		pBackgroundRenderComponent->SetDestRectBounds(static_cast<float>(windowWidth), static_cast<float>(windowHeight));


		const auto pHighScoreUI{ scene.CreateCanvasObject("Higscore UI") };
		auto pHighScoreComponent = pHighScoreUI->AddComponent<HighScoreScreenComponent>();


		const auto pInputScreenObject = pHighScoreUI->CreateNewObject("Input screen");
		const auto pLogo{ pInputScreenObject->CreateNewObject("Logo") };

		pLogo->GetTransform()->SetWorldPosition(windowWidth / 2.f, margin);
		auto pLogoRenderComponent = pLogo->AddComponent<RenderComponent>();
		pLogoRenderComponent->SetTexture(pLogoTexture);
		pLogoRenderComponent->SetOffset(-logoWidth / 2, 0);
		pLogoRenderComponent->SetDestRectBounds(logoWidth, logoHeight);



		const auto pHighscoreScreenObject = pHighScoreUI->CreateNewObject("Highscore Window");

		pHighscoreScreenObject->SetActive(false);


		pHighScoreComponent->Initialize(pInputScreenObject, pHighscoreScreenObject);

		
		scene.StartFrame();
	}
}