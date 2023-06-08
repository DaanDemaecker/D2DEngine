#include "Scene.h"
#include "GameObject.h"
#include "ImGuiInfoComponent.h"
#include "InfoCommand.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include <iostream>
#include <SDL.h>

extern SDL_Window* g_window;

using namespace D2D;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name)
{
	m_pSceneRoot = std::make_unique<GameObject>("Scene Root");
	m_pSceneRoot->Init();

	int windowWidth{};
	int windowHeight{};
	SDL_GetWindowSize(g_window, &windowWidth, &windowHeight);

	const auto pBackgroundTexture{ ResourceManager::GetInstance().LoadTexture("sprites/UIBackGround.tga")};
	auto sceneRootRenderComponent = m_pSceneRoot->AddComponent<RenderComponent>();
	sceneRootRenderComponent->SetTexture(pBackgroundTexture);
	sceneRootRenderComponent->SetDestRectBounds(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

	m_pCanvas = std::make_unique<GameObject>("Canvas");
	m_pCanvas->Init();

	auto pInfoComponent = m_pSceneRoot->AddComponent<ImGuiInfoComponent>().get();

	pInfoComponent->SetCanvas(m_pCanvas.get());

	InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_TAB, keyState::Down, std::make_unique<InfoCommand>(pInfoComponent), m_name);

	std::cout << "\n Pres Tab to toggle the info window \n \n";
}

Scene::~Scene() = default;

GameObject* D2D::Scene::CreateGameObject(const std::string& name)
{
	return m_pSceneRoot->CreateNewObject(name);
}

GameObject* D2D::Scene::CreateCanvasObject(const std::string& name)
{
	return m_pCanvas->CreateNewObject(name);
}

void Scene::Remove(GameObject* pObject)
{
	m_pSceneRoot->RemoveChild(pObject);
}

void Scene::RemoveAll()
{
	
}

void D2D::Scene::OnSceneLoad()
{
	m_pSceneRoot->OnSceneLoad();
	m_pCanvas->OnSceneLoad();
}

void D2D::Scene::StartFrame()
{
	m_pSceneRoot->StartFrame();
	m_pCanvas->StartFrame();
}

void Scene::Update()
{
	m_pSceneRoot->Update();
	m_pCanvas->Update();
}

void D2D::Scene::FixedUpdate()
{
	m_pSceneRoot->FixedUpdate();
	m_pCanvas->FixedUpdate();
}

void D2D::Scene::LateUpdate()
{
	m_pSceneRoot->LateUpdate();
	m_pCanvas->LateUpdate();
}

void Scene::Render() const
{
	m_pSceneRoot->Render();
}

void D2D::Scene::RenderCanvas() const
{
	m_pCanvas->Render();
}

void D2D::Scene::OnGUI() const
{
	m_pSceneRoot->OnGUI();
	m_pCanvas->OnGUI();
}

void D2D::Scene::PostUpdate()
{
	m_pSceneRoot->PostUpdate();
	m_pCanvas->PostUpdate();
}



