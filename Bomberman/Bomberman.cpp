#include "pch.h"

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "DemoScene.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	dae::LoadDemoScene(scene);

}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}