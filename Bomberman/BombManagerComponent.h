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

		void SetBombSize(float size) { m_BombTextureSize = size; }

	private:
		std::shared_ptr<Texture2D> m_pBombtexture{};
		float m_BombTextureSize{};

		GridComponent* m_pGrid;

		void SpawnBomb(const glm::vec2& pos);
	};
}