#pragma once
#include <vector>
#include <memory>
#include <string>

namespace D2D
{
	class Component;
	class RenderComponent;
	class Transform;

	class GameObject final
	{
	public:
		GameObject() : GameObject("UnNamed"){}
		GameObject(const std::string& name) : m_Name{name}{}
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Init();

		void Update();

		void FixedUpdate();

		void LateUpdate();

		void Render() const;

		void OnGUI();

		void PostUpdate();

		void Destroy() { m_ShouldDestroy = true; }
		bool ShouldDestroy() const { return m_ShouldDestroy; }

		GameObject* CreateNewObject(const std::string& name = "UnNamed");

		template <class T>
		std::shared_ptr<T> GetComponent() const;
		template <class T>
		std::shared_ptr<T> AddComponent();
		template <class T>
		bool RemoveComponent();
		template <class T>
		bool HasComponent() const;

		void SetParent(GameObject* pParent, bool worldPositionStays);
		GameObject* GetParent() const { return m_pParent; }
		void RemoveChild(GameObject* pChild);
		const std::vector<std::unique_ptr<GameObject>>& GetChildren() const { return m_pChildren; }
		bool ContainsChild(GameObject* pChild) const;

		std::shared_ptr<Transform> GetTransform() { return m_pTransform; }

		const std::string& GetName() const { return m_Name; }

	private:
		const std::string m_Name;

		GameObject* m_pParent{};
		std::vector<std::unique_ptr<GameObject>> m_pChildren{};

		std::shared_ptr<Transform> m_pTransform;

		std::vector<std::shared_ptr<Component>> m_pComponents{};

		bool m_ShouldDestroy{ false };

		void DestroyComponent(std::shared_ptr<Component> pComponent);
	};

	template<class T>
	inline std::shared_ptr<T> GameObject::GetComponent() const
	{
		if (!std::is_base_of<Component, T>())
		{
			return nullptr;
		}

		for (const auto& pComponent : m_pComponents)
		{
			auto pCastedComponent = std::dynamic_pointer_cast<T>(pComponent);

			if (pCastedComponent)
			{
				return pCastedComponent;
			}
		}

		return nullptr;
	}

	template<class T>
	inline std::shared_ptr<T> GameObject::AddComponent()
	{
		if (!std::is_base_of<Component, T>())
			return nullptr;

		if (HasComponent<T>())
		{
			return GetComponent<T>();
		}

		auto pComponent = std::make_shared<T>();

		pComponent->SetOwner(this);

		m_pComponents.push_back(pComponent);


		return pComponent;
	}

	template<class T>
	inline bool GameObject::RemoveComponent()
	{
		if (!std::is_base_of<Component, T>())
			return;

		auto pComponent{ GetComponent<T>() };
		if (pComponent)
		{
			DestroyComponent(pComponent);
		}

		return false;
	}


	template<class T>
	inline bool GameObject::HasComponent() const
	{
		if (!std::is_base_of<Component, T>())
			return false;

		for (auto& pComponent : m_pComponents)
		{
			if (std::dynamic_pointer_cast<T>(pComponent))
			{
				return true;
			}
		}

		return false;
	}
}