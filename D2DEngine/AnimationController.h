#pragma once
#include "Component.h"
#include "AnimationClip.h"

namespace D2D
{

	class AnimationController : public Component
	{
	public:
		AnimationController() = default;
		virtual ~AnimationController() override = default;

		void SetShouldAnimate(bool shouldAnimate);

		virtual void Update() override;

	private:
		bool m_ShouldAnimate{ true };

	protected:
		std::vector<std::unique_ptr<AnimationClip>> m_pClips{};
		int m_CurrentClip{};
	};
}

