#pragma once
#include "Component.h"
#include "PlayerComponent.h"
#include "Observer.h"
#include <map>

namespace D2D
{
	class TextComponent;
	class PlayerComponent;
	class Texture2D;
	class BombComponent;
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


	class GridComponent : public Component, public Observer
	{
	public:
		GridComponent();
		virtual ~GridComponent() override = default;

		void SetGrid(int rows, int columns, float cubeSize);
		void SetGrid(const std::string& file, float cubeSize);

		virtual void Notify(const Event& event);

		virtual void Render() const override;

		void SetBomb(const glm::vec2 position, PlaceBombResponse& response);
		void GiveBomb(int index, BombComponent* pBombComponent);

		glm::vec2 GetPlayerPosition(int index);

		float GetLevelWidth();

	private:
		int m_Rows{};
		int m_Columns{};
		float m_SquareSize{};

		int m_EnemieBorder{ 5 };
		int m_EnemyAmount{ 5 };

		std::shared_ptr<Texture2D> m_pWallTexture{};
		std::shared_ptr<Texture2D> m_pBrickWallTexture{};
		std::shared_ptr<Texture2D> m_pBrickExplosionTexture{};

		std::map<PowerupType, std::shared_ptr<Texture2D>> m_pPowerupSprites{};

		std::vector<std::shared_ptr<Texture2D>> m_pBalloonTextures{};


		std::map<ExplosionType,std::shared_ptr<Texture2D>> m_pExplosionTextures{};
		std::map<int, GameObject*> m_pBrickWalls{};
		std::map<int, BombComponent*> m_pBombs{};

		std::vector<GridType> m_Grid{};
		std::vector<int> m_PlayerSpawns{};

		glm::vec2 WorldToGridPos(const glm::vec2& pos);
		int GetGridNumber(const glm::vec2& pos);
		glm::vec2 GetGridPos(int square);

		void SetGridWalls();

		void ExplodeBomb(ExplosionType type, int number, int strength, int currentDistance);
		void CreateExplosion(ExplosionType type, int gridNumber);

		int GetTopNeighbour(int number);
		int GetBottomNeighbour(int number);
		int GetLeftNeighbour(int number);
		int GetRightNeighbour(int number);

		void DeleteBrickWall(int number);

		void SetupEnemies();
		void SpawnEnemy(int number);

		void SetupPowerupAndWall();

		void SpawnDoor(int gridIndex);
		void SpawnPowerup(int gridIndex);
	};
}