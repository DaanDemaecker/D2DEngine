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
#include "ExplosionComponent.h"
#include "BombComponent.h"
#include "SingleClipAnimator.h"
#include "CapsuleCollider.h"
#include "EnemyAnimator.h"
#include "Powerup.h"
#include "CameraComponent.h"
#include "EnemyManager.h"
#include "PlayerSetup.h"
#include "GameData.h"
#include "Door.h"
#include "EnemyMovementStates.h"
#include <iostream>
#include <regex>

D2D::GridComponent::GridComponent()
{
	const auto& resourceManager = ResourceManager::GetInstance();

	//Walls
	m_pWallTexture = resourceManager.LoadTexture("Sprites/Wall.png");
	m_pBrickWallTexture = resourceManager.LoadTexture("Sprites/BrickWall.png");
	m_pBrickExplosionTexture = resourceManager.LoadTexture("Sprites/Spritesheets/BrickWallDestroy.png");


	//Explosions
	m_pExplosionTextures[ExplosionType::Center] = resourceManager.LoadTexture("Sprites/Spritesheets/Explosion/ExplosionCenter.png");

	m_pExplosionTextures[ExplosionType::LeftMiddle] = resourceManager.LoadTexture("Sprites/Spritesheets/Explosion/ExplosionLeftMiddle.png");
	m_pExplosionTextures[ExplosionType::Left] = resourceManager.LoadTexture("Sprites/Spritesheets/Explosion/ExplosionLeft.png");

	m_pExplosionTextures[ExplosionType::UpMiddle] = resourceManager.LoadTexture("Sprites/Spritesheets/Explosion/ExplosionUpMiddle.png");
	m_pExplosionTextures[ExplosionType::Up] = resourceManager.LoadTexture("Sprites/Spritesheets/Explosion/ExplosionUp.png");

	m_pExplosionTextures[ExplosionType::RightMiddle] = resourceManager.LoadTexture("Sprites/Spritesheets/Explosion/ExplosionRightMiddle.png");
	m_pExplosionTextures[ExplosionType::Right] = resourceManager.LoadTexture("Sprites/Spritesheets/Explosion/ExplosionRight.png");

	m_pExplosionTextures[ExplosionType::DownMiddle] = resourceManager.LoadTexture("Sprites/Spritesheets/Explosion/ExplosionDownMiddle.png");
	m_pExplosionTextures[ExplosionType::Down] = resourceManager.LoadTexture("Sprites/Spritesheets/Explosion/ExplosionDown.png");


	//Enemies
	m_pBalloonTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/BalloonLeft.png"));
	m_pBalloonTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/BalloonRight.png"));
	m_pBalloonTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/BalloonDeath.png"));

	m_pOnealTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/OnealLeft.png"));
	m_pOnealTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/OnealRight.png"));
	m_pOnealTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/OnealDeath.png"));

	m_pDollTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/DollLeft.png"));
	m_pDollTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/DollRight.png"));
	m_pDollTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/DollDeath.png"));

	m_pMinvoTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/MinvoLeft.png"));
	m_pMinvoTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/MinvoRight.png"));
	m_pMinvoTextures.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Enemies/MinvoDeath.png"));


	//Powerups
	m_pPowerupSprites[PowerupType::FireUp] = resourceManager.LoadTexture("Sprites/Powerups/FireUp.png");
	m_pPowerupSprites[PowerupType::BombUp] = resourceManager.LoadTexture("Sprites/Powerups/BombUp.png");
	m_pPowerupSprites[PowerupType::RemoteControl] = resourceManager.LoadTexture("Sprites/Powerups/RemoteControl.png");


	//Door
	m_pDoorTexture = resourceManager.LoadTexture("Sprites/Door.png");


	//Bomb
	m_pBombSprites = resourceManager.LoadTexture("Sprites/SpriteSheets/Bomb.png");


	//Player
	m_pPlayerSprites.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Player/PlayerDown.png"));
	m_pPlayerSprites.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Player/PlayerUp.png"));
	m_pPlayerSprites.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Player/PlayerLeft.png"));
	m_pPlayerSprites.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Player/PlayerRight.png"));
	m_pPlayerSprites.push_back(resourceManager.LoadTexture("Sprites/SpriteSheets/Player/PlayerDie.png"));
}

void D2D::GridComponent::OnSceneUnload()
{
	GameData::GetInstance().ResetPowerups();
}

void D2D::GridComponent::SetGrid(int rows, int columns, float cubeSize)
{
	m_Rows = rows;
	m_Columns = columns;
	m_SquareSize = cubeSize;

	m_Grid.resize(m_Rows * m_Columns);
	std::fill(m_Grid.begin(), m_Grid.end(), GridType::Empty);
}

void D2D::GridComponent::ReadLevelFromFile(const std::string& fileName, float cubeSize, Observer* pMainLevelUIObserver)
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		return;
	}

	srand(static_cast<unsigned int>(time(nullptr)));

	m_Columns = 0;
	m_Rows = 0;
	m_SquareSize = cubeSize;

	int brickChance = 25; //Chance of brick wall spawning in possible place in percentage
	int currentIndex{};

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == 'L')
		{
			for (char c : line)
			{
				switch (c)
				{
				case 'L':
					continue;
					break;
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
		else if (line[0] == 'E')
		{
			ReadEnemies(line);
		}
	}
	file.close();

	SetupPowerupAndWall(pMainLevelUIObserver);
	SetGridWalls();
}

void D2D::GridComponent::ReadEnemies(const std::string& enemyString)
{
	std::cout << enemyString << std::endl;

	std::regex pattern(R"((\d+) (\d+) (\d+) (\d+))");

	m_Enemies.clear();

	std::smatch matches;
	if (std::regex_search(enemyString, matches, pattern))
	{
		for (int i{}; i < matches.size(); ++i)
		{
			if (i == 0)
				continue;

			m_Enemies.push_back(std::stoi(matches[i]));
		}
	}
}

void D2D::GridComponent::Notify(const Event& event)
{
	if (auto bombExplodeEvent{ dynamic_cast<const BombExplodeEvent*>(&event) })
	{
		m_Grid[bombExplodeEvent->gridNumber] = Empty;
		m_pBombs[bombExplodeEvent->gridNumber] = nullptr;
		ExplodeBomb(Center, bombExplodeEvent->gridNumber, bombExplodeEvent->strength, 0);
	}
	else if (auto explosionOverEvent{ dynamic_cast<const ExplosionOverEvent*>(&event) })
	{
		m_Grid[explosionOverEvent->gridIndex] = Empty;
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

void D2D::GridComponent::GiveBomb(int index, BombComponent* pBombComponent)
{
	m_pBombs[index] = pBombComponent;
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
		pCollider->SetVariables(m_SquareSize, m_SquareSize);
	}
}

float D2D::GridComponent::GetLevelWidth()
{
	return m_SquareSize * m_Columns;
}

void D2D::GridComponent::SetupGame(const std::string& levelFile, float cubeSize, Observer* pMainLevelUIObserver, Observer* pLivesDisplay, Observer* pPointsDisplay, const std::string& sceneName)
{
	const auto pEnemyManager{ GetOwner()->CreateNewObject("EnemyManager") };
	m_pEnemyManager = pEnemyManager->AddComponent<EnemyManager>().get();

	ReadLevelFromFile(levelFile, cubeSize, pMainLevelUIObserver);

	auto cameraComponent = GetComponent<CameraComponent>();
	cameraComponent->SetLevelBounds(0, GetLevelWidth());

	AddObserver(m_pEnemyManager);

	m_pEnemyManager->AddObserver(pPointsDisplay);
	m_pEnemyManager->AddSubject(this);

	

	SetupEnemies();

	if (GameData::GetInstance().GetGameMode() == GameMode::SinglePlayer)
	{
		auto player = SetupPlayer(GetOwner(), pMainLevelUIObserver, pLivesDisplay, pPointsDisplay, sceneName, 0, 1, cubeSize, m_pPlayerSprites, m_pBombSprites);
		cameraComponent->SetPlayer(player->GetTransform().get());
	}
	else
	{
		auto player2 = SetupPlayer(GetOwner(), pMainLevelUIObserver, pLivesDisplay, pPointsDisplay, sceneName, 1, 1, cubeSize, m_pPlayerSprites, m_pBombSprites);
		auto player1 = SetupPlayer(GetOwner(), pMainLevelUIObserver, pLivesDisplay, pPointsDisplay, sceneName, 0, 2, cubeSize, m_pPlayerSprites, m_pBombSprites);
		cameraComponent->SetPlayer(player1->GetTransform().get(), player2->GetTransform().get());
	}
}

void D2D::GridComponent::EndGame()
{
	m_pBrickWalls.clear();
	m_pBombs.clear();
	m_Grid.clear();
	m_PlayerSpawns.clear();

	m_pEnemyManager->RemoveSubjects();

	GetOwner()->RemoveAllChildren();
}


void D2D::GridComponent::ExplodeBomb(ExplosionType type, int number, int strength, int currentDistance)
{
	if (m_Grid[number] != Empty)
	{
		if (m_Grid[number] == BrickWall)
		{
			DeleteBrickWall(number);
		}
		else if (m_Grid[number] == Bomb)
		{
			m_pBombs[number]->InstantExplosion();
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
	m_Grid[gridNumber] = Explosion;

	const auto pExplosion = GetOwner()->CreateNewObject("Explosion");
	pExplosion->GetTransform()->SetWorldPosition(GetGridPos(gridNumber));

	auto pExplosionComponent = pExplosion->AddComponent<ExplosionComponent>();
	pExplosionComponent->AddObserver(this);
	pExplosionComponent->SetGridIndex(gridNumber);

	auto pRenderComponent = pExplosion->AddComponent<RenderComponent>();
	pRenderComponent->SetOffset(-m_SquareSize / 2, -m_SquareSize / 2);
	pRenderComponent->SetDestRectBounds(m_SquareSize, m_SquareSize);

	auto pAnimator = pExplosion->AddComponent<SelfDestroyingAnimator>();
	pAnimator->Init(pRenderComponent.get(), m_pExplosionTextures[type], 4, 1, 4);

	auto pCollider = pExplosion->AddComponent<BoxCollider>();
	pCollider->AddToPhysicsManager(true);
	pCollider->SetVariables(m_SquareSize, m_SquareSize);
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

void D2D::GridComponent::SetupEnemies()
{
	for (int j{}; j < m_Enemies.size(); ++j)
	{

		for (int i{}; i < m_Enemies[j]; ++i)
		{
			bool goodPosition{ false };
			int position{};

			while (!goodPosition)
			{
				position = rand() % m_Grid.size();

				goodPosition = m_Grid[position] == Empty && position % m_Columns > m_EnemieBorder;
			}
			SpawnEnemy(position, static_cast<EnemyType>(j));
		}
	}
}

void D2D::GridComponent::SpawnEnemy(int number, EnemyType type)
{
	const float enemyTriggerHeight{ m_SquareSize * .9f };
	const float enemyTriggerWidth{ m_SquareSize  * 0.8f };

	const float enemyHeight{ enemyTriggerHeight * 0.9f };
	const float enemyWidth{ enemyTriggerWidth * 0.9f };

	const float slowSpeed{ 1.5f * m_SquareSize };
	const float normalSpeed{ slowSpeed * 1.5f };
	const float fastSpeed{ slowSpeed * 2.f };


	const auto pEnemy = GetOwner()->CreateNewObject("Enemy");
	pEnemy->GetTransform()->SetWorldPosition(GetGridPos(number));

	auto pRenderComponent = pEnemy->AddComponent<RenderComponent>();
	pRenderComponent->SetOffset(-enemyWidth / 2, -enemyHeight / 2);
	pRenderComponent->SetDestRectBounds(enemyWidth, enemyHeight);

	auto pAnimator = pEnemy->AddComponent<EnemyAnimator>();

	auto pTrigger = pEnemy->AddComponent<BoxCollider>();
	pTrigger->SetVariables(enemyTriggerWidth, enemyTriggerHeight);
	pTrigger->AddToPhysicsManager(true);

	auto pCollider = pEnemy->AddComponent<CapsuleCollider>();
	pCollider->SetVariables(enemyHeight, enemyWidth / 2);
	pCollider->AddToPhysicsManager(false);
	auto pEnemyComponent = pEnemy->AddComponent<BaseEnemyComponent>();

	switch (type)
	{
	case D2D::EnemyType::Balloom:
		pAnimator->Init(pRenderComponent.get(), m_pBalloonTextures);
		pEnemyComponent->SetVariables(type, slowSpeed, pCollider.get(), pTrigger.get());
		pEnemyComponent->SetMovementState(std::make_unique<EnemyWanderState>(enemyWidth / 2.5f, enemyHeight / 2.5f, enemyHeight * 0.6f, m_SquareSize));
		break;
	case D2D::EnemyType::Oneal:
		pAnimator->Init(pRenderComponent.get(), m_pOnealTextures);
		pEnemyComponent->SetVariables(type, normalSpeed, pCollider.get(), pTrigger.get());
		pEnemyComponent->SetMovementState(std::make_unique<EnemyLookingState>(enemyWidth / 2.5f, enemyHeight / 2.5f, enemyHeight * 0.6f, m_SquareSize, 3.f * m_SquareSize));
		break;
	case D2D::EnemyType::Doll:
		pAnimator->Init(pRenderComponent.get(), m_pDollTextures);
		pEnemyComponent->SetVariables(type, normalSpeed, pCollider.get(), pTrigger.get());
		pEnemyComponent->SetMovementState(std::make_unique<EnemyWanderState>(enemyWidth / 2.5f, enemyHeight / 2.5f, enemyHeight * 0.6f, m_SquareSize));
		break;
	case D2D::EnemyType::Minvo:
		pAnimator->Init(pRenderComponent.get(), m_pMinvoTextures);
		pEnemyComponent->SetVariables(type, fastSpeed, pCollider.get(), pTrigger.get());
		pEnemyComponent->SetMovementState(std::make_unique<EnemyLookingState>(enemyWidth / 2.5f, enemyHeight / 2.5f, enemyHeight * 0.6f, m_SquareSize, 3.f * m_SquareSize));
		break;
	default:
		break;
	}

	auto spawnEvent = EnemySpawnEvent();
	spawnEvent.pEnemy = pEnemyComponent.get();
	NotifyObservers(spawnEvent);
}

void D2D::GridComponent::SetupPowerupAndWall(Observer* pMainLevelUIObserver)
{
	int doorIndex{};
	int powerupIndex{};

	do
	{
		doorIndex = rand() % m_Grid.size();
	} while (m_Grid[doorIndex] != BrickWall);

	do
	{
		powerupIndex = rand() % m_Grid.size();
	} while (m_Grid[powerupIndex] != BrickWall || powerupIndex == doorIndex);


	SpawnDoor(doorIndex, pMainLevelUIObserver);
	SpawnPowerup(powerupIndex);
}

void D2D::GridComponent::SpawnDoor(int gridIndex, Observer* pMainLevelUIObserver)
{
	auto pDoor = GetOwner()->CreateNewObject("Door");

	pDoor->GetTransform()->SetWorldPosition(GetGridPos(gridIndex));

	auto pRenderComponent = pDoor->AddComponent<RenderComponent>();
	pRenderComponent->SetOffset(-m_SquareSize / 2, -m_SquareSize / 2);
	pRenderComponent->SetDestRectBounds(m_SquareSize, m_SquareSize);
	pRenderComponent->SetTexture(m_pDoorTexture);

	auto pCollider = pDoor->AddComponent<BoxCollider>();
	pCollider->SetVariables(m_SquareSize * 0.9f, m_SquareSize * 0.9f);
	pCollider->AddToPhysicsManager(true);


	auto pDoorComponent = pDoor->AddComponent<Door>();
	m_pEnemyManager->AddObserver(pDoorComponent.get());
	pDoorComponent->AddObserver(pMainLevelUIObserver);
}

void D2D::GridComponent::SpawnPowerup(int gridIndex)
{
	auto pPowerup = GetOwner()->CreateNewObject("Powerup");

	PowerupType powerupType = static_cast<PowerupType>(rand() % 3);

	pPowerup->GetTransform()->SetWorldPosition(GetGridPos(gridIndex));

	auto powerupComponent = pPowerup->AddComponent<Powerup>();
	powerupComponent->SetType(powerupType);

	auto pRenderComponent = pPowerup->AddComponent<RenderComponent>();
	pRenderComponent->SetOffset(-m_SquareSize / 2, -m_SquareSize / 2);
	pRenderComponent->SetDestRectBounds(m_SquareSize, m_SquareSize);
	if (m_pPowerupSprites.contains(powerupType))
	{
		pRenderComponent->SetTexture(m_pPowerupSprites[powerupType]);
	}

	auto pTrigger = pPowerup->AddComponent<BoxCollider>();
	pTrigger->SetVariables(m_SquareSize * 0.8f, m_SquareSize * 0.8f);
	pTrigger->AddToPhysicsManager(true);
}
