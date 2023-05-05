#pragma once
#include "AnimationController.h"
#include <glm/glm.hpp>

namespace D2D
{
	class RenderComponent;

	class PlayerAnimator final : public AnimationController
	{
	public:
		PlayerAnimator() = default;
		virtual ~PlayerAnimator() override = default;

		void Init(RenderComponent* pRenderComponent);

		void SetDirection(const glm::vec2& direction) { m_Direction = direction; }

	private:
		glm::vec2 m_Direction{};


		bool ShouldGoDown();
		bool ShouldGoUp();
		bool ShouldGoLeft();
		bool ShouldGoRight();
	};
}