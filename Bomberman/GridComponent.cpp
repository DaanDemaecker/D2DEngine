#include "pch.h"
#include "GridComponent.h"
#include "Renderer.h"
#include "Transform.h"
#include <algorithm>
#include <fstream>
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "BoxCollider.h"
#include "WorldEvents.h"
#include "SelfDestroyingAnimator.h"
#include "AnimationClip.h"

D2D::GridComponent::GridComponent()
{
	m_pWallTexture = ResourceManager::GetInstance().LoadTexture("Sprites/Wall.png");
	m_pBrickWallTexture = ResourceManager::GetInstance().LoadTexture("Sprites/BrickWall.png");
	m_pBrickExplosionTexture = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/BrickWallDestroy.png");

	m_pExplosionTextures[ExplosionType::Center] = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/Explosion/ExplosionCenter.png");

	m_pExplosionTextures[ExplosionType::LeftMiddle] = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/Explosion/ExplosionLeftMiddle.png");
	m_pExplosionTextures[ExplosionType::Left] = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/Explosion/ExplosionLeft.png");

	m_pExplosionTextures[ExplosionType::UpMiddle] = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/Explosion/ExplosionUpMiddle.png");
	m_pExplosionTextures[ExplosionType::Up] = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/Explosion/ExplosionUp.png");

	m_pExplosionTextures[ExplosionType::RightMiddle] = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/Explosion/ExplosionRightMiddle.png");
	m_pExplosionTextures[ExplosionType::Right] = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/Explosion/ExplosionRight.png");

	m_pExplosionTextures[ExplosionType::DownMiddle] = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/Explosion/ExplosionDownMiddle.png");
	m_pExplosionTextures[ExplosionType::Down] = ResourceManager::GetInstance().LoadTexture("Sprites/Spritesheets/Explosion/ExplosionDown.png");

}

void D2D::GridComponent::SetGrid(int rows, int columns, float cubeSize)
{
	m_Rows = rows;
	m_Columns = columns;
	m_SquareSize = cubeSize;

	m_Grid.resize(m_Rows * m_Columns);
	std::fill(m_Grid.begin(), m_Grid.end(), GridType::Empty);
}

void D2D::GridComponent::SetGrid(const std::string& fileName, float cubeSize)
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		return;
	}

	m_Columns = 0;
	m_Rows = 0;
	m_SquareSize = cubeSize;

	int brickChance = 25; //Chance of brick wall spawning in possible place in percentage
	int currentIndex{};

	std::string line;
	while (std::getline(file, line)) {
		for (char c : line)
		{
			switch (c) {
			case 'w':
				m_Grid.push_back(D2D::Wall);
				break;
			case 'b':
			{
				int random = rand() % 100;
				if (random <= brickChance)
				{
					m_Grid.push_back(D2D::BrickWall);
				}
				else
				{
					m_Grid.push_back(D2D::Empty);
				}
			}
				break;
			case 'p':
				m_PlayerSpawns.push_back(currentIndex);
			case 'e':
				m_Grid.push_back(D2D::Empty);
				break;
			}
			++currentIndex;
			if (m_Rows == 0)
				++m_Columns;
		}
		m_Rows++;
	}
	file.close();

	SetGridWalls();
}

void D2D::GridComponent::Notify(const Event& event)
{
	if (auto bombExplodeEvent{ dynamic_cast<const BombExplodeEvent*>(&event) })
	{
		m_Grid[bombExplodeEvent->gridNumber] = Empty;
		ExplodeBomb(Center, bombExplodeEvent->gridNumber, bombExplodeEvent->strength, 0);
	}
}

void D2D::GridComponent::Render() const
{
	/*auto pos = GetOwner()->GetTransform()->GetWorldPosition();

	for (int x{}; x < m_Columns; x++)
	{
		for (int y{}; y < m_Rows; y++)
		{
			Renderer::GetInstance().DrawRect(m_SquareSize * x + pos.x, m_SquareSize * y + pos.y, m_SquareSize, m_SquareSize);
		}
	}*/
}

void D2D::GridComponent::SetBomb(const glm::vec2 position, D2D::PlaceBombResponse& response)
{
	int index{ GetGridNumber(position) };

	response.success = m_Grid[index] == D2D::Empty;

	if (response.success)
	{
		response.index = index;
		response.position = GetGridPos(index);
		m_Grid[index] = D2D::Bomb;
		return;
	}
	else
	{
		return;
	}
}

glm::vec2 D2D::GridComponent::GetPlayerPosition(int index)
{
	return GetGridPos(m_PlayerSpawns[index]);
}

glm::vec2 D2D::GridComponent::WorldToGridPos(const glm::vec2& pos)
{
	return GetGridPos(GetGridNumber(pos));
}

int D2D::GridComponent::GetGridNumber(const glm::vec2& pos)
{
	int x{};
	int y{};

	x = static_cast<int>(pos.x / m_SquareSize);
	y = static_cast<int>(pos.y / m_SquareSize);
	

	if (x < 0 || x >= m_Columns || y < 0 || y >= m_Rows)
		return 0;

	return y * m_Columns + x;
}

glm::vec2 D2D::GridComponent::GetGridPos(int square)
{
	int x{};
	int y{};

	x = square % m_Columns;
	y = (square - x) / m_Columns;

	return GetOwner()->GetTransform()->GetWorldPosition() + glm::vec2(x * m_SquareSize + m_SquareSize/2, y * m_SquareSize + m_SquareSize/2);
}

void D2D::GridComponent::SetGridWalls()
{
	for (size_t i{}; i < m_Grid.size(); i++)
	{
		if (m_Grid[i] == D2D::Empty)
			continue;

		GameObject* pWall{};
		std::shared_ptr<RenderComponent> pRenderComponent{};

		switch (m_Grid[i])
		{
		case D2D::Wall:
			pWall = GetOwner()->CreateNewObject("Wall");
			pRenderComponent = pWall->AddComponent<RenderComponent>();
			pRenderComponent->SetTexture(m_pWallTexture);
			break;
		case D2D::BrickWall:
			pWall = GetOwner()->CreateNewObject("BrickWall");
			pRenderComponent = pWall->AddComponent<RenderComponent>();
			pRenderComponent->SetTexture(m_pBrickWallTexture);

			m_pBrickWalls.insert(std::make_pair(static_cast<int>(i), pWall));
			break;
		default:
			continue;
			break;
		}

		pWall->GetTransform()->SetWorldPosition(GetGridPos(static_cast<int>(i)));

		pRenderComponent->SetOffset(-m_SquareSize / 2, -m_SquareSize / 2);
		pRenderComponent->SetDestRectBounds(m_SquareSize, m_SquareSize);

		auto pCollider = pWall->AddComponent<BoxCollider>();
		pCollider->AddToPhysicsManager();
		pCollider->SetVariables(m_SquareSize, m_SquareSize, -m_SquareSize / 2, -m_SquareSize / 2);
	}
}

float D2D::GridComponent::GetLevelWidth()
{
	return m_SquareSize * m_Columns;
}

void D2D::GridComponent::ExplodeBomb(ExplosionType type, int number, int strength, int currentDistance)
{
	if (m_Grid[number] != Empty)
	{
		if (m_Grid[number] == BrickWall)
		{
			DeleteBrickWall(number);
		}
		return;
	}

	switch (type)
	{
	case D2D::Center:
		CreateExplosion(Center, number);
		ExplodeBomb(Left, GetLeftNeighbour(number), strength, currentDistance + 1);
		ExplodeBomb(Up, GetTopNeighbour(number), strength, currentDistance + 1);
		ExplodeBomb(Right, GetRightNeighbour(number), strength, currentDistance + 1);
		ExplodeBomb(Down, GetBottomNeighbour(number), strength, currentDistance + 1);
		break;
	case D2D::Left:
		if (currentDistance < strength)
		{
			ExplodeBomb(Left, GetLeftNeighbour(number), strength, currentDistance + 1);
			CreateExplosion(LeftMiddle, number);
		}
		else
		{
			CreateExplosion(Left, number);
		}
		break;
	case D2D::Up:
		if (currentDistance < strength)
		{
			ExplodeBomb(Up, GetTopNeighbour(number), strength, currentDistance + 1);
			CreateExplosion(UpMiddle, number);
		}
		else
		{
			CreateExplosion(Up, number);
		}
		break;
	case D2D::Right:
		if (currentDistance < strength)
		{
			ExplodeBomb(Right, GetRightNeighbour(number), strength, currentDistance + 1);
			CreateExplosion(RightMiddle, number);
		}
		else
		{
			CreateExplosion(Right, number);
		}
		break;
	case D2D::Down:
		if (currentDistance < strength)
		{
			ExplodeBomb(Down, GetBottomNeighbour(number), strength, currentDistance + 1);
			CreateExplosion(DownMiddle, number);
		}
		else
		{
			CreateExplosion(Down, number);
		}
		break;
	}
}

void D2D::GridComponent::CreateExplosion(ExplosionType type, int gridNumber)
{
	const auto pExplosion = GetOwner()->CreateNewObject("Explosion");
	pExplosion->GetTransform()->SetWorldPosition(GetGridPos(gridNumber));

	auto pRenderComponent = pExplosion->AddComponent<RenderComponent>();
	pRenderComponent->SetOffset(-m_SquareSize / 2, -m_SquareSize / 2);
	pRenderComponent->SetDestRectBounds(m_SquareSize, m_SquareSize);

	auto pAnimator = pExplosion->AddComponent<SelfDestroyingAnimator>();
	pAnimator->Init(pRenderComponent.get(), m_pExplosionTextures[type], 4, 1, 4);

	auto pCollider = pExplosion->AddComponent<BoxCollider>();
	pCollider->AddToPhysicsManager(true);
	pCollider->SetVariables(m_SquareSize, m_SquareSize, -m_SquareSize / 2, -m_SquareSize / 2);
}

int D2D::GridComponent::GetTopNeighbour(int number)
{
	return number - m_Columns;
}

int D2D::GridComponent::GetBottomNeighbour(int number)
{
	return number + m_Columns;
}

int D2D::GridComponent::GetLeftNeighbour(int number)
{
	return number - 1;
}

int D2D::GridComponent::GetRightNeighbour(int number)
{
	return number + 1;
}

void D2D::GridComponent::DeleteBrickWall(int number)
{
	auto iter = m_pBrickWalls.find(number);
	if (iter != m_pBrickWalls.end())
	{
		iter->second->Destroy();
		m_pBrickWalls.erase(iter);
		m_Grid[number] = Empty;

		const auto pExplosion = GetOwner()->CreateNewObject("ExplodingBrick");
		pExplosion->GetTransform()->SetWorldPosition(GetGridPos(number));

		auto pRenderComponent = pExplosion->AddComponent<RenderComponent>();
		pRenderComponent->SetOffset(-m_SquareSize / 2, -m_SquareSize / 2);
		pRenderComponent->SetDestRectBounds(m_SquareSize, m_SquareSize);

		auto pAnimator = pExplosion->AddComponent<SelfDestroyingAnimator>();
		pAnimator->Init(pRenderComponent.get(), m_pBrickExplosionTexture, 4, 1, 4);
	}
}
