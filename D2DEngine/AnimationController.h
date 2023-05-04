#pragma once
#include "Component.h"
#include <functional>

namespace D2D
{
	class AnimationClip;

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

		struct Transition
		{
			int fromClip{};
			int toClip{};
			std::function<bool()> predicate{};
		};

		std::vector<std::unique_ptr<AnimationClip>> m_pClips{};
		int m_CurrentClip{};

		std::vector<std::unique_ptr<Transition>> m_pTransitions{};
	};
}

