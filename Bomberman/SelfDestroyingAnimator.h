#pragma once
#include "AnimationController.h"
#include "Observer.h"

namespace D2D
{
	class Texture2D;
	class RenderComponent;

	class SelfDestroyingAnimator final : public AnimationController, Observer
	{
	public:
		SelfDestroyingAnimator() = default;
		virtual ~SelfDestroyingAnimator() override = default;

		void Init(RenderComponent* pRenderComponent, std::shared_ptr<Texture2D> pTexture, int cols, int rows, int frames);

		virtual void Notify(const Event& event);
	};
}
