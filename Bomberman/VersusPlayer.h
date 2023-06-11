#pragma once
#include "Component.h"
#include "Observer.h"
#include <glm/glm.hpp>

namespace D2D
{
	class ControlledState;

	class VersusPlayer : public Component, public Observer
	{
	public:
		VersusPlayer() = default;
		virtual ~VersusPlayer() override = default;

		virtual void Update() override;

		void Setup(const std::string& sceneName, float speed, int controllerIdx, const glm::vec2& levelMin, const glm::vec2& levelMax);

		void Move(const glm::vec2& directoin);


		virtual void Notify(const Event& event) override;

	private:
		float m_Speed{};

		glm::vec2 m_Direction{};

		glm::vec2 m_LevelMin{};
		glm::vec2 m_LevelMax{};

		ControlledState* m_pControlledEnemy{};

		void MovePlayer();
		void MoveEnemy();
	};
}

