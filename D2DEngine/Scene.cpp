#include "Scene.h"
#include "GameObject.h"
#include "ImGuiInfoComponent.h"
#include "InfoCommand.h"
#include "InputManager.h"

#include <iostream>

using namespace D2D;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name)
{
	m_pSceneRoot = std::make_unique<GameObject>("Scene Root");
	m_pSceneRoot->Init();

	m_pCanvas = std::make_unique<GameObject>("Canvas");
	m_pCanvas->Init();

	auto pInfoComponent = m_pSceneRoot->AddComponent<ImGuiInfoComponent>().get();

	pInfoComponent->SetCanvas(m_pCanvas.get());

	InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_TAB, keyState::Down, std::make_unique<InfoCommand>(pInfoComponent));

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



