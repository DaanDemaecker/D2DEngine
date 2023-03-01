#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "RenderComponent.h"

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

void dae::GameObject::DestroyComponent(std::shared_ptr<Component> pComponent)
{
	pComponent->Destroy();
}
