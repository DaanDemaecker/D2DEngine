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
		void DeleteScene(const std::string& name);
		std::shared_ptr<Scene> GetScene(const std::string& name);

		void NextScene();
		void PreviousScene();
		void SetActiveScene(const std::string name);

		Scene& GetActiveScene() { return *m_ActiveScene; }

		void StartFrame();

		void Update();
		void FixedUpdate();

		void LateUpdate();

		void OnGUI();

		void Render() const;
		void RenderCanvas() const;

		void PostUpdate();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		std::shared_ptr<Scene> m_ActiveScene{};
		
	};
}
