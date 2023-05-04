#pragma once
#include "AnimationController.h"

namespace D2D
{
	class Texture2D;
	class RenderComponent;

	class BombAnimator final : public AnimationController
	{
	public:
		BombAnimator() = default;
		virtual ~BombAnimator() override = default;

		void Init(RenderComponent* pRenderComponent, std::shared_ptr<Texture2D> pTexture);
	};
}