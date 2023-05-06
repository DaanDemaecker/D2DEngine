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

	class BombManagerComponent : public Component, public Observer
	{
	public:
		BombManagerComponent();
		virtual ~BombManagerComponent() override = default;

		virtual void Notify(const Event& event);

		void SetGrid(GridComponent* grid);

		void SetBombSize(float size) { m_BombSize = size; }

	private:
		GridComponent* m_pGrid;

		std::shared_ptr<Texture2D> m_pBombtexture{};
		float m_BombSize{};

		int m_BombStrength{10};
		int m_BombAmount{1};
		int m_CurrentBombAmount{};

		void SpawnBomb(const glm::vec2& pos);
	};
}