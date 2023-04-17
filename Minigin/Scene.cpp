#include "Scene.h"
#include "GameObject.h"
#include "ImGuiInfoComponent.h"
#include "InfoCommand.h"
#include "InputManager.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name)
{
	m_pSceneRoot = std::make_unique<GameObject>("Scene Root");
	m_pSceneRoot->Init();

	auto pInfoComponent = m_pSceneRoot->AddComponent<ImGuiInfoComponent>().get();

	InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_TAB, keyState::Down, std::make_unique<InfoCommand>(pInfoComponent));
}

Scene::~Scene() = default;

GameObject* dae::Scene::CreateGameObject(const std::string& name)
{
	return m_pSceneRoot->CreateNewObject(name);
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
}

void dae::Scene::FixedUpdate()
{
	m_pSceneRoot->FixedUpdate();
}

void Scene::Render() const
{
	m_pSceneRoot->Render();
}

void dae::Scene::OnGUI() const
{
	m_pSceneRoot->OnGUI();
}

void dae::Scene::PostUpdate()
{
	m_pSceneRoot->PostUpdate();
}



