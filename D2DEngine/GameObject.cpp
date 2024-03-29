#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "InputManager.h"
#include <iostream>

D2D::GameObject::~GameObject()
{
}

void D2D::GameObject::Init()
{
	m_pTransform = AddComponent<Transform>();
}

void D2D::GameObject::OnSceneLoad()
{
	for (auto& pcomponent : m_pComponents)
	{
		pcomponent->OnSceneLoad();
	}

	for (auto& pChild : m_pChildren)
	{
		pChild->OnSceneLoad();
	}
}

void D2D::GameObject::OnSceneUnload()
{
	for (auto& pcomponent : m_pComponents)
	{
		pcomponent->OnSceneUnload();
	}

	for (auto& pChild : m_pChildren)
	{
		pChild->OnSceneUnload();
	}
}

void D2D::GameObject::StartFrame()
{
	for (size_t i{}; i < m_pChildrenToAdd.size(); ++i)
	{
		m_pChildren.push_back(std::move(m_pChildrenToAdd[i]));
	}

	m_pChildrenToAdd.clear();

	for (auto& pChild : m_pChildren)
	{
		if (pChild->IsActive())
		{
			pChild->StartFrame();
		}
	}
}

void D2D::GameObject::Update()
{
	for (auto& pComponent : m_pComponents)
	{
		if (pComponent->IsActive())
		{
			pComponent->Update();
		}
	}

	for (auto& pChild : m_pChildren)
	{
		if (pChild->IsActive())
		{
			pChild->Update();
		}
	}
}

void D2D::GameObject::FixedUpdate()
{
	for (auto& pComponent : m_pComponents)
	{
		if (pComponent->IsActive())
		{
			pComponent->FixedUpdate();
		}
	}

	for (auto& pChild : m_pChildren)
	{
		if (pChild->IsActive())
		{
			pChild->FixedUpdate();
		}
	}
}

void D2D::GameObject::LateUpdate()
{
	for (auto& pComponent : m_pComponents)
	{
		if (pComponent->IsActive())
		{
			pComponent->LateUpdate();
		}
	}

	for (auto& pChild : m_pChildren)
	{
		if (pChild->IsActive())
		{
			pChild->LateUpdate();
		}
	}

}

void D2D::GameObject::Render() const
{
	for (auto& pComponent : m_pComponents)
	{
		if (pComponent->IsActive())
		{
			pComponent->Render();
		}
	}

	for (auto& pChild : m_pChildren)
	{
		if (pChild->IsActive())
		{
			pChild->Render();
		}
	}
}

void D2D::GameObject::OnGUI()
{
	for (auto& pComponent : m_pComponents)
	{
		if (pComponent->IsActive())
		{
			pComponent->OnGUI();
		}
	}

	for (auto& pChild : m_pChildren)
	{
		if (pChild->IsActive())
		{
			pChild->OnGUI();
		}
	}
}

void D2D::GameObject::PostUpdate()
{
	m_pComponents.erase(std::remove_if(m_pComponents.begin(), m_pComponents.end(), [](std::shared_ptr<Component>& pComponent)
		{
			return pComponent->ShouldDestroy();
		}), m_pComponents.end());

	m_pChildren.erase(std::remove_if(m_pChildren.begin(), m_pChildren.end(), [](std::unique_ptr<GameObject>& pChild)
		{
			return pChild->ShouldDestroy();
		}), m_pChildren.end());


	for (auto& pChild : m_pChildren)
	{
		if (pChild->IsActive())
		{
			pChild->PostUpdate();
		}
	}
}

void D2D::GameObject::Destroy()
{
	m_ShouldDestroy = true;

	for (auto& child : m_pChildren)
	{
		child->Destroy();
	}

	for (auto& component : m_pComponents)
	{
		component->Destroy();
	}
}

D2D::GameObject* D2D::GameObject::CreateNewObject(const std::string& name, const std::string& tag)
{
	auto pNewObject{ std::make_unique<GameObject>(name, tag) };

	pNewObject->Init();

	pNewObject->m_pParent = this;

	return m_pChildrenToAdd.emplace_back(std::move(pNewObject)).get();
}

void D2D::GameObject::RemoveAllChildren()
{
	m_pChildren.clear();
	m_pChildrenToAdd.clear();
}

void D2D::GameObject::OnTriggerEnter(const Collider* pCollider)
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->OnTriggerEnter(pCollider);
	}
}

void D2D::GameObject::OnTriggerExit(const Collider* pCollider)
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->OnTriggerExit(pCollider);
	}
}

void D2D::GameObject::SetParent(GameObject* pParent, bool worldPositionStays)
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

void D2D::GameObject::RemoveChild(GameObject* pChild)
{
	pChild->SetParent(nullptr, true);

	m_pChildren.erase(std::remove_if(m_pChildren.begin(), m_pChildren.end(), [&](std::unique_ptr<GameObject>& pCurrentChild)
		{
			return pCurrentChild.get() == pChild;
		}), m_pChildren.end());
}

bool D2D::GameObject::ContainsChild(GameObject* pChild) const
{
	for (const auto& child : m_pChildren)
	{
		if (child.get() == pChild)
			return true;
	}
	return false;
}

void D2D::GameObject::SetActive(bool isActive)
{
	m_IsActive = isActive;

	for (auto& pComponent : m_pComponents)
	{
		pComponent->SetActive(isActive);
	}

	for (auto& pChild : m_pChildren)
	{
		pChild->SetActive(isActive);
	}
}

void D2D::GameObject::DestroyComponent(std::shared_ptr<Component> pComponent)
{
	pComponent->Destroy();
}
