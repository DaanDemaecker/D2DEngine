#pragma once
#include "AnimationController.h"
#include <glm/glm.hpp>

namespace D2D
{
	class RenderComponent;
	class Observer;

	class PlayerAnimator final : public AnimationController
	{
	public:
		PlayerAnimator() = default;
		virtual ~PlayerAnimator() override = default;

		void Init(std::vector<std::shared_ptr<Texture2D>> pSprites, RenderComponent* pRenderComponent, Observer* pObserver);

		void SetDirection(const glm::vec2& direction) { m_Direction = direction; }

		void Kill() { m_IsDead = true; }

	private:
		glm::vec2 m_Direction{};

		bool m_IsDead{ false };

		bool ShouldGoDown();
		bool ShouldGoUp();
		bool ShouldGoLeft();
		bool ShouldGoRight();
		bool IsDead();
	};
}