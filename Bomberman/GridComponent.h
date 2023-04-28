#pragma once
#include "Component.h"
#include "PlayerComponent.h"
#include "Observer.h"

namespace D2D
{
	class TextComponent;
	class PlayerComponent;
	class Texture2D;

	enum GridType
	{
		Empty,
		Wall,
		BrickWall,
		Bomb
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

	private:
		int m_Rows{};
		int m_Columns{};
		float m_SquareSize{};

		std::shared_ptr<Texture2D> m_pWallTexture{};
		std::shared_ptr<Texture2D> m_pBrickWallTexture{};

		std::vector<GridType> m_Grid{};

		glm::vec2 WorldToGridPos(const glm::vec2& pos);
		int GetGridNumber(const glm::vec2& pos);
		glm::vec2 GetGridPos(int square);

		void SetGridWalls();
	};
}