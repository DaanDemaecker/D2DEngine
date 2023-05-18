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
#include "Powerup.h"

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
	else if (auto bombExplodeEvent{ dynamic_cast<const BombExplodeEvent*>(&event) })
	{
		if (!m_pBombs.empty())
		{
			m_pBombs[m_pBombs.size()-1]->InstantExplosion();

			m_pBombs.erase(std::remove_if(m_pBombs.begin(), m_pBombs.end(), [&](BombComponent* pBomb) {return pBomb->GetGridNumber() == bombExplodeEvent->gridNumber; }), m_pBombs.end());
		}
	}
	else if (auto powerupCollectedEvent{ dynamic_cast<const PowerupCollectedEvent*>(&event) })
	{
		switch (powerupCollectedEvent->type)
		{
		case PowerupType::FireUp:
			m_BombStrength++;
			break;
		case PowerupType::BombUp:
			m_BombAmount++;
			break;
		case PowerupType::RemoteControl:
			m_RemoteControlActive = true;
			break;
		default:
			break;
		}
	}
}

void D2D::BombManagerComponent::SetGrid(GridComponent* grid)
{
	m_pGrid = grid;
}

void D2D::BombManagerComponent::RemoteControlTriggered()
{
	if (m_RemoteControlActive && !m_pBombs.empty())
	{
		m_pBombs[0]->InstantExplosion();
	}
}

void D2D::BombManagerComponent::SpawnBomb(const glm::vec2& pos)
{
	if (m_pGrid == nullptr || static_cast<int>(m_pBombs.size()) >= m_BombAmount)
		return;

	D2D::PlaceBombResponse response{};

	m_pGrid->SetBomb(pos, response);

	if (!response.success)
		return;

	ServiceLocator::GetSoundSystem().Play(0, 128);

	const auto pBomb = GetOwner()->CreateNewObject("Bomb");
	pBomb->GetTransform()->SetWorldPosition(response.position);

	auto pRenderComponent = pBomb->AddComponent<RenderComponent>();
	pRenderComponent->SetOffset(-m_BombSize/2, -m_BombSize/2);
	pRenderComponent->SetDestRectBounds(m_BombSize, m_BombSize);

	auto pAnimator = pBomb->AddComponent<SingleClipAnimator>();
	pAnimator->Init(pRenderComponent.get(), m_pBombtexture, 3, 1, 3);

	auto pCollider = pBomb->AddComponent<BoxCollider>();
	pCollider->AddToPhysicsManager();
	pCollider->SetVariables(m_BombSize, m_BombSize);

	auto pBombComponent = pBomb->AddComponent<BombComponent>();
	m_pGrid->GiveBomb(response.index, pBombComponent.get());
	pBombComponent->SetBombStrength(m_BombStrength);
	pBombComponent->SetGridNumber(response.index);
	pBombComponent->AddObserver(m_pGrid);
	pBombComponent->AddObserver(this);

	m_pBombs.push_back(pBombComponent.get());
}
