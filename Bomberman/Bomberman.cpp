#include "pch.h"

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "D2DEngine.h"
#include "SceneManager.h"
#include "DemoScene.h"
#include "BombermanScene.h"
#include "StartScreenScene.h"
#include "HighscoreScene.h"
#include <ctime>

#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "DebugSDLSoundSystem.h"
#include "PhysicsManager.h"


void load()
{
	//auto& scene = D2D::SceneManager::GetInstance().CreateScene("Demo");
	//D2D::LoadDemoScene(scene);
#ifdef NDEBUG
	D2D::ServiceLocator::RegisterSoundSystem(std::make_unique<D2D::SDLSoundSystem>());
#else
	D2D::ServiceLocator::RegisterSoundSystem(std::make_unique<D2D::DebugSDLSoundSystem>());
#endif
	D2D::ServiceLocator::GetSoundSystem().ReadSoundSheet("/TextFiles/SoundEffects.txt");

	auto& physics = D2D::PhysicsManager::GetInstance();
	physics.AddIgnoreLayers("Player", "Enemy");
	physics.AddIgnoreLayers("Player", "Player");
	physics.AddIgnoreLayers("Enemy", "Enemy");
	physics.AddIgnoreLayers("Enemy", "Player");


	auto startScreenScene = D2D::SceneManager::GetInstance().CreateScene("StartScreen");
	D2D::LoadStartScreenScene(*startScreenScene);

	auto bombermanScene = D2D::SceneManager::GetInstance().CreateScene("Bomberman");
	D2D::LoadBombermanScene(*bombermanScene);

	auto highScoreScene = D2D::SceneManager::GetInstance().CreateScene("HighscoreScreen");
	D2D::LoadHighscoreScene(*highScoreScene);

	D2D::SceneManager::GetInstance().SetActiveScene(startScreenScene);

	std::cout << "\n Pres Tab to toggle the info window \n \n";
}

int main(int, char* [])
{
	srand(static_cast<unsigned int>(time(nullptr)));

	D2D::D2DEngine engine("../Data/");
	engine.Run(load);
	return 0;
}