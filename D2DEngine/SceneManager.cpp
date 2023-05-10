#include "SceneManager.h"
#include "Scene.h"

#include <iostream>

void D2D::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void D2D::SceneManager::FixedUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}

void D2D::SceneManager::LateUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

void D2D::SceneManager::OnGUI()
{
	for (const auto& scene : m_scenes)
	{
		scene->OnGUI();
	}
}

void D2D::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void D2D::SceneManager::PostUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->PostUpdate();
	}
}

D2D::Scene& D2D::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void D2D::SceneManager::StartFrame()
{
	for (auto& scene : m_scenes)
	{
		scene->StartFrame();
	}
}
