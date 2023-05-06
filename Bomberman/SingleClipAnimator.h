#pragma once
#include "AnimationController.h"

namespace D2D
{
	class Texture2D;
	class RenderComponent;

	class SingleClipAnimator final : public AnimationController
	{
	public:
		SingleClipAnimator() = default;
		virtual ~SingleClipAnimator() override = default;

		void Init(RenderComponent* pRenderComponent, std::shared_ptr<Texture2D> pTexture, int cols, int rows, int frames);
	};
}