#pragma once
#include "AnimationController.h"

namespace D2D
{
	class RenderComponent;

	class PlayerAnimator final : public AnimationController
	{
	public:
		PlayerAnimator() = default;
		virtual ~PlayerAnimator() override = default;

		void Init(RenderComponent* pRenderComponent);
	};
}