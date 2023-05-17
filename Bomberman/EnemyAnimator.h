#pragma once
#include "AnimationController.h"
#include "Observer.h"
#include <glm/glm.hpp>

namespace D2D
{
	class RenderComponent;

	class EnemyAnimator final : public AnimationController, Observer
	{
	public:
		EnemyAnimator() = default;
		virtual ~EnemyAnimator() override = default;

		void Init(RenderComponent* pRenderComponent, std::vector<std::shared_ptr<Texture2D>>& pTextures);

		void FacingRight(bool facingRight) { m_FacingRight = facingRight; }
		void Kill() { m_IsDead = true; }

		void Notify(const Event& event);

	private:
		bool m_FacingRight{ true };
		bool m_IsDead{ false };

		bool ShouldGoLeft();
		bool ShouldGoRight();
		bool IsDead();
	};
}