#include "pch.h"

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "DemoScene.h"
#include "BombermanScene.h"


void load()
{
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//dae::LoadDemoScene(scene);

	auto& bombermanScene = dae::SceneManager::GetInstance().CreateScene("Bomberman");
	dae::LoadBombermanScene(bombermanScene);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}