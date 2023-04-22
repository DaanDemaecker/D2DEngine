#include "pch.h"
#include "BombManagerComponent.h"
#include "PlayerEvents.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "RenderComponent.h"

D2D::BombManagerComponent::BombManagerComponent()
{
	const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

	m_pBombtexture = pResourceManager.LoadTexture("sprites/Bomb.png");
}

void D2D::BombManagerComponent::Notify(const Event& event)
{
	if (auto placeBombEvent{ dynamic_cast<const PlaceBombEvent*>(&event) })
	{
		SpawnBomb(placeBombEvent->position);
	}
}

void D2D::BombManagerComponent::SpawnBomb(const glm::vec2& pos)
{
	const auto pBomb = GetOwner()->CreateNewObject("Bomb");
	pBomb->GetTransform()->SetWorldPosition(pos);
	pBomb->AddComponent<RenderComponent>()->SetTexture(m_pBombtexture);
}
