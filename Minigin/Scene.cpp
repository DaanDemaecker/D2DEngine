#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name)
{
	m_pSceneRoot = std::make_unique<GameObject>();
	m_pSceneRoot->Init();
}

Scene::~Scene() = default;

GameObject* dae::Scene::CreateGameObject()
{
	return m_pSceneRoot->CreateNewObject();
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



