#include "pch.h"
#include "BombManagerComponent.h"
#include "PlayerEvents.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "BoxCollider.h"
#include "GridComponent.h"

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

void D2D::BombManagerComponent::SetGrid(GridComponent* grid)
{
	m_pGrid = grid;
}

void D2D::BombManagerComponent::SpawnBomb(const glm::vec2& pos)
{
	if (m_pGrid == nullptr)
		return;


	D2D::PlaceBombResponse response{};

	m_pGrid->SetBomb(pos, response);

	if (!response.success)
		return;

	const auto pBomb = GetOwner()->CreateNewObject("Bomb");
	pBomb->GetTransform()->SetWorldPosition(response.position);

	auto pRenderComponent = pBomb->AddComponent<RenderComponent>();
	pRenderComponent->SetTexture(m_pBombtexture);
	pRenderComponent->SetOffset(-m_BombTextureSize/2, -m_BombTextureSize/2);
	pRenderComponent->SetDestRectBounds(m_BombTextureSize, m_BombTextureSize);

	auto pCollider = pBomb->AddComponent<BoxCollider>();
	pCollider->SetVariables(m_BombTextureSize, m_BombTextureSize, -m_BombTextureSize/2, -m_BombTextureSize/2);
}
