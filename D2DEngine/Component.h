#pragma once
#include <memory>
#include "GameObject.h"

namespace D2D
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update() {};

		virtual void FixedUpdate() {};

		virtual void LateUpdate() {};

		virtual void Render() const {};

		virtual void OnGUI() {};
		
		void Destroy() { m_ShouldDestroy = true; }
		bool ShouldDestroy() { return m_ShouldDestroy; }



		template <class T>
		friend std::shared_ptr<T> GameObject::AddComponent();

		template <class T>
		std::shared_ptr<T> GetComponent() const;

		template <class T>
		bool HasComponent() const;

	protected:
		GameObject* GetOwner() const { return m_pOwner; }

	private:
		GameObject* m_pOwner{};

		void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
		
		bool m_ShouldDestroy{false};
	};


	template<class T>
	inline std::shared_ptr<T> Component::GetComponent() const
	{
		if (!std::is_base_of<Component, T>())
			return nullptr;

		if (m_pOwner == nullptr)
			return nullptr;

		return m_pOwner->GetComponent<T>();
	}

	template<class T>
	inline bool Component::HasComponent() const
	{
		if (!std::is_base_of<Component, T>())
			return false;

		if (m_pOwner == nullptr)
			return false;

		return m_pOwner->HasComponent<T>();
	}
}

