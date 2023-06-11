#pragma once
#include "Component.h"
#include "PlayerComponent.h"
#include "Observer.h"
#include "glm/glm.hpp"
#include <deque>

namespace D2D
{
	class Texture2D;
	class GridComponent;
	class BombComponent;

	class BombManagerComponent : public Component, public Observer
	{
	public:
		BombManagerComponent() = default;
		virtual ~BombManagerComponent() override = default;

		virtual void Notify(const Event& event);

		void SetGrid(GridComponent* grid);

		void SetBombSize(float size) { m_BombSize = size; }

		void SetBombTexture(std::shared_ptr<Texture2D> texture) { m_pBombtexture = texture; }

		void RemoteControlTriggered();

		void SetPlayerIndex(int idx);

	private:
		int m_PlayerIndex{};

		GridComponent* m_pGrid{};

		std::shared_ptr<Texture2D> m_pBombtexture{};
		float m_BombSize{};

		int m_BombStrength{1};
		int m_BombAmount{1};

		bool m_RemoteControlActive{ false };

		void SpawnBomb(const glm::vec2& pos);

		std::vector<BombComponent*> m_pBombs;

		void CollectPowerup(PowerupType type);
	};
}