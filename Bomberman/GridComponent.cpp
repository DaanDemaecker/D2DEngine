#include "pch.h"
#include "GridComponent.h"
#include "Renderer.h"
#include "Transform.h"
#include <algorithm>
#include <fstream>
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "BoxCollider.h"

D2D::GridComponent::GridComponent()
{
	m_pWallTexture = ResourceManager::GetInstance().LoadTexture("Sprites/Wall.png");
	m_pBrickWallTexture = ResourceManager::GetInstance().LoadTexture("Sprites/BrickWall.png");
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
	auto owner{ GetOwner() };

	for (int i{}; i < m_Grid.size(); i++)
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
			break;
		default:
			continue;
			break;
		}

		pWall->GetTransform()->SetWorldPosition(GetGridPos(i));

		pRenderComponent->SetOffset(-m_SquareSize / 2, -m_SquareSize / 2);
		pRenderComponent->SetDestRectBounds(m_SquareSize, m_SquareSize);

		auto pCollider = pWall->AddComponent<BoxCollider>();
		pCollider->SetVariables(m_SquareSize, m_SquareSize, -m_SquareSize / 2, -m_SquareSize / 2);
	}
}
