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
}

void dae::GameObject::FixedUpdate()
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (auto& pRenderComponent : m_pRenderComponents)
	{
		pRenderComponent->Render();
	}
}

void dae::GameObject::PostUpdate()
{
	m_pComponents.erase(std::remove_if(m_pComponents.begin(), m_pComponents.end(), [](std::shared_ptr<Component> pComponent)
		{
			return pComponent->ShouldDestroy();
		}), m_pComponents.end());
}

void dae::GameObject::SetParent(std::weak_ptr<GameObject> pParent)
{
	for (auto& pChild : m_pChildren)
	{
		if (pParent.lock() == pChild.lock())
			return;
	}

	if (!m_pParent.expired())
	{
		auto pCurrentParent{ m_pParent.lock() };

		if (pParent.lock() == pCurrentParent)
			return;

		pCurrentParent.get()->RemoveChild(weak_from_this());
	}

	pParent.lock()->m_pChildren.push_back(weak_from_this());

	m_pParent = pParent;

	m_pTransform->SetDirtyFlag();
}

void dae::GameObject::RemoveChild(std::weak_ptr<GameObject> pChild)
{
	auto pToRemove = pChild.lock().get();

	pToRemove->SetParent(std::weak_ptr<GameObject>());

	m_pChildren.erase(std::remove_if(m_pChildren.begin(), m_pChildren.end(), [&](std::weak_ptr<GameObject> pCurrentChild)
		{
			return pCurrentChild.lock().get() == pToRemove;
		}), m_pChildren.end());
}

void dae::GameObject::DestroyComponent(std::shared_ptr<Component> pComponent)
{
	pComponent->Destroy();
}
