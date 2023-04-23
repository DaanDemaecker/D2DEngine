#pragma once
#include "Component.h"
#include "PlayerComponent.h"
#include "Observer.h"
#include "glm/glm.hpp"
#include <deque>

namespace D2D
{
	class Texture2D;

	class BombManagerComponent : public Component, public Observer
	{
	public:
		BombManagerComponent();
		virtual ~BombManagerComponent() override = default;

		virtual void Notify(const Event& event);

		//virtual void Update() override;

	private:
		std::shared_ptr<Texture2D> m_pBombtexture{};


		void SpawnBomb(const glm::vec2& pos);
	};
}