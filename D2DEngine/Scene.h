#pragma once
#include "SceneManager.h"

namespace D2D
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		GameObject* CreateGameObject(const std::string& name = "UnNamed");
		GameObject* CreateCanvasObject(const std::string& name = "UnNamed");
		
		void Remove(GameObject* object);
		void RemoveAll();

		void StartFrame();

		void Update();

		void FixedUpdate();

		void LateUpdate();

		void Render() const;

		void OnGUI() const;

		void PostUpdate();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::unique_ptr<GameObject> m_pSceneRoot{};
		std::unique_ptr<GameObject> m_pCanvas{};

		std::string m_name;

		static unsigned int m_idCounter; 
	};

}
