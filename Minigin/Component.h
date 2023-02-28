#pragma once
#include <memory>
#include "GameObject.h"

namespace dae
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
		
		void Destroy() { m_ShouldDestroy = true; }
		bool ShouldDestroy() { return m_ShouldDestroy; }



		template <class T>
		friend std::shared_ptr<T> GameObject::AddComponent();

		template <class T>
		std::shared_ptr<T> GetComponent() const;

	protected:
		std::weak_ptr<GameObject> m_pParent{};

	private:
		void SetParent(std::weak_ptr<GameObject> pParent) { m_pParent = pParent; }
		
		bool m_ShouldDestroy{false};
	};


	template<class T>
	inline std::shared_ptr<T> Component::GetComponent() const
	{
		if (!std::is_base_of<Component, T>())
			return nullptr;

		if (m_pParent.expired())
			return nullptr;

		return m_pParent.lock()->GetComponent<T>();
	}
}

