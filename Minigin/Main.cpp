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
#include "GameObject.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "FPSCounter.h"
#include "Rotator.h"
#include "TrashTheCacheComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

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

	const auto pSceneCenter{ scene.CreateGameObject("Scene Center")};
	pSceneCenter->GetTransform()->SetWorldPosition(300, 300);

	const auto pBomberMan{ pSceneCenter->CreateNewObject("Bomber Man")};
	pBomberMan->AddComponent<dae::RenderComponent>()->SetTexture(pBomberManTexture);
	pBomberMan->AddComponent<dae::Rotator>();

	const auto pEnemy{ pBomberMan->CreateNewObject("Enemy")};
	pEnemy->AddComponent<dae::RenderComponent>()->SetTexture(pEnemyTexture);
	pEnemy->AddComponent<dae::Rotator>()->SetRotSpeed(glm::radians(-360.f));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
} 