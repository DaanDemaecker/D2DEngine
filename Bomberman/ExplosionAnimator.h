#pragma once
#include "AnimationController.h"
#include "Observer.h"

namespace D2D
{
	class Texture2D;
	class RenderComponent;

	class ExplosionAnimator final : public AnimationController, Observer
	{
	public:
		ExplosionAnimator() = default;
		virtual ~ExplosionAnimator() override = default;

		void Init(RenderComponent* pRenderComponent, std::shared_ptr<Texture2D> pTexture);

		virtual void Notify(const Event& event);
	};
}
