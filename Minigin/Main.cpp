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

#include "DemoScene.h"

#include "SDL.h"
#include <iostream>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	dae::LoadDemoScene(scene);
	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
} 