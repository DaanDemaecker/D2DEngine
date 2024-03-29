#pragma once
#include "Structs.h"
#include "GameObject.h"
#include "Subject.h"
#include <memory>
#include <map>
#include <functional>

namespace D2D
{
	class Texture2D;
	class RenderComponent;
	struct Event;

	struct Transition
	{
		int toClip{};
		std::function<bool()> predicate{};
	};

	class AnimationClip final : public Subject
	{
	public:
		AnimationClip(RenderComponent* pRenderComponent);

		~AnimationClip() = default;

		AnimationClip(const AnimationClip& other) = delete;
		AnimationClip(AnimationClip&& other) = delete;
		AnimationClip& operator=(const AnimationClip& other) = delete;
		AnimationClip& operator=(AnimationClip&& other) = delete;

		void SetClip(std::shared_ptr<Texture2D> pTexture, int cols, int rows, int frames);

		void AddAnimationEvent(int clip, std::unique_ptr<Event> event);

		void SetCurrentSprite();

		void Update();

		void AddTransition(Transition transition);

		void SetFrameDuration(float duration) { m_FrameDuration = duration; }

		std::vector<Transition>& GetTransitions() { return m_Transitions; }

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		RenderComponent* m_pRenderComponent{};

		std::multimap<int, std::unique_ptr<Event>> m_AnimationEvents{};

		int m_Cols{};
		int m_Rows{};

		int m_FrameAmount{};
		int m_CurrentFrame{};

		Rect m_SrcRect{};

		float m_FrameDuration{ 1 / 15.f };
		float m_FrameTimer{};

		std::vector<Transition> m_Transitions{};

		void SetFrame();
	};
}
