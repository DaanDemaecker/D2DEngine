#include "SceneManager.h"
#include "Scene.h"

#include <iostream>

void D2D::SceneManager::Update()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->Update();
	}

	/*for(auto& scene : m_scenes)
	{
		scene->Update();
	}*/
}

void D2D::SceneManager::FixedUpdate()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->FixedUpdate();
	}

	/*for (const auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}*/
}

void D2D::SceneManager::LateUpdate()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->LateUpdate();
	}

	/*for (const auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}*/
}

void D2D::SceneManager::OnGUI()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->OnGUI();
	}

	/*for (const auto& scene : m_scenes)
	{
		scene->OnGUI();
	}*/
}

void D2D::SceneManager::Render() const
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->Render();
	}

	/*for (const auto& scene : m_scenes)
	{
		scene->Render();
	}*/
}

void D2D::SceneManager::RenderCanvas() const
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->RenderCanvas();
	}

	/*for (const auto& scene : m_scenes)
	{
		scene->RenderCanvas();
	}*/
}

void D2D::SceneManager::PostUpdate()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->PostUpdate();
	}

	/*for (auto& scene : m_scenes)
	{
		scene->PostUpdate();
	}*/
}

D2D::Scene& D2D::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);

	if (m_ActiveScene == nullptr)
	{
		m_ActiveScene = scene;
	}

	return *scene;
}

void D2D::SceneManager::DeleteScene(const std::string& name)
{
	auto scene = GetScene(name);

	if (scene != nullptr)
	{
		m_scenes.erase(std::remove(m_scenes.begin(), m_scenes.end(), scene), m_scenes.end());
	}
}

std::shared_ptr<D2D::Scene> D2D::SceneManager::GetScene(const std::string& name)
{
	for (auto& scene : m_scenes)
	{
		if (scene->GetName() == name)
		{
			return scene;
		}
	}
	return nullptr;
}

void D2D::SceneManager::NextScene()
{
	int currentSceneIndex{ -1 };

	for (int i{}; i < m_scenes.size(); ++i)
	{
		if (m_scenes[i] == m_ActiveScene)
		{
			currentSceneIndex = i;
		}
	}

	if (currentSceneIndex <= 0)
	{
		int nextActiveScene = (currentSceneIndex+1) % m_scenes.size();

		m_ActiveScene = m_scenes[nextActiveScene];
	}
}

void D2D::SceneManager::PreviousScene()
{
	int currentSceneIndex{ -1 };

	for (int i{}; i < m_scenes.size(); ++i)
	{
		if (m_scenes[i] == m_ActiveScene)
		{
			currentSceneIndex = i;
		}
	}

	if (currentSceneIndex <= 0)
	{
		int nextActiveScene = (currentSceneIndex - 1);

		if (nextActiveScene < 0)
			nextActiveScene = static_cast<int>(m_scenes.size() - 1);


		m_ActiveScene = m_scenes[nextActiveScene];
	}
}

void D2D::SceneManager::SetActiveScene(const std::string name)
{
	for (auto& scene : m_scenes)
	{
		if (scene->GetName() == name)
		{
			m_ActiveScene = scene;
			return;
		}
	}
}

void D2D::SceneManager::StartFrame()
{
	for (auto& scene : m_scenes)
	{
		scene->StartFrame();
	}
}
