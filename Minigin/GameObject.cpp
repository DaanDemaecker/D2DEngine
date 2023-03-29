#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "RenderComponent.h"
#include "Transform.h"

void dae::GameObject::Init()
{
	m_pTransform = AddComponent<Transform>();
}

void dae::GameObject::Update()
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Update();
	}

	for (auto& pChild : m_pChildren)
	{
		pChild->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->FixedUpdate();
	}

	for (auto& pChild : m_pChildren)
	{
		pChild->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Render();
	}


	for (auto& pChild : m_pChildren)
	{
		pChild->Render();
	}
}

void dae::GameObject::PostUpdate()
{
	m_pComponents.erase(std::remove_if(m_pComponents.begin(), m_pComponents.end(), [](std::shared_ptr<Component>& pComponent)
		{
			return pComponent->ShouldDestroy();
		}), m_pComponents.end());


	for (auto& pChild : m_pChildren)
	{
		pChild->PostUpdate();
	}
}

dae::GameObject* dae::GameObject::CreateNewObject()
{
	auto pNewObject{ std::make_unique<GameObject>() };

	pNewObject->Init();

	pNewObject->m_pParent = this;

	return m_pChildren.emplace_back(std::move(pNewObject)).get();
}

void dae::GameObject::SetParent(GameObject* pParent, bool worldPositionStays)
{
	if (pParent == nullptr || m_pParent == nullptr)
	{
		GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	}
	else
	{
		if (worldPositionStays)
		{
			GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() -
				GetParent()->GetTransform()->GetWorldPosition());
		}
		GetTransform()->SetDirtyFlag();
	}

	std::unique_ptr<GameObject> child;

	if (m_pParent != nullptr)
	{
		for (auto it = m_pParent->m_pChildren.begin(); it != m_pParent->m_pChildren.end(); it++)
		{
			if (it->get() == this)
			{
				child = std::move(*it);
				m_pParent->m_pChildren.erase(it);
				break;
			}
		}
	}

	m_pParent = pParent;

	if (m_pParent != nullptr)
	{
		if (child == nullptr)
		{
			child = std::unique_ptr<GameObject>(this);
		}

		m_pParent->m_pChildren.emplace_back(std::move(child));
	}
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	pChild->SetParent(nullptr, true);

	m_pChildren.erase(std::remove_if(m_pChildren.begin(), m_pChildren.end(), [&](std::unique_ptr<GameObject>& pCurrentChild)
		{
			return pCurrentChild.get() == pChild;
		}), m_pChildren.end());
}

bool dae::GameObject::ContainsChild(GameObject* pChild) const
{
	for (const auto& child : m_pChildren)
	{
		if (child.get() == pChild)
			return true;
	}
	return false;
}

void dae::GameObject::DestroyComponent(std::shared_ptr<Component> pComponent)
{
	pComponent->Destroy();
}
