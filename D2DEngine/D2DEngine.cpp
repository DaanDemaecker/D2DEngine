#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "D2DEngine.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include <chrono>

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

D2D::D2DEngine::D2DEngine(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

D2D::D2DEngine::~D2DEngine()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void D2D::D2DEngine::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = TimeManager::GetInstance();

	// todo: this update loop could use some work.
	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	
	float lag = 0.0f;
	constexpr float fixedTimeStep = 0.02f;

	time.SetFixedTime(fixedTimeStep);

	constexpr float desiredFrameRate = 144 ;
	constexpr float desiredFrameDuration = 1000.f / desiredFrameRate;

	while (doContinue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

		time.SetDeltaTime(deltaTime);

		lastTime = currentTime;
		lag += deltaTime;

		doContinue = input.ProcessInput();

		while (lag >= fixedTimeStep)
		{
			
			sceneManager.FixedUpdate();
			lag -= fixedTimeStep;
		}

		sceneManager.Update();

		sceneManager.LateUpdate();

		sceneManager.PostUpdate();

		renderer.Render();

		const auto frameDuration{std::chrono::high_resolution_clock::now() - lastTime};
		const auto sleepTime{std::chrono::milliseconds(static_cast<int>(desiredFrameDuration)) - frameDuration};
		std::this_thread::sleep_for(sleepTime);
	}
}
