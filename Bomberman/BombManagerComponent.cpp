#include "pch.h"
#include "BombManagerComponent.h"
#include "PlayerEvents.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "BoxCollider.h"
#include "GridComponent.h"
#include "SingleClipAnimator.h"
#include "AnimationClip.h"
#include "BombComponent.h"
#include "WorldEvents.h"
#include "ServiceLocator.h"

D2D::BombManagerComponent::BombManagerComponent()
{
	const auto& pResourceManager{ D2D::ResourceManager::GetInstance() };

	m_pBombtexture = pResourceManager.LoadTexture("sprites/SpriteSheets/Bomb.png");


	m_CurrentBombAmount = m_BombAmount;
}

void D2D::BombManagerComponent::Notify(const Event& event)
{
	if (auto placeBombEvent{ dynamic_cast<const PlaceBombEvent*>(&event) })
	{
		SpawnBomb(placeBombEvent->position);
	}
	else if (auto bombExplodeEvent{ dynamic_cast<const BombExplodeEvent*>(&event) })
	{
		++m_CurrentBombAmount;
	}
}

void D2D::BombManagerComponent::SetGrid(GridComponent* grid)
{
	m_pGrid = grid;
}

void D2D::BombManagerComponent::SpawnBomb(const glm::vec2& pos)
{
	if (m_pGrid == nullptr || m_CurrentBombAmount <= 0)
		return;

	D2D::PlaceBombResponse response{};

	m_pGrid->SetBomb(pos, response);

	if (!response.success)
		return;

	ServiceLocator::GetSoundSystem().Play(0, 128);

	m_CurrentBombAmount--;

	const auto pBomb = GetOwner()->CreateNewObject("Bomb");
	pBomb->GetTransform()->SetWorldPosition(response.position);

	auto pRenderComponent = pBomb->AddComponent<RenderComponent>();
	pRenderComponent->SetOffset(-m_BombSize/2, -m_BombSize/2);
	pRenderComponent->SetDestRectBounds(m_BombSize, m_BombSize);

	auto pAnimator = pBomb->AddComponent<SingleClipAnimator>();
	pAnimator->Init(pRenderComponent.get(), m_pBombtexture, 3, 1, 3);

	auto pCollider = pBomb->AddComponent<BoxCollider>();
	pCollider->AddToPhysicsManager();
	pCollider->SetVariables(m_BombSize, m_BombSize, -m_BombSize/2, -m_BombSize/2);

	auto pBombComponent = pBomb->AddComponent<BombComponent>();
	m_pGrid->GiveBomb(response.index, pBombComponent.get());
	pBombComponent->SetBombStrength(m_BombStrength);
	pBombComponent->SetGridNumber(response.index);
	pBombComponent->AddObserver(m_pGrid);
	pBombComponent->AddObserver(this);
}
