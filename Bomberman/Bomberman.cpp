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
#include <ctime>


void load()
{
	//auto& scene = D2D::SceneManager::GetInstance().CreateScene("Demo");
	//D2D::LoadDemoScene(scene);

	auto& bombermanScene = D2D::SceneManager::GetInstance().CreateScene("Bomberman");
	D2D::LoadBombermanScene(bombermanScene);
}

int main(int, char* [])
{
	srand(time(nullptr));


	D2D::D2DEngine engine("../Data/");
	engine.Run(load);
	return 0;
}