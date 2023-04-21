#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "GameObject.h"

namespace D2D
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void FixedUpdate();

		void OnGUI();

		void Render();

		void PostUpdate();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
