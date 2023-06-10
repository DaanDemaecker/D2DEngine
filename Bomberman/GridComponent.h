#pragma once
#include "Component.h"
#include "PlayerComponent.h"
#include "Observer.h"
#include "BaseEnemyComponent.h"
#include <map>

namespace D2D
{
	class TextComponent;
	class PlayerComponent;
	class Texture2D;
	class BombComponent;
	class EnemyManager;
	enum class PowerupType;

	enum GridType
	{
		Empty,
		Wall,
		BrickWall,
		Bomb,
		Explosion
	};

	enum ExplosionType
	{
		Center,
		LeftMiddle,
		Left,
		UpMiddle,
		Up,
		RightMiddle,
		Right,
		DownMiddle,
		Down
	};

	struct PlaceBombResponse
	{
		bool success = false;
		int index = 0;
		glm::vec2 position = glm::vec2{};
	};


	class GridComponent : public Component, public Observer, public Subject
	{
	public:
		GridComponent();
		virtual ~GridComponent() override = default;

		virtual void OnSceneUnload() override;

		void SetGrid(int rows, int columns, float cubeSize);
		void SetupEnemies();

		virtual void Notify(const Event& event);

		virtual void Render() const override;

		void SetBomb(const glm::vec2 position, PlaceBombResponse& response);
		void GiveBomb(int index, BombComponent* pBombComponent);

		glm::vec2 GetPlayerPosition(int index);

		float GetLevelWidth();

		void SetupGame(const std::string& levelFile, float cubeSize, 
			Observer* pMainLevelUIObserver, Observer* pLivesDisplay, Observer* pPointsDisplay,
			const std::string& sceneName);
		void EndGame();

	private:
		int m_Rows{};
		int m_Columns{};
		float m_SquareSize{};

		int m_EnemieBorder{ 5 };
		int m_EnemyAmount{ 1 };

		std::shared_ptr<Texture2D> m_pWallTexture{};
		std::shared_ptr<Texture2D> m_pBrickWallTexture{};
		std::shared_ptr<Texture2D> m_pBrickExplosionTexture{};

		std::map<PowerupType, std::shared_ptr<Texture2D>> m_pPowerupSprites{};
		std::shared_ptr<Texture2D> m_pDoorTexture{};
		std::shared_ptr<Texture2D> m_pBombSprites{};

		std::vector<std::shared_ptr<Texture2D>> m_pPlayerSprites{};

		std::vector<std::shared_ptr<Texture2D>> m_pBalloonTextures{};
		std::vector<std::shared_ptr<Texture2D>> m_pOnealTextures{};
		std::vector<std::shared_ptr<Texture2D>> m_pDollTextures{};
		std::vector<std::shared_ptr<Texture2D>> m_pMinvoTextures{};


		std::map<ExplosionType,std::shared_ptr<Texture2D>> m_pExplosionTextures{};
		std::map<int, GameObject*> m_pBrickWalls{};
		std::map<int, BombComponent*> m_pBombs{};

		std::vector<GridType> m_Grid{};
		std::vector<int> m_PlayerSpawns{};

		EnemyManager* m_pEnemyManager{ nullptr };

		glm::vec2 WorldToGridPos(const glm::vec2& pos);
		int GetGridNumber(const glm::vec2& pos);
		glm::vec2 GetGridPos(int square);

		void ReadLevelFromFile(const std::string& file, float cubeSize, Observer* pMainLevelUIObserver);

		void SetGridWalls();

		void ExplodeBomb(ExplosionType type, int number, int strength, int currentDistance);
		void CreateExplosion(ExplosionType type, int gridNumber);

		int GetTopNeighbour(int number);
		int GetBottomNeighbour(int number);
		int GetLeftNeighbour(int number);
		int GetRightNeighbour(int number);

		void DeleteBrickWall(int number);

		void SpawnEnemy(int number, EnemyType type);

		void SetupPowerupAndWall(Observer* pMainLevelUIObserver);

		void SpawnDoor(int gridIndex, Observer* pMainLevelUIObserver);
		void SpawnPowerup(int gridIndex);
	};
}