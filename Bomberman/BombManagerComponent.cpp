#include "pch.h"
#include "BombManagerComponent.h"
#include "PlayerEvents.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "BoxCollider.h"
#include "GridComponent.h"
#include "BombAnimator.h"
#include "AnimationClip.h"

D2D::BombManagerComponent::BombManagerComponent()
{
	const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

	m_pBombtexture = pResourceManager.LoadTexture("sprites/SpriteSheets/Bomb.png");
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
	pRenderComponent->SetOffset(-m_BombSize/2, -m_BombSize/2);
	pRenderComponent->SetDestRectBounds(m_BombSize, m_BombSize);

	auto pAnimator = pBomb->AddComponent<BombAnimator>();
	pAnimator->Init(pRenderComponent.get(), m_pBombtexture);

	auto pCollider = pBomb->AddComponent<BoxCollider>();
	pCollider->SetVariables(m_BombSize, m_BombSize, -m_BombSize/2, -m_BombSize/2);
}
